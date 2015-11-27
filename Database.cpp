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

//gets automatically called by the table class
void Database::AddTable(StorageUnit& table)
{
    mChilds.push_back(&table);
}

/*void Database::CreateBookingDB()
{
    // ----- 1. book transaction ----------------------------------------------------
    std::list<int> slist = seatTable.getSeatList(BerlinID);
    std::list<int> freeSeats = reservationTable.getFreeSeats(slist);
    srand(time(NULL));
    int randomValue = rand() % freeSeats.size();         // v1 in the range 0 to 99
    std::list<int>::iterator i = freeSeats.begin();
    std::advance(i, randomValue);
    reservationTable.book(1, 1, *i);
}*/
