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
        
        passengerTable.mLock.Exclusive();
        //std::cout << database.() << std::endl;
        if (db.allowExclusiveLock())
            std::cout << "can be locked" << std::endl;
        else
            std::cout << "can't be locked" << std::endl;
        //test different / all the cases of locking
        
        assert(!db.allowExclusiveLock());
        // assert(false); this should only happen if there is a programming error
        
    }
}

#endif