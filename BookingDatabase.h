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
#include <algorithm>
#include <sstream>
//#include <mutex>
//#include "LogFile.h"

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
    //LogFile* mLogFile = nullptr;
    
    bool DataConsoleOutput = false;
    
    namespace Transaction1 {
        // total_reservations(): return the total sum of all reservations on all flights
        // this transaction can't be called on non-existing data, table could be empty, then 0 is printed
        
        // should always return true
        //std::mutex m;
        
        bool getReservationSum()
        {
            //m.lock();
            bool a = reservations.printReservationSum();
            //m.unlock();
            return a;
        }
    }
    
    namespace Transaction2 {
        // cancel(flight_id, passenger_id): cancel reservation for passenger on a flight
        // if this transaction is performed on non-existing data (deleted during time)
        // it does not have any influence (won't find a reservation)
        // std::mutex m1, m2;
        
        const Reservations::Reservation* RandomReservation = nullptr;
            
        bool removeReservation()
        {
            // m1.lock();
            // if reservation exists
            if (RandomReservation != nullptr)
            {
                // delete the random reservation
                //if (DataConsoleOutput)
                //    mLogFile->write("Random Reservation to be removed: " + std::to_string(RandomReservation->mFID) + ", " + std::to_string(RandomReservation->mPID));
                // remove this reservation
                bool a = reservations.removeRes(RandomReservation->mFID, RandomReservation->mPID);
                // m1.unlock();
                return a;
            }
            // m1.unlock();
            return false;
        }
        
        // returns false if no reservation is found
        bool getRandomReservation()
        {
            // m2.lock();
            if (!reservations.isEmpty())
                RandomReservation = reservations.getRandom();
            else
                RandomReservation = nullptr;
            //returns true if a RandomReservation is successfully set
            bool a = (RandomReservation != nullptr);
            // m2.unlock();
            return a;
        }
    }
    
    namespace Transaction3 {
        // my_flights(passenger_id): return the set of flights on which a passenger has a reservation
        // if this transaction is performed on non-existing data (deleted during time), it does not have an influence (no booking is found)
        // std::mutex m1, m2;
        
        int RandomPID = -1;
        
        // get a random reservation ID
        // should return a valid passanger in any case if the table is filled
        bool getRandomPID()
        {
            // m1.lock();
            RandomPID = passengers.getRandomID();
            // returns true if a random passenger was found (the id is grater than 0)
            bool a = (RandomPID > 0);
            // m1.unlock();
            return a;
        }
        
        // is always successful if the passanger exists (if table is filled)
        bool getBookedFlights()
        {
            // m2.lock();
            // print the booked flights of the random PID if one was found
            if (RandomPID > 0)
            {
                //if (DataConsoleOutput)
                //    mLogFile->write("Random Passenger to list bookings: " + std::to_string(RandomPID));
                bool a = reservations.getBookedFlights(RandomPID);
                // m2.unlock();
                return a;
            }
            // m2.unlock();
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
        // std::mutex m1, m2, m3, m4;

        // get an existing passenger / make sure they are not deleted
        // returns true if passanger exists in table (is filled)
        bool getRandomPID()
        {
            // m1.lock();
            RandomPID = passengers.getRandomID();
            bool a = (RandomPID > 0);
            // m1.unlock();
            return a;
        }
        
        // get an existing flight / make sure they are not deleted
        // returns true if flights exist in table (is filled)
        bool getRandomFID()
        {
            // m2.lock();
            RandomFID = flights.getRandomID();
            bool a = (RandomFID > 0);
            // m2.unlock();
            return a;
        }
        
        // get all setas from the flight
        // should always return true if the database is initialized properly
        bool getSeatList()
        {
            // m3.lock();
            int i = RandomFID;
            seatList.clear();
            seatList = seats.getSeats(i);
            bool a = (seatList.size() > 0);
            // m3.unlock();
            return a;
        }
        
        // book a flight, true is returned if the reservation was successful
        bool bookFlight()
        {
            // m4.lock();
            bool a = reservations.book(RandomFID, RandomPID, seatList);
            // m4.unlock();
            return a;
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
    
    // Add all necessary locks to the transactions
    // they will be acquired before the transaction is excecuted
    // a serial schedule is obtained by locking the db exclusively in any command of any transaction
    Transaction transactions[4];
    
    // serial transaction handler:
    // - create transactions (getReservationSum, removeReservation, getBookedFlights, bookFlight)
    // - add locks to transaction objects
    // - add transactions to transaction handler
    void initTransactionHandlerSerial()
    {
        // Transaction 1 (print reservation sum), has only one command
        Command* c1 = new Command(&transactions[0], Transaction1::getReservationSum);
        c1->addObjectLock(Lock::LockingMode::exclusive, &db);
        
        // Transaction 2 (remove reservatio)
        // has two commands; get a random reservation to remove and then remove it
        Command* c2 = new Command(&transactions[1], Transaction2::getRandomReservation);
        c2->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* c3 = new Command(&transactions[1], Transaction2::removeReservation);
        c3->addObjectLock(Lock::LockingMode::exclusive, &db);
        
        // Transaction 3 (get booked flights)
        // has two commands: get random passenger and book flights of this passenger
        Command* c4 = new Command(&transactions[2], Transaction3::getRandomPID);
        c4->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* c5 = new Command(&transactions[2], Transaction3::getBookedFlights);
        c5->addObjectLock(Lock::LockingMode::exclusive, &db);
        
        Command* c6 = new Command(&transactions[3], Transaction4::getRandomFID);
        c6->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* c7 = new Command(&transactions[3], Transaction4::getSeatList);
        c7->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* c8 = new Command(&transactions[3], Transaction4::getRandomPID);
        c8->addObjectLock(Lock::LockingMode::exclusive, &db);
        Command* c9 = new Command(&transactions[3], Transaction4::bookFlight);
        c9->addObjectLock(Lock::LockingMode::exclusive, &db);

        
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
        
        Command* command1 = new Command(&transactions[0], Transaction1::getReservationSum);
        command1->addObjectLock(Lock::LockingMode::shared, &reservations);
        
        Command* command2_0 = new Command(&transactions[1], Transaction2::getRandomReservation);
        command2_0->addObjectLock(Lock::LockingMode::shared, &reservations);
        Command* command2_1 = new Command(&transactions[1], Transaction2::removeReservation);
        // upgrade:
        command2_1->addObjectLock(Lock::LockingMode::exclusive, &reservations);
        
        Command* command3_0 = new Command(&transactions[2], Transaction3::getRandomPID);
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
        //if (seats.getRowCount() < flights.getRowCount())
            //std::cerr << "WARNING: there are not more flights than seats" << std::endl;
        
        //if (reservations.getRowCount() > passengers.getRowCount())
        //    std::cerr << "WARNING: more passengers than reservations!? this is not possible, dude!" << std::endl;
    }
    
    // initialize data:
    // - setup database
    // - add tables to database (tables for passengers, flights, reservations, seats)
    // - add rows to tables (flights and passengers)
    // - book flights (which creates rows in the table for reservations)
    // - display tables (i.e. print to console)
    void initData(std::vector<std::string>& pDestinationList, std::vector<std::string>& pPassengerList, int AverageSeatCount, int MaxSeatCount, int PassengerCount, int FlightCount)
    
    //void initData(std::vector<std::string>& pDestinationList, std::vector<std::string>& pPassengerList, int AverageSeatCount)
    {
        initRand();
        
        // inserts 20 new flights into the flight table / data structure and stores the id in the mFlightList
        //for (auto destination: pDestinationList)
        int numbOfSeats;
        int flight = 0;
        for (unsigned int f = 1; f <= FlightCount / pDestinationList.size(); f++)
        {
            //add / substract some random seat offset
            //int offset = RandomInt(10);
            //addFlight(destination, AverageSeatCount+offset-5);
            // inserts <FlightCount> new flights into the flight table / data structure and stores the id in the mFlightList
            for (auto destination: pDestinationList)
            {
                flight++; // count flight sum
                // for the last flight, take the remaining seats of MaxSeatCount
                if (flight == FlightCount)
                    numbOfSeats = MaxSeatCount;
                else
                {
                    // add / substract some random seat offset
                    int offset = RandomInt(FlightCount);
                    numbOfSeats = AverageSeatCount + offset - 5;
                    MaxSeatCount -= numbOfSeats;
                }
                // add number to destination name, to distinguish between flights by name
                std::stringstream sstm;
                sstm << destination << "_" << f;
                std::string target = sstm.str();
                
                if (numbOfSeats < 0)
                    numbOfSeats = std::max(numbOfSeats, 0);
                
                addFlight(target, numbOfSeats);
                //std::cout << "Flight target: " << target << ", max: " << MaxSeatCount << ", numb of seats: " << numbOfSeats << std::endl;
            }
        }
        flights.display(); // print flightsTable to console
        
        // inserts passengers into passenger table
        //for (auto passenger: pPassengerList)
        //    passengers.add(passenger);
        
        // inserts <PassengerCount> passengers into passenger table
        for (unsigned int p = 1; p <= PassengerCount / pPassengerList.size(); p++)
        {
            for (auto passenger : pPassengerList)
            {
            // add number to passenger name, to distinguish between passengers by name
                std::stringstream sstm;
                sstm << passenger << "_" << p;
                std::string name = sstm.str();
                passengers.add(name);
            }
        }
        
        passengers.display(); // print passengersTable to console
        reservations.display(); // print reservationTable to console (should be empty)
        
        checkData();
    }

}

#endif