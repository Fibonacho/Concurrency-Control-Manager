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

class Seats: public Table
{
private:
    struct Seat
    {
        int mSID;  // Seat ID
        int* mFID; // Pointer to flight ID
        
        Seat(int pSID, int* pFID): mSID(pSID), mFID(pFID) {};
        Seat() {};
    };
    
    int* returnSID(StorageUnit* su);
public:
    int add(int &pFID);
    void add(int &pFID, int pCount);
    int* getSeat(int pIndex) const;
    int* getSeat(int* pFID);
    int* getSeat(int pIndex, int* pFID);
    int* getSeat();
    
    Seats(Database& database);
};

#endif
