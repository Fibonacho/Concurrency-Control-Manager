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
    // creates a databases and tables (+ link them)
    Database db;
    Flights flights(&db);
    Passengers passengers(&db);
    Reservations reservations(&db);
    Seats seats(&db);
    
    TransactionHandler transactionHandler(db);
    
    // helperfunction - add a flight to the table
    void addFlight(std::string pDestination, int pSeats)
    {
        int FlightID = flights.add(pDestination);
        seats.add(FlightID, pSeats);
    }
    
    // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
    // if this transaction is performed on non-existing data (deleted during time), it does not have any influence (won't find a reservation)
    void removeReservation()
    {
        // if reservation exists
        if (!reservations.isEmpty())
        {
            Reservations::Reservation randomReservation = reservations.getRandomReservation();
            std::cout << "Random Reservation to be removed: " << randomReservation.mFID << ", " << randomReservation.mPID << std::endl;
            // remove this reservation
            reservations.removeRes(randomReservation.mFID, randomReservation.mPID);
        }
        reservations.display();
        // 2PL: release lock on reservation
    }
    
    // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
    // if this transaction is performed on non-existing data (deleted during time), it does not have an influence (no booking is found)
    void getBookedFlights()
    {
        // 2PL: get shared lock on passenger and reservation
        // get a Random Passenger ID
        int randomPID = passengers.getRandomPassengerID();
        std::cout << "Random Passenger to list bookings: " << randomPID << std::endl;
        reservations.getBookedFlights(randomPID);
        // 2PL: release lock on reservation
    }
    
    // total_reservations(): return the total sum of all reservations on all flights
    // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
    void getReservationSum()
    {
        // 2PL: get shared lock on reservation
        reservations.printReservationSum();
        // 2PL: release lock on reservation
    }
    
    // book(flight_id, passenger_id): book a seat for a passenger on a flight
    void bookFlight()
    {
        // 2PL: get passenger, flight, seat shared lock und exclusive lock on booking
        // get an existing passenger
        int randomPID = passengers.getRandomPassengerID();
        // get an existing flight - make sure they are not deleted (locks)
        int randomFID = flights.getRandomFlightID();
        std::vector<int> seatList = seats.getSeats(randomFID);
        reservations.book(randomFID, randomPID, seatList);
        // 2PL: release passenger, flight, seat and reservation lock
        reservations.display();
    }
    
    // serial transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initializeTransactionHandlerSerial()
    {
        Transaction transaction1(getReservationSum);
        //Add all necessary locks to the transaction, they will be acquired before the transaction is excecuted
        transaction1.addObjectLock(Lock::LockingMode::exclusive, &db);
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2(removeReservation);
        transaction2.addObjectLock(Lock::LockingMode::exclusive, &db);
        transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3(getBookedFlights);
        transaction3.addObjectLock(Lock::LockingMode::exclusive, &db);
        transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4(bookFlight);
        transaction4.addObjectLock(Lock::LockingMode::exclusive, &db);
        transactionHandler.addTransaction(transaction4);
    }

    // concurrent transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initializeTransactionHandlerConcurrent()
    {
        Transaction transaction1(getReservationSum);
        transaction1.addObjectLock(Lock::LockingMode::shared, &reservations);
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2(removeReservation);
        // 2PL: get exclusive lock on reservation row + shared lock on reservation
        transaction1.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3(getBookedFlights);
        transaction3.addObjectLock(Lock::LockingMode::shared, &reservations);
        transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4(bookFlight);
        transaction3.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transactionHandler.addTransaction(transaction4);
    }

    // initialize data:
    // - setup database
    // - add tables to database (tables for passengers, flights, reservations, seats)
    // - add rows to tables (flights and passengers)
    // - book flights (which creates rows in the table for reservations)
    // - display tables (i.e. print to console)
    void initializeData(std::string (&destinations)[10], std::string (&passengerNames)[20])
    {
        initRand();

        // inserts 20 new flights into the flight table / data structure and stores the id in the mFlightList
        for (int i = 0; i < 2; i++)
            for (const std::string &destination: destinations)
                addFlight(destination, 20);
        flights.display(); // print flightsTable to console
        
        // inserts 20*i new passengers into passenger table
        for (int i = 0; i < 5; i++)
            for (const std::string &passenger: passengerNames)
                passengers.add(passenger);
        passengers.display(); // print passengersTable to console
        reservations.display(); // print reservationTable to console
    }

}

#endif