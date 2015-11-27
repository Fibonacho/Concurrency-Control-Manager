//Database

#ifndef BOOKINGDATABASE_H
#define BOOKINGDATABASE_H

#include "Database.h"
#include "Flights.h"
#include "Passengers.h"
#include "Seats.h"
#include "Reservations.h"
#include "TransactionHandler.h"

namespace BookingDatabase {
    Database database;
    Flights flightsTable(database); //link reservation and seat table?!
    Passengers passengerTable(database);
    Reservations reservationTable(database);
    Seats seatTable(database);
    TransactionHandler transactionHandler(database);
    
    std::vector<int> mFlightList;
    std::vector<int> mPassengerList;
    
    void initializeData()
    {
        // mList!
        int TokioID = flightsTable.add("Tokio");
        int BerlinID = flightsTable.add("Berlin");
        mFlightList.push_back(TokioID);
        mFlightList.push_back(BerlinID);
        
        //Passengers passengerTable(database);
        int pIDEva = passengerTable.add("Eva");
        int pIDElvis = passengerTable.add("Elvis");
        int pIDJohanna = passengerTable.add("Johanna");
        
        seatTable.add(TokioID, 10);
        seatTable.add(BerlinID, 20);
        
        //add comments
        reservationTable.add(BerlinID, seatTable.getSeat(10), pIDEva);
        reservationTable.add(BerlinID, seatTable.getSeat(10), pIDEva);
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