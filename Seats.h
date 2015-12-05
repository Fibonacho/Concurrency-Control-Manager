//  ---------------------------------------------------
//  Seats:
//  - Seats Table
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef SEATS_H
#define SEATS_H

#include "Table.h"
#include <list>
#include "Database.h"

namespace BookingDatabase {
    class Seats: public Table
    {
    private:
        struct Seat
        {
            int mSID;  // Seat ID
            int mFID;  // Flight ID
            
            Seat(int pSID, int pFID): mSID(pSID), mFID(pFID) {};
            Seat(): mSID(-1), mFID(-1) {};
        };
    
        int returnSID(StorageUnit* su) const;
        // add a new seat with id pFID to seats table
        int add(int pFID);
    public:
        // add pCount seats to flight with id pFID
        void add(int pFID, int pCount);
        // get a free seat (randomly chosen) of flight with id pFID
        int getFreeSeat(int pFID);
        std::vector<int> getSeats(int pFID) const;
        // get a random seat
        Seat getRandomSeat() const;
        Seat getRandomSeat(int pFID) const;
        // get a random seat id
        int getRandomSeatID() const;

        Seats(Database* database);
        virtual ~Seats();
    };
}

#endif
