//Database

#include "Database.h"
#include "Flights.h"
#include "Seats.h"
#include "Reservations.h"
#include "Passengers.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Database::Database(): StorageUnit(nullptr) //this is the root = the database
{
    
    
}

void Database::AddTable(StorageUnit& table)
{
    //StorageUnit storageUnitTable = new StorageUnit(this);
    mChilds.push_back(&table);
}

/*void Database::CreateBookingDB()
{
 
    Seats seatTable;
    seatTable.add(TokioID, 20);
    seatTable.add(BerlinID, 40);
 
    
    // ------------------------------------------------------------------------------
    
    // ----- 3. list flights --------------------------------------------------------
    std::list<int> a = reservationTable.getFlightIDs(2);
    // ------------------------------------------------------------------------------
    
    // ----- 4. get reservation sum -------------------------------------------------
    std::cout << reservationTable.count() << std::endl;
    // ------------------------------------------------------------------------------
    
    // ----- 1. book transaction ----------------------------------------------------
    std::list<int> slist = seatTable.getSeatList(BerlinID);
    std::list<int> freeSeats = reservationTable.getFreeSeats(slist);
    srand(time(NULL));
    int randomValue = rand() % freeSeats.size();         // v1 in the range 0 to 99
    std::list<int>::iterator i = freeSeats.begin();
    std::advance(i, randomValue);
    reservationTable.book(1, 1, *i);
    // ---------------------------------------------------------------------------  
    
    mTables.push_back(passengerTable);
    mTables.push_back(flightTable);
    mTables.push_back(seatTable);
    mTables.push_back(reservationTable);
}*/
