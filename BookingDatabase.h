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
    Database database;
    Flights flightsTable(database);
    Passengers passengerTable(database);
    Reservations reservationTable(database);
    Seats seatTable(database);
    TransactionHandler transactionHandler(database);
    
    std::vector<int*> FlightList;
    std::vector<int*> PassengerList;
    int MaxSeatID = 0;
    
    void addFlight(const std::string pDestination, const int pSeats)
    {
        int FlightID = flightsTable.add(pDestination);
        seatTable.add(FlightID, pSeats);
        FlightList.push_back(&FlightID);
        MaxSeatID += pSeats;
    }
    
    int* getRandomPassenger()
    {
        return PassengerList[RandomInt((int)PassengerList.size()-1)];
    }
    
    int* getRandomFlight()
    {
        return FlightList[RandomInt((int)FlightList.size()-1)];
    }
    
    int getRandomSeat()
    {
        return RandomInt(MaxSeatID);
    }
    
    void initializeData()
    {
        // inserts a new flight into the flight table / data structure and stores the id in the mFlightList
        addFlight("Tokio", 2);
        addFlight("New York", 3);
        addFlight("Berlin", 10);
        
        PassengerList.push_back(passengerTable.add("Eva"));
        PassengerList.push_back(passengerTable.add("Elvis"));
        PassengerList.push_back(passengerTable.add("Johanna"));
        
        reservationTable.add(getRandomFlight(), seatTable.getSeat(getRandomSeat()), getRandomPassenger());
    }
    
    void removeReservation()
    {
        // reservationTable.remove(BerlinID, pIDElvis)
        reservationTable.remove();
    }
    
    void getBookedFlights()
    {
        reservationTable.getBookedFlights();
        //reservationTable.getBookedFlights(pIDEva);
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
        transactionHandler.addTransaction(removeReservation);
        transactionHandler.addTransaction(getBookedFlights);
        transactionHandler.addTransaction(getReservationSum);
        transactionHandler.addTransaction(bookFlight);
    }

}

#endif