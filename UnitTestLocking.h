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
    // create database
    Database db;
    // create tables
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
        // lock (exclusively) and check if another exclusive lock is allowed //
        std::cout << "TEST  1:   ";
        passengerTable.mLock.Exclusive();
        if (db.allowExclusiveLock())
            std::cout << "db can be locked again (exclusively)" << std::endl;
        else
            std::cout << "db does not allow another (exclusive) lock" << std::endl;
        assert(!db.allowExclusiveLock());

        // 2 //////////////////////////////////////////////////////////////////
        // release (exclusive) lock and check if unlocked /////////////////////
        std::cout << "TEST  2:   ";
        db.mLock.Release();
        if (db.mLock.isUnlocked())
            std::cout << "db is unlocked" << std::endl;
        else
            std::cout << "db is not unlocked" << std::endl;
        assert(db.mLock.isUnlocked());

        // 3 //////////////////////////////////////////////////////////////////
        // lock (shared) and check if there's a shared lock ///////////////////
        std::cout << "TEST  3:   ";
        reservationTable.mLock.Shared();
        if (reservationTable.mLock.isSharedLocked())
            std::cout << "db is locked (shared)" << std::endl;
        else
            std::cout << "db is not locked (shared)" << std::endl;
        assert(reservationTable.mLock.isSharedLocked());

        // 4 //////////////////////////////////////////////////////////////////
        // lock (shared) and check if another shared lock is allowed //////////
        std::cout << "TEST  4:   ";
        passengerTable.mLock.Shared();
        if (db.allowSharedLock())
            std::cout << "db allows further lock (shared)" << std::endl;
        else
            std::cout << "db does not allow further lock (shared)" << std::endl;
        assert(db.allowSharedLock());

        // 5 //////////////////////////////////////////////////////////////////
        // check if there are NOT more seats than flights /////////////////////
        std::cout << "TEST  5:   ";
        long seatCount = seatTable.getRowCount();
        long flightCount = flightsTable.getRowCount();
        if (seatCount >= flightCount)
            std::cout << "there are not more flights than seats" << std::endl;
        else
            std::cout << "there are more flights than seats" << std::endl;
        assert(seatCount >= flightCount);

        // 6 //////////////////////////////////////////////////////////////////
        // check: reservations > 0 => passengers > 0 //////////////////////////
        std::cout << "TEST  6:   ";
        long passengerCount = passengerTable.getRowCount();
        long reservationCount = reservationTable.getRowCount();
        if (reservationCount > 0 && passengerCount > 0)
            std::cout << "number of reservations AND number of passengers > 0" << std::endl;
        else if (reservationCount > 0)
            std::cout << "number of reservations > 0 BUT number of passengers not" << std::endl;
        else
            std::cout << "number of reservations <= 0" << std::endl;
        assert((reservationCount > 0 && passengerCount > 0) || reservationCount <= 0);

        // 7 //////////////////////////////////////////////////////////////////
        // lock parent (exclusively) and check if child is also locked ////////
        std::cout << "TEST  7:   ";
        db.mLock.Exclusive();
        if (flightsTable.mLock.isExclusiveLocked())
            std::cout << "db is locked exclusively, table is also" << std::endl;
        else
            std::cout << "db is locked exclusively, table is not" << std::endl;
        //assert(flightsTable.mLock.isExclusiveLocked());
    }
}

#endif