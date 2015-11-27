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
#include "TransactionHandler.h"

int main(int argc, const char * argv[]) {
    Database database;
    Flights flightsTable(database);
    int TokioID = flightsTable.add("Tokio");
    int BerlinID = flightsTable.add("Berlin");
    
    Passengers passengerTable(database);
    int pIDEva = passengerTable.add("Eva");
    int pIDElvis = passengerTable.add("Elvis");
    int pIDJohanna = passengerTable.add("Johanna");
    
    //database.CreateBookingDB();
    
    TransactionHandler transactionHandler(database);
    
    std::cin.get();
    return 0;
}
