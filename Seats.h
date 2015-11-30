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
        int add(int pFID);
    public:
        void add(int pFID, int pCount);
        int getFreeSeat(int pFID);
        std::vector<int> getSeats(int pFID) const;
        
        Seat getRandomSeat() const;
        Seat getRandomSeat(int pFID) const;
        int getRandomSeatID() const;

        Seats(Database& database);
        ~Seats();
    };
}

#endif
