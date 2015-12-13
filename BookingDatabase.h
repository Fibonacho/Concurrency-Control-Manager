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
    // creates a databases and tables (+ link them)
    Database db(&lockManager);
    Flights flights(&db);
    Passengers passengers(&db);
    Reservations reservations(&db);
    Seats seats(&db);
    TransactionHandler transactionHandler(db);
    
    bool DataConsoleOutput = false;
    
    namespace Transaction1 {
        // getReservationSum
        
        // total_reservations(): return the total sum of all reservations on all flights
        // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
        bool getReservationSum()
        {
            reservations.printReservationSum();
            return true;
        }
       
    }
    
    namespace Transaction2 {
        // removeReservation
        Reservations::Reservation* RandomReservation = nullptr;
        // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
        // if this transaction is performed on non-existing data (deleted during time), it does not have any influence (won't find a reservation)
        bool removeReservation()
        {
            if (RandomReservation != nullptr)
            {
                // get a random reservation
                // delete this random reservation
                // if reservation exists
                if (DataConsoleOutput)
                    std::cout << "Random Reservation to be removed: " << RandomReservation->mFID << ", " << RandomReservation->mPID << std::endl;
                // remove this reservation
                return reservations.removeRes(RandomReservation->mFID, RandomReservation->mPID);
            }
            return false;
        }
        
        bool getRandomReservation()
        {
            if (!reservations.isEmpty())
                RandomReservation = reservations.getRandom();
            else
                RandomReservation = nullptr;
            return (RandomReservation != nullptr);
        }
    }
    
    namespace Transaction3 {
        // getBookedFlights
        
        int RandomPID = -1;
        
        bool getRandomPassengerID()
        {
            RandomPID = passengers.getRandomID();
            return (RandomPID > 0);
        }
        
        // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
        // if this transaction is performed on non-existing data (deleted during time), it does not have an influence (no booking is found)
        bool getBookedFlights()
        {
            if (RandomPID > 0)
            {
                if (DataConsoleOutput)
                    std::cout << "Random Passenger to list bookings: " << RandomPID << std::endl;
                return reservations.getBookedFlights(RandomPID);
            }
            return false;
        }
    }

    namespace Transaction4 {
        
        // bookFlight
        int RandomPID = -1;
        int RandomFID = -1;
        std::vector<int> seatList;

        // get an existing passenger
        bool getRandomPID()
        {
            RandomPID = passengers.getRandomID();
            return (RandomPID > 0);
        }
        
        // get an existing flight - make sure they are not deleted (locks)
        bool getRandomFID()
        {
            RandomFID = flights.getRandomID();
            return (RandomFID > 0);
        }
        
        bool getSeatList()
        {
            seatList.clear();
            seatList = seats.getSeats(RandomFID);
            return true;
        }
        
        // book(flight_id, passenger_id): book a seat for a passenger on a flight
        bool bookFlight()
        {
            return reservations.book(RandomFID, RandomPID, seatList);
        }
    }
    
    //Transaction 2 objects

    Passengers::Passenger* RandomPassenger = nullptr;
    
    // helperfunction - add a flight to the table
    void addFlight(const std::string pDestination, const int pSeats)
    {
        int FlightID = flights.add(pDestination);
        seats.add(FlightID, pSeats);
    }
    
    // serial transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initTransactionHandlerSerial()
    {
        // Add all necessary locks to the transactions
        // they will be acquired before the transaction is excecuted
        // a serial schedule is obtained by locking the database in exclusive mode
        Transaction transaction1;
        Command* command1 = new Command(Transaction1::getReservationSum);
        command1->addObjectLock(Lock::LockingMode::exclusive, &db);
        transaction1.addCommand(command1);
        
        //Transaction transaction1(getReservationSum);
        //transaction1.addObjectLock(Lock::LockingMode::exclusive, &db);
        //transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2;
        Command* command2_0 = new Command(Transaction2::getRandomReservation);
        command2_0->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* command2_1 = new Command(Transaction2::removeReservation);
        command2_1->addObjectLock(Lock::LockingMode::exclusive, &db);
        transaction2.addCommand(command2_0);
        transaction2.addCommand(command2_1);
        
        //Transaction transaction2(removeReservation);
        //transaction2.addObjectLock(Lock::LockingMode::exclusive, &db);
        //transactionHandler.addTransaction(transaction2);
        
        Transaction transaction3;
        Command* command3_0 = new Command(Transaction3::getRandomPassengerID);
        command3_0->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* command3_1 = new Command(Transaction3::getBookedFlights);
        command3_1->addObjectLock(Lock::LockingMode::exclusive, &db);
        transaction3.addCommand(command3_0);
        transaction3.addCommand(command3_1);
        
        //Transaction transaction3(getBookedFlights);
        //transaction3.addObjectLock(Lock::LockingMode::exclusive, &db);
        //transactionHandler.addTransaction(transaction3);
        
        Transaction transaction4;
        Command* command4_0 = new Command(Transaction4::getRandomPID);
        command4_0->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* command4_1 = new Command(Transaction4::getRandomFID);
        command4_1->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* command4_2 = new Command(Transaction4::getSeatList);
        command4_2->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* command4_3 = new Command(Transaction4::bookFlight);
        command4_3->addObjectLock(Lock::LockingMode::exclusive, &db);
        transaction3.addCommand(command4_0);
        transaction3.addCommand(command4_1);
        transaction3.addCommand(command4_2);
        transaction3.addCommand(command4_3);
        
        //Transaction transaction4(bookFlight);
        //transaction4.addObjectLock(Lock::LockingMode::exclusive, &db);
        //transactionHandler.addTransaction(transaction4);
        transactionHandler.addTransaction(transaction1);
        transactionHandler.addTransaction(transaction2);
        transactionHandler.addTransaction(transaction3);
        transactionHandler.addTransaction(transaction4);
    }

    // concurrent transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initTransactionHandlerConcurrent()
    {
        // Add all necessary locks to the transactions
        // they will be acquired before the transaction is excecuted
        // this locking is on a table level but could also be extended to row level locking
        
        // get shared lock on reservation
        Transaction transaction1;
        Command* command1 = new Command(Transaction1::getReservationSum);
        command1->addObjectLock(Lock::LockingMode::shared, &reservations);
        transaction1.addCommand(command1);
    
        // Transaction transaction2(removeReservation);
        // get exclusive lock on reservation row + shared lock on reservation
        // transaction2.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        
        transactionHandler.addTransaction(transaction1);
        
        Transaction transaction2;
        Command* command2_0 = new Command(Transaction2::getRandomReservation);
        command2_0->addObjectLock(Lock::LockingMode::shared, &reservations);
        Command* command2_1 = new Command(Transaction2::removeReservation);
        command2_1->addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transaction2.addCommand(command2_0);
        transaction2.addCommand(command2_1);
        transactionHandler.addTransaction(transaction2);
        
        // Transaction transaction3(getBookedFlights);
        // get shared lock on passenger and reservation
        // transaction3.addObjectLock(Lock::LockingMode::shared, &reservations);
        // transaction3.addObjectLock(Lock::LockingMode::shared, &passengers);
        
        
        Transaction transaction3;
        Command* command3_0 = new Command(Transaction3::getRandomPassengerID);
        command3_0->addObjectLock(Lock::LockingMode::shared, &passengers);
        Command* command3_1 = new Command(Transaction3::getBookedFlights);
        command3_1->addObjectLock(Lock::LockingMode::shared, &reservations);
        transaction3.addCommand(command3_0);
        transaction3.addCommand(command3_1);
        transactionHandler.addTransaction(transaction3);
        
        //Transaction transaction3(getBookedFlights);
        //transaction3.addObjectLock(Lock::LockingMode::exclusive, &db);
        //transactionHandler.addTransaction(transaction3);
        // Transaction transaction4(bookFlight);
        // get passenger, flight, seat shared lock und exclusive lock on booking
        // transaction4.addObjectLock(Lock::LockingMode::shared, &passengers);
        // transaction4.addObjectLock(Lock::LockingMode::shared, &flights);
        // transaction4.addObjectLock(Lock::LockingMode::shared, &seats);
        // transaction4.addObjectLock(Lock::LockingMode::exclusive, &reservations);
        
        Transaction transaction4;
        Command* command4_0 = new Command(Transaction4::getRandomPID);
        command4_0->addObjectLock(Lock::LockingMode::shared, &passengers);
        Command* command4_1 = new Command(Transaction4::getRandomFID);
        command4_1->addObjectLock(Lock::LockingMode::shared, &flights);
        Command* command4_2 = new Command(Transaction4::getSeatList);
        command4_2->addObjectLock(Lock::LockingMode::shared, &seats);
        Command* command4_3 = new Command(Transaction4::bookFlight);
        command4_3->addObjectLock(Lock::LockingMode::exclusive, &reservations);
        transaction4.addCommand(command4_0);
        transaction4.addCommand(command4_1);
        transaction4.addCommand(command4_2);
        transaction4.addCommand(command4_3);
        transactionHandler.addTransaction(transaction4);
    }

    // only for testing purposes
    void checkData()
    {
        // do some data checks and warningss
        // make sure there are no more flights than seats, otherweise you get a warning
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