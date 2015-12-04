//  ---------------------------------------------------
//  UnitTestLocking:
//  -
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef UNITTESTLOCKING_H
#define UNITTESTLOCKING_H


#include "Database.h"
#include "Flights.h"
#include "Passengers.h"
#include "Seats.h"
#include "Reservations.h"
#include <assert.h>
    
namespace UnitTestLocking {
    // creates database
    Database db;
    // creates tables
    BookingDatabase::Flights flightsTable(db);
    BookingDatabase::Passengers passengerTable(db);
    BookingDatabase::Reservations reservationTable(db);
    BookingDatabase::Seats seatTable(db);
    
    void test()
    {
        db.AddTable(passengerTable); //this should be done in the constructor of the database
        db.AddTable(flightsTable);
        db.AddTable(reservationTable);
        db.AddTable(seatTable);
        
        // 1 //////////////////////////////////////////////////////////////////
        // lock (exclusively) and check if another exclusive lock is allowed
        passengerTable.mLock.Exclusive();
        if (db.allowExclusiveLock())
            std::cout << "db can be locked (exclusively)" << std::endl;
        else
            std::cout << "db can't be locked (exclusively)" << std::endl;
        assert(!db.allowExclusiveLock());
        
        // 2 //////////////////////////////////////////////////////////////////
        // release (exclusive) lock and check if unlocked
        db.mLock.Release();
        if (db.mLock.isUnlocked())
            std::cout << "db is unlocked" << std::endl;
        else
            std::cout << "db is not unlocked" << std::endl;
        assert(db.mLock.isUnlocked());

        // 3 //////////////////////////////////////////////////////////////////
        // lock (shared) and check if there's a shared lock
        reservationTable.mLock.Shared();
        if (reservationTable.mLock.isSharedLocked())
            std::cout << "db is locked (shared)" << std::endl;
        else
            std::cout << "db is not locked (shared)" << std::endl;
        assert(reservationTable.mLock.isSharedLocked());
    }
}

#endif