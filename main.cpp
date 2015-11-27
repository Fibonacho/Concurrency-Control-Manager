//  ---------------------------------------------------
//  main.cpp
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#include <iostream>
#include "Database.h"
#include "Flights.h"
#include "Passengers.h"
#include "Seats.h"
#include "Reservations.h"
#include "TransactionHandler.h"

int main(int argc, const char * argv[]) {
    std::vector<int> mFlightID;
    
    Database database;
    Flights flightsTable(database); //link reservation and seat table?!
    int TokioID = flightsTable.add("Tokio");
    int BerlinID = flightsTable.add("Berlin");
    mFlightID.push_back(TokioID);
    mFlightID.push_back(BerlinID);
    
    Passengers passengerTable(database);
    int pIDEva = passengerTable.add("Eva");
    int pIDElvis = passengerTable.add("Elvis");
    int pIDJohanna = passengerTable.add("Johanna");
    
    Seats seatTable(database);
    seatTable.add(TokioID, 10);
    seatTable.add(BerlinID, 20);
    
    Reservations reservationTable(database);
    reservationTable.add(TokioID, seatTable.getSeat(10), pIDEva);
    
    // ----- 2. cancel --------------------------------------------------------------
    // reservationTable.remove(BerlinID, pIDElvis);
    bool removed = reservationTable.remove(BerlinID, pIDElvis);

    //reservationTable.add(BerlinID, seatTable.getSeat(30), pIDEva);
    //reservationTable.add(BerlinID, seatTable.getSeat(1), pIDElvis);
    
    TransactionHandler transactionHandler(database);
    
    std::cin.get();
    return 0;
}
