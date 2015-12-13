//  ---------------------------------------------------
//  Passengers:
//  - Passengers Table
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef PASSENGERS_H
#define PASSENGERS_H

#include "Table.h"
#include <string>
#include "Database.h"

namespace BookingDatabase {
    class Passengers: public Table
    {
    public:
        struct Passenger
        {
            int mPID;
            std::string mName;
            
            Passenger(): mPID(-1), mName("") {}
        };
        Passengers(Database* database);
        virtual ~Passengers();
        // add a passenger (row) to the passenger table
        int add(std::string pName);
        // get a random passenger from the table
        Passenger* getRandom();
        // get a random passenger id by calling getRandomPassenger() and accessing it's ID
        int getRandomID();
        // display passengers, i.e. print content of passenger table to console
        void display() const;
    };
}

#endif