//  ---------------------------------------------------
//  BookingDatabase.h
//  - namespace for the booking database
//  - neccesary tables (flights, passengers, reservations and seast) are created
//  - the transaction handler is initialized and called
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef BOOKINGDATABASE_H
#define BOOKINGDATABASE_H

#include "Database.h"
#include "Flights.h"
#include "Passengers.h"
#include "Seats.h"
#include "Reservations.h"
#include "TransactionHandler.h"
#include "Common.h"
#include "Transaction.h"

namespace BookingDatabase {
    // creates database
    Database database;
    // creates tables
    Flights flightsTable(database);
    Passengers passengerTable(database);
    Reservations reservationTable(database);
    Seats seatTable(database);
    // adds tables to database
    
    TransactionHandler transactionHandler(database);
    
    struct FlightListElement {
        int mID;
        std::vector<int> mSID;
        FlightListElement(int pID) : mID(pID) {}
    };
    
    std::vector<FlightListElement> FlightList;
    //std::vector<int> FlightSeats;
    std::vector<int> PassengerList;
    
    int MaxSeatID = 0;
    
    void addFlight(std::string pDestination, int pSeats)
    {
        int FlightID = flightsTable.add(pDestination);
        FlightListElement listElement(FlightID);
        //listElement.mSID.push_back();
        //FlightSeats.push_back(pSeats);
        //FlightList.push_back(listElement);
        MaxSeatID += pSeats;
        seatTable.add(FlightID, pSeats);
    }
    
    int getRandomSeat()
    {
        return RandomInt(MaxSeatID)+1;
    }
    
    // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
    // if this transaction is performed on non-existing data (deleted during time), it does not have any influence (won't find a reservation)
    void removeReservation()
    {
        // 2PL: get exclusive lock on reservation row + shared lock on reservation
        // if reservation exists
        if (!reservationTable.isEmpty())
        {
            Reservations::Reservation randomReservation = reservationTable.getRandomReservation();
            std::cout << "Random Reservation to be removed: " << randomReservation.mFID << ", " << randomReservation.mPID << std::endl;
            // remove this reservation
            reservationTable.removeRes(randomReservation.mFID, randomReservation.mPID);
        }
        // 2PL: release lock on reservation
    }
    
    // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
    // if this transaction is performed on non-existing data (deleted during time), it does not have an influence (no booking is found)
    void getBookedFlights()
    {
        // 2PL: get shared lock on passenger and reservation
        // get a Random Passanger ID
        int randomPID = passengerTable.getRandomPassengerID();
        std::cout << "Random Passanger to list bookings: " << randomPID << std::endl;
        reservationTable.getBookedFlights(randomPID);
        // 2PL: release lock on reservation
    }
    
    // total_reservations(): return the total sum of all reservations on all flights
    // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
    void getReservationSum()
    {
        // 2PL: get shared lock on reservation
        reservationTable.printReservationSum();
        // 2PL: release lock on reservation
    }
    
    // book(flight_id, passenger_id): book a seat for a passenger on a flight
    void bookFlight()
    {
        // 2PL: get passanger, flight, seat shared lock und exclusive lock on booking
        // get an existing passenger
        int randomPID = passengerTable.getRandomPassengerID();
        // get an existing flight - make sure they are not deleted (locks)
        int randomFID = flightsTable.getRandomFlightID();
        std::vector<int> seatList = seatTable.getSeats(randomFID);
        reservationTable.book(randomFID, randomPID, seatList);
        // 2PL: release passanger, flight, seat and reservation lock
    }
    
    void initializeTransactionHandlerSerial()
    {
        Transaction transaction1(getReservationSum);
        //Add all necessary locks to the transaction, they will be acquired before the transaction is excecuted
        transaction1.addObjectLock(Lock::LockingMode::exclusive, &database);
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2(removeReservation);
        transaction2.addObjectLock(Lock::LockingMode::exclusive, &database);
        transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3(getBookedFlights);
        transaction3.addObjectLock(Lock::LockingMode::exclusive, &database);
        transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4(bookFlight);
        transaction4.addObjectLock(Lock::LockingMode::exclusive, &database);
        transactionHandler.addTransaction(transaction4);
    }
    
    void initializeTransactionHandlerConcurrent()
    {
        Transaction transaction1(getReservationSum);
        transaction1.addObjectLock(Lock::LockingMode::shared, &reservationTable);
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2(removeReservation);
        transaction1.addObjectLock(Lock::LockingMode::exclusive, &reservationTable);
        transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3(getBookedFlights);
        transaction3.addObjectLock(Lock::LockingMode::shared, &reservationTable);
        transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4(bookFlight);
        transaction3.addObjectLock(Lock::LockingMode::exclusive, &reservationTable);
        transactionHandler.addTransaction(transaction4);
    }

    void initializeData()
    {
        initRand();
        
        database.AddTable(passengerTable);
        database.AddTable(flightsTable);
        database.AddTable(reservationTable);
        database.AddTable(seatTable);
        
        // inserts a new flight into the flight table / data structure and stores the id in the mFlightList
        addFlight("Tokio", 100);
        addFlight("New York", 100);
        addFlight("Berlin", 200);
        flightsTable.display();
        
        PassengerList.push_back(passengerTable.add("Eva"));
        PassengerList.push_back(passengerTable.add("Elvis"));
        PassengerList.push_back(passengerTable.add("Johanna"));
        passengerTable.display();
        
        bookFlight();
        bookFlight();
        bookFlight();
        reservationTable.display();
    }

}

#endif