//  ---------------------------------------------------
//  Flights:
//  - Flights Table 
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef FLIGHTS_H
#define FLIGHTS_H

#include "Table.h"
#include "Database.h"
#include <string>
#include "Database.h"

namespace BookingDatabase {
    class Flights: public Table
    {
    private:
        struct Flight
        {
            int mID;
            std::string mDestination;
            
            Flight(): mID(-1), mDestination("") {}
            Flight(int pID, std::string pDestination): mID(pID), mDestination(pDestination) {}
        };
    public:
        // add a flight (row) to the flight table
        int add(std::string pDestination);
        // display flights, i.e. print content of flight table to console
        void display() const;
        // get a random flight from the table
        Flight getRandomFlight() const;
        // get a random flight id by calling getRandomFlight() and accessing it's ID
        int getRandomFlightID() const;
        // get number of flights
        long count();

        Flights(Database& database);
        ~Flights();
    };
}

#endif