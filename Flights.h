//  ---------------------------------------------------
//  Flights:
//  - Flight Table
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
        //stores a flight item, which is a row
        struct Flight
        {
            int mID;
            std::string mDestination;
        };
    public:
        int add(std::string pDestination);
        void display();
    
        Flights(Database& database);
        ~Flights();
    };
}

#endif