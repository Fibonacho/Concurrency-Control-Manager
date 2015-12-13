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

typedef bool (*Function)(void);
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
        // total_reservations(): return the total sum of all reservations on all flights
        // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
        bool getReservationSum()
        {
            return reservations.printReservationSum();
        }
    }
    
    namespace Transaction2 {
        // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
        // if this transaction is performed on non-existing data (deleted during time)
        // it does not have any influence (won't find a reservation)
        
        Reservations::Reservation* RandomReservation = nullptr;
        
        bool removeReservation()
        {
            // if reservation exists
            if (RandomReservation != nullptr)
            {
                // delete the random reservation
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
            //returns true if a RandomReservation is successfully set
            return (RandomReservation != nullptr);
        }
    }
    
    namespace Transaction3 {
        // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
        // if this transaction is performed on non-existing data (deleted during time), it does not have an influence (no booking is found)
        
        int RandomPID = -1;
        
        // get a random reservation ID
        bool getRandomPassengerID()
        {
            RandomPID = passengers.getRandomID();
            // returns true if a random passenger was found (the id is grater than 0)
            return (RandomPID > 0);
        }
        
        bool getBookedFlights()
        {
            // print the booked flights of the random PID if one was found
            if (RandomPID > 0)
            {
                if (DataConsoleOutput)
                    std::cout << "Random Passenger to list bookings: " << RandomPID << std::endl;
                return reservations.getBookedFlights(RandomPID);
            }
            return false;
        }
    }

    namespace Transaction4
    {
        // book(flight_id, passenger_id): book a seat for a passenger on a flight
        // first get a random passenger ID and a flight ID
        // then, get the seat list for this flight
        // then, call reservations.book using those as parameters
        
        int RandomPID = -1;
        int RandomFID = -1;
        std::vector<int> seatList;

        // get an existing passenger / make sure they are not deleted
        bool getRandomPID()
        {
            RandomPID = passengers.getRandomID();
            return (RandomPID > 0);
        }
        
        // get an existing flight / make sure they are not deleted
        bool getRandomFID()
        {
            RandomFID = flights.getRandomID();
            return (RandomFID > 0);
        }
        
        // get all setas from the flight
        bool getSeatList()
        {
            seatList.clear();
            seatList = seats.getSeats(RandomFID);
            return true;
        }
        
        // book a flight, true is returned if the reservation was successful
        bool bookFlight()
        {
            return reservations.book(RandomFID, RandomPID, seatList);
        }
    }
   
    // helperfunction - add a flight to the table
    void addFlight(const std::string pDestination, const int pSeats)
    {
        int FlightID = flights.add(pDestination);
        seats.add(FlightID, pSeats);
    }
    
    // helper function to create a serial command
    void newSerialCommand(Transaction* pTransaction, Function pFunction)
    {
        Command* command = new Command(pTransaction, pFunction);
        command->addObjectLock(Lock::LockingMode::exclusive, &db);
    }
    
    // serial transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initTransactionHandlerSerial()
    {
        // Add all necessary locks to the transactions
        // they will be acquired before the transaction is excecuted
        // a serial schedule is obtained by locking the db exclusively in any command of any transaction
        Transaction transactions[4];
        // Transaction 1 (print reservation sum), has only one command
        newSerialCommand(&transactions[0], Transaction1::getReservationSum);
        // Transaction 2 (remove reservatio)
        // has two commands; get a random reservation to remove and then remove it
        newSerialCommand(&transactions[1], Transaction2::getRandomReservation);
        newSerialCommand(&transactions[1], Transaction2::removeReservation);
        // Transaction 3 (get booked flights)
        // has two commands: get random passenger and book flights of this passenger
        newSerialCommand(&transactions[2], Transaction3::getRandomPassengerID);
        newSerialCommand(&transactions[2], Transaction3::getBookedFlights);
        // Transaction 4 (book flight)
        // has 4 commands: get random passenger + flight, get seats from flight and booking itself
        newSerialCommand(&transactions[3], Transaction4::getRandomFID);
        newSerialCommand(&transactions[3], Transaction4::getSeatList);
        newSerialCommand(&transactions[3], Transaction4::getRandomPID);
        newSerialCommand(&transactions[3], Transaction4::bookFlight);
        
        // add all transactions to the transactionHandler
        for (int i = 0; i < 4; i++)
            transactionHandler.addTransaction(transactions[i]);
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
        Transaction transactions[4];
        
        Command* command1 = new Command(&transactions[0], Transaction1::getReservationSum);
        command1->addObjectLock(Lock::LockingMode::shared, &reservations);
        
        Command* command2_0 = new Command(&transactions[1], Transaction2::getRandomReservation);
        command2_0->addObjectLock(Lock::LockingMode::shared, &reservations);
        Command* command2_1 = new Command(&transactions[1], Transaction2::removeReservation);
        // upgrade:
        command2_1->addObjectLock(Lock::LockingMode::exclusive, &reservations);
        
        Command* command3_0 = new Command(&transactions[2], Transaction3::getRandomPassengerID);
        command3_0->addObjectLock(Lock::LockingMode::shared, &passengers);
        Command* command3_1 = new Command(&transactions[2], Transaction3::getBookedFlights);
        command3_1->addObjectLock(Lock::LockingMode::shared, &reservations);
        
        Command* command4_0 = new Command(&transactions[3], Transaction4::getRandomPID);
        command4_0->addObjectLock(Lock::LockingMode::shared, &passengers);
        Command* command4_1 = new Command(&transactions[3], Transaction4::getRandomFID);
        command4_1->addObjectLock(Lock::LockingMode::shared, &flights);
        Command* command4_2 = new Command(&transactions[3], Transaction4::getSeatList);
        command4_2->addObjectLock(Lock::LockingMode::shared, &seats);
        Command* command4_3 = new Command(&transactions[3], Transaction4::bookFlight);
        command4_3->addObjectLock(Lock::LockingMode::exclusive, &reservations);
        
        // add all transactions to the transactionHandler
        for (int i = 0; i < 4; i++)
            transactionHandler.addTransaction(transactions[i]);
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