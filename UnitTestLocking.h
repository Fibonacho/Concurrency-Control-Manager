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
    BookingDatabase::Flights flights(&db);
    BookingDatabase::Passengers passengers(&db);
    BookingDatabase::Reservations reservations(&db);
    BookingDatabase::Seats seats(&db);
    
    void test()
    {
        // lock an table of the database exclusively and check if the database can be locked (which should not be the case)
        passengers.mLock.Exclusive();
        assert(!db.ExclusiveLockable());
        // relase the lock on the passanger table
        passengers.mLock.Release();
        // check if the database now can exclusively be locked (which should be the case - since no child is locked anymore)
        assert(db.ExclusiveLockable());
        
        // now lock two tables / childs of the database and check if the database is still lockable
        passengers.mLock.Exclusive();
        seats.mLock.Shared();
        flights.mLock.Exclusive();
        // should not allowed to be locked
        assert(!db.ExclusiveLockable());
        seats.mLock.Release();
        assert(!db.ExclusiveLockable());
        flights.mLock.Release();
        assert(!db.ExclusiveLockable());
        passengers.mLock.Release();
        // if all table locks get released it should be lockable
        assert(db.ExclusiveLockable());
        
        // lock the passenger table in shared mode
        passengers.mLock.Shared();
        // should be fine to lock the passenger table or the database in shared mode
        assert(passengers.SharedLockable());
        assert(db.SharedLockable());
        
        // but any table is locked exclusively
        flights.mLock.Exclusive();
        // it is not possible anymore to lock the database in shared mode
        assert(!db.SharedLockable());
        // Release all locks again
        flights.mLock.Release();
        // now it is... (only passengers is locked in shared)
        assert(db.SharedLockable());
        // release the shared lock of passengers
        passengers.mLock.Release();
        // now nothing is locked is should be even more clear
        assert(db.SharedLockable());

        // if the db is locked in exclusive locked NO table can be locked in ANY mode
        db.mLock.Exclusive();
        assert(!flights.ExclusiveLockable());
        assert(!flights.SharedLockable());
        assert(!passengers.ExclusiveLockable());
        assert(!passengers.SharedLockable());
        assert(!seats.ExclusiveLockable());
        assert(!seats.SharedLockable());
        assert(!passengers.ExclusiveLockable());
        assert(!passengers.SharedLockable());
        db.mLock.Release();
        
        // now check if this that also works for rows ...
        // add a row to the table flights
        flights.add("Perth");
        // get the row storage unit object
        StorageUnit* FirstFlight = flights.getFirstChild(); //Row<Flight> object
        
        // lock the database in exclusive mode
        db.mLock.Exclusive();
        // check if the row can then be locked in shared mode (which should not be possible)
        assert(!FirstFlight->SharedLockable());
        // release the lock on the database
        db.mLock.Release();
        
        // and then lock the row in exclusive mode
        FirstFlight->mLock.Exclusive();
        // if row is locked in exclusive mode neither the flight table can be locked in any mode ...
        assert(!flights.SharedLockable());
        assert(!flights.ExclusiveLockable());
        // ... nor the database itself
        assert(!db.SharedLockable());
        assert(!db.ExclusiveLockable());
        // but lock the passenger, seat or reservation table is fine since the row was a flight row
        assert(passengers.ExclusiveLockable());
        assert(seats.ExclusiveLockable());
        assert(reservations.ExclusiveLockable());
        // relase the row level lock
        FirstFlight->mLock.Release();
        // not it should be possible to lock the flights table in shared mode or any other
        assert(flights.SharedLockable());
        assert(flights.ExclusiveLockable());
        FirstFlight->mLock.Release();
        
        // 5 //////////////////////////////////////////////////////////////////
        // check if there are NOT more seats than flights /////////////////////
        std::cout << "TEST  5:   ";
        long seatCount = seats.getRowCount();
        long flightCount = flights.getRowCount();
        if (seatCount >= flightCount)
            std::cout << "there are not more flights than seats" << std::endl;
        else
            std::cout << "there are more flights than seats" << std::endl;
        assert(seatCount >= flightCount);

        // 6 //////////////////////////////////////////////////////////////////
        // check: reservations > 0 => passengers > 0 //////////////////////////
        std::cout << "TEST  6:   ";
        long passengerCount = passengers.getRowCount();
        long reservationCount = reservations.getRowCount();
        if (reservationCount > 0 && passengerCount > 0)
            std::cout << "number of reservations AND number of passengers > 0" << std::endl;
        else if (reservationCount > 0)
            std::cout << "number of reservations > 0 BUT number of passengers not" << std::endl;
        else
            std::cout << "number of reservations <= 0" << std::endl;
        assert((reservationCount > 0 && passengerCount > 0) || reservationCount <= 0);


    }
}

#endif