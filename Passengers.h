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
    private:
        struct Passenger
        {
            int mPID;
            std::string mName;
            
            Passenger(): mPID(-1), mName("") {}
        };
    public:
        Passengers(Database& database);
        ~Passengers();
        
        int add(std::string pName);
        Passenger getRandomPassenger() const;
        int getRandomPassengerID() const;
        void display() const;
    };
}

#endif