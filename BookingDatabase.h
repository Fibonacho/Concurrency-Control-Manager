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
    
    /*int getRandomPassenger()
    {
        int random = RandomInt((int)PassengerList.size()-1);
        return PassengerList[random];
    }
    
    int getRandomFlight()
    {
        int random = RandomInt((int)FlightList.size()-1);
        return FlightList[random].mID;
    }*/
    
    int getRandomSeat()
    {
        return RandomInt(MaxSeatID)+1;
    }
    
    void initializeData()
    {
        database.AddTable(passengerTable);
        database.AddTable(flightsTable);
        database.AddTable(reservationTable);
        database.AddTable(seatTable);
        
        // inserts a new flight into the flight table / data structure and stores the id in the mFlightList
        addFlight("Tokio", 1);
        addFlight("New York", 1);
        addFlight("Berlin", 2);
        flightsTable.display();
        
        PassengerList.push_back(passengerTable.add("Eva"));
        PassengerList.push_back(passengerTable.add("Elvis"));
        PassengerList.push_back(passengerTable.add("Johanna"));
        passengerTable.display();
        
        // reservationTable.mFlightList = &FlightList;
        // reservationTable.mPassengerList = &PassengerList;
        
        //reservationTable.add(FlightList[0].mID, seatTable.getSeat(getRandomSeat()), PassengerList[2]);
        //reservationTable.add(getRandomFlight(), seatTable.getSeat(getRandomSeat()), getRandomPassenger());
        //reservationTable.display();
    }
    
    void removeReservation()
    {
        // if reservation do exist
        if (!reservationTable.isEmpty())
        {
            Reservations::Reservation* randomReservation = reservationTable.getRandomReservation();
            // childCount = 0 (no data in table - should usually not happen)
            if (randomReservation != nullptr)
            {
                std::cout << "Random Reservation to be removed: " << randomReservation->mFID << ", " << randomReservation->mPID << std::endl;
                // remove this reservation
                reservationTable.removeRes(randomReservation->mFID, randomReservation->mPID);
            }
        }
    }
    
    void getBookedFlights()
    {
        //get a Random Passanger ID
        int randomPID = passengerTable.getRandomPassengerID();
        std::cout << "Random Passanger to list bookings: " << randomPID << std::endl;
        reservationTable.getBookedFlights(randomPID);
    }

    void getReservationSum()
    {
        reservationTable.printReservationSum();
    }
    
    void bookFlight()
    {
        reservationTable.book();
    }
    
    void initializeTransactionHandler()
    {
        transactionHandler.addTransaction(getReservationSum);
        transactionHandler.addTransaction(removeReservation);
        transactionHandler.addTransaction(getBookedFlights);
        transactionHandler.addTransaction(bookFlight);
    }
}

#endif