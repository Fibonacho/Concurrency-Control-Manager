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
    std::vector<int> FlightSeats;
    std::vector<int*> PassengerList;
    int MaxSeatID = 0;
    
    void addFlight(std::string pDestination, int pSeats)
    {
        int* FlightID = flightsTable.add(pDestination);
        FlightList.push_back(FlightID);
        FlightSeats.push_back(pSeats);
        MaxSeatID += pSeats;
        seatTable.add(FlightID, pSeats);
    }
    
    int* getRandomPassenger()
    {
        int random = RandomInt((int)PassengerList.size()-1);
        return PassengerList[random];
    }
    
    int* getRandomFlight()
    {
        int random = RandomInt((int)FlightList.size()-1);
        return FlightList[random];
    }
    
    int getRandomSeat()
    {
        return RandomInt(MaxSeatID)+1;
    }
    
    void initializeData()
    {
        // inserts a new flight into the flight table / data structure and stores the id in the mFlightList
        addFlight("Tokio", 1);
        addFlight("New York", 1);
        addFlight("Berlin", 2);
        flightsTable.display();
        
        PassengerList.push_back(passengerTable.add("Eva"));
        PassengerList.push_back(passengerTable.add("Elvis"));
        PassengerList.push_back(passengerTable.add("Johanna"));
        passengerTable.display();
        
        reservationTable.mFlightList = &FlightList;
        reservationTable.mPassengerList = &PassengerList;
        
        reservationTable.add(FlightList[0], seatTable.getSeat(getRandomSeat()), PassengerList[2]);
        reservationTable.add(getRandomFlight(), seatTable.getSeat(getRandomSeat()), getRandomPassenger());
        reservationTable.display();
    }
    
    void removeReservation()
    {
        reservationTable.remove(*getRandomFlight(), *getRandomPassenger());
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
        transactionHandler.addTransaction(getReservationSum);
        transactionHandler.addTransaction(removeReservation);
        transactionHandler.addTransaction(getBookedFlights);
        transactionHandler.addTransaction(bookFlight);
    }
}

#endif