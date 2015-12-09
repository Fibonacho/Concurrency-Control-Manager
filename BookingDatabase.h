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
#include "LockManager.h"

namespace BookingDatabase {
    LockManager lockManager;
    // creates a database and tables (+ links them)
    Database db(&lockManager);
    Flights flights(&db);
    Passengers passengers(&db);
    Reservations reservations(&db);
    Seats seats(&db);
    TransactionHandler transactionHandler(db);
    
    bool DataConsoleOutput = false;
    
    // helperfunction - add a flight to the table
    void addFlight(const std::string pDestination, const int pSeats)
    {
        int FlightID = flights.add(pDestination);
        seats.add(FlightID, pSeats);
    }
    
    // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
    // if this transaction is performed on non-existing data (deleted during time),
    // it does not have any influence (won't find a reservation)
    bool removeReservation()
    {
        // if any reservation exists
        if (!reservations.isEmpty())
        {
            Reservations::Reservation randomReservation = reservations.getRandomReservation();
            if (DataConsoleOutput)
                std::cout << "Random Reservation to be removed: " << randomReservation.mFID << ", " << randomReservation.mPID << std::endl;
            // remove this reservation and get true/false (depending on success)
            bool ok = reservations.removeRes(randomReservation.mFID, randomReservation.mPID);
            return ok;
        }
        return false; // at this point, no reservation was removed (maybe there was not any)
    }
    
    // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
    // if this transaction is performed on non-existing data (deleted during time), it does not
    // have any influence (no booking is found)
    bool getBookedFlights()
    {
        // get a Random Passenger ID
        const int randomPID = passengers.getRandomPassengerID();
        if (DataConsoleOutput)
            std::cout << "Random Passenger to list bookings: " << randomPID << std::endl;
        reservations.getBookedFlights(randomPID);
        return true;
    }
    
    // total_reservations(): return the total sum of all reservations on all flights
    // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
    bool getReservationSum()
    {
        reservations.printReservationSum();
        return true;
    }
    
    // book(flight_id, passenger_id): book a seat for a passenger on a flight
    bool bookFlight()
    {
        // get an existing passenger
        int randomPID = passengers.getRandomPassengerID();
        // get an existing flight - make sure they are not deleted (locks)
        int randomFID = flights.getRandomFlightID();
        std::vector<int> seatList = seats.getSeats(randomFID);
        bool ok = reservations.book(randomFID, randomPID, seatList);
        return ok;
    }
    
    // serial transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initTransactionHandlerSerial()
    {
        // add all necessary locks to the transactions
        // they will be acquired before the transaction is excecuted
        // a serial schedule is obtained by locking the database
        // in exclusive mode (by every transaction separately)
        Transaction transaction1(getReservationSum);
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
    void initTransactionHandlerConcurrent()
    {
        // add all necessary locks to the transactions
        // they will be acquired before the transaction is excecuted
        // this locking is on a table level but could also be extended to row level locking

        Transaction transaction1(getReservationSum);
        // get shared lock on reservation (only read-operation)
        transaction1.addObjectLock(Lock::LockingMode::shared, &reservations);
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2(removeReservation);
        // get exclusive lock on reservation row (write-operation) + shared lock on reservation
        transaction2.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3(getBookedFlights);
        // get shared lock on passenger and reservation (both read-operations)
        transaction3.addObjectLock(Lock::LockingMode::shared, &reservations);
        transaction3.addObjectLock(Lock::LockingMode::shared, &passengers);
        transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4(bookFlight);
        // get passenger, flight, seat (all read-operations) shared lock
        // and exclusive lock on booking (write-operation)
        transaction4.addObjectLock(Lock::LockingMode::shared, &passengers);
        transaction4.addObjectLock(Lock::LockingMode::shared, &flights);
        transaction4.addObjectLock(Lock::LockingMode::shared, &seats);
        transaction4.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transactionHandler.addTransaction(transaction4);
    }

    // only for testing purposes
    void checkData()
    {
        // do some data checks and warnings
        // make sure there are not more flights than seats, otherwise you get a warning
        if (seats.getRowCount() < flights.getRowCount())
            std::cerr << "WARNING: there are not more flights than seats" << std::endl;
        
        if (reservations.getRowCount() > passengers.getRowCount())
            std::cerr << "WARNING: more passengers than reservations!? this is not possible, dude!" << std::endl;
    }
    
    // initialize data:
    // - setup database
    // - add tables to database (tables for passengers, flights, reservations, seats)
    // - add rows to tables (flights and passengers)
    // - book flights (which creates rows in the table for reservations)
    // - display tables (i.e. print to console)
    void initData(std::vector<std::string>& pDestinationList, std::vector<std::string>& pPassengerList, int AverageSeatCount)
    {
        initRand();
        
        // inserts 20 new flights into the flight table / data structure and stores the id in the mFlightList
        for (auto destination: pDestinationList)
        {
            //add / substract some random seat offset
            int offset = RandomInt(10);
            addFlight(destination, AverageSeatCount+offset-5);
        }
        flights.display(); // print flightsTable to console
        
        // inserts passengers into passenger table
        for (auto passenger: pPassengerList)
            passengers.add(passenger);
        passengers.display(); // print passengersTable to console
        reservations.display(); // print reservationTable to console (should be empty)
        
        checkData();
    }

}

#endif