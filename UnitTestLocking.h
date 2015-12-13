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
    Database db(nullptr);
    // create tables
    BookingDatabase::Flights flights(&db);
    BookingDatabase::Passengers passengers(&db);
    BookingDatabase::Reservations reservations(&db);
    BookingDatabase::Seats seats(&db);
    
    void test()
    {
        std::cout << "START Unit Test ------------------------ " << std::endl;
        // lock an object in exclusive mode and check if it could be locked again (which should of course not be possible)
        // and after check for shared locks (shared / shared) - where it is possible to lock twice
        
        // first for the database
        db.ForceLockExclusive();
        assert(!db.ExclusiveLockable());
        assert(!db.SharedLockable());
        db.ReleaseLocks();
        // now with shared:
        db.ForceLockShared();
        assert(!db.ExclusiveLockable());
        assert(db.SharedLockable());
        db.ReleaseLocks();
        
        // then for the passenger table
        passengers.ForceLockExclusive();
        assert(!passengers.ExclusiveLockable());
        assert(!passengers.SharedLockable());
        passengers.ReleaseLocks();
        // now with shared:
        passengers.ForceLockShared();
        assert(!passengers.ExclusiveLockable());
        assert(passengers.SharedLockable());
        passengers.ReleaseLocks();
        
        // and later for the rows of a flight
        passengers.add("Test");
        // get the row storage unit object
        StorageUnit* FirstPassenger = passengers.getFirstChild(); //Row<Passenger> object
        FirstPassenger->ForceLockExclusive();
        assert(!FirstPassenger->ExclusiveLockable());
        assert(!FirstPassenger->SharedLockable());
        FirstPassenger->ReleaseLocks();
        
        // now with shared:
        FirstPassenger->ForceLockShared();
        assert(!FirstPassenger->ExclusiveLockable());
        assert(FirstPassenger->SharedLockable());
        FirstPassenger->ReleaseLocks();
        
        // lock a table of the database exclusively and check if the database can be locked (which should not be the case)
        passengers.ForceLockExclusive();
        assert(!db.ExclusiveLockable());
        // relase the lock on the passanger table
        passengers.ReleaseLocks();
        // check if the database now can exclusively be locked (which should be the case - since no child is locked anymore)
        assert(db.ExclusiveLockable());
        
        // now lock two tables / childs of the database and check if the database is still lockable
        passengers.ForceLockExclusive();
        seats.ForceLockShared();
        flights.ForceLockExclusive();
        // should not allowed to be locked
        assert(!db.ExclusiveLockable());
        seats.ReleaseLocks();
        assert(!db.ExclusiveLockable());
        flights.ReleaseLocks();
        assert(!db.ExclusiveLockable());
        passengers.ReleaseLocks();
        // if all table locks get released it should be lockable
        assert(db.ExclusiveLockable());
        
        // lock the passenger table in shared mode
        passengers.ForceLockShared();
        // should be fine to lock the passenger table or the database in shared mode
        assert(passengers.SharedLockable());
        assert(db.SharedLockable());
        
        // but any table is locked exclusively
        flights.ForceLockExclusive();
        // it is not possible anymore to lock the database in shared mode
        assert(!db.SharedLockable());
        // Release all locks again
        flights.ReleaseLocks();
        // now it is... (only passengers is locked in shared)
        assert(db.SharedLockable());
        // release the shared lock of passengers
        passengers.ReleaseLocks();
        // now nothing is locked is should be even more clear
        assert(db.SharedLockable());

        // if the db is locked in exclusive locked NO table can be locked in ANY mode
        db.ForceLockExclusive();
        assert(!flights.ExclusiveLockable());
        assert(!flights.SharedLockable());
        assert(!passengers.ExclusiveLockable());
        assert(!passengers.SharedLockable());
        assert(!seats.ExclusiveLockable());
        assert(!seats.SharedLockable());
        assert(!passengers.ExclusiveLockable());
        assert(!passengers.SharedLockable());
        db.ReleaseLocks();
        
        // now check if this also works for rows:
        // add a row to the table flights
        flights.add("Perth");
        // get the row storage unit object
        StorageUnit* FirstFlight = flights.getFirstChild(); //Row<Flight> object
        
        // lock the database in exclusive mode
        db.ForceLockExclusive();
        // check if the row can then be locked in shared mode (which should not be possible)
        assert(!FirstFlight->SharedLockable());
        // release the lock on the database
        db.ReleaseLocks();
        // now it's possible
        assert(FirstFlight->SharedLockable());
        
        // then lock the row in exclusive mode
        FirstFlight->ForceLockExclusive();
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
        FirstFlight->ReleaseLocks();
        // it should be possible to lock the flights table in shared mode or any other
        assert(flights.SharedLockable());
        assert(flights.ExclusiveLockable());
        FirstFlight->ReleaseLocks();
        std::cout << "END Unit Test ------------------------ " << std::endl;
    }
}

#endif