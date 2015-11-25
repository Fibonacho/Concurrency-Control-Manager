//Database

#include "Database.h"
#include "Flights.h"
#include "Seats.h"
#include "Reservations.h"
#include "Passengers.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

Database::Database()
{
    
    
}

void Database::CreateFlightReservationDB()
{
    Flights flightTable;
    int TokioID = flightTable.add("Tokio");
    int BerlinID = flightTable.add("Berlin");
    
    Seats seatTable;
    seatTable.add(TokioID, 20);
    seatTable.add(BerlinID, 40);
    
    Passengers passengerTable;
    int pIDEva = passengerTable.add("Eva");
    int pIDElvis = passengerTable.add("Elvis");
    int pIDJohanna = passengerTable.add("Johanna");
    
    Reservations reservationTable;
    reservationTable.add(TokioID, 1, pIDEva);
    reservationTable.add(BerlinID, 35, pIDEva);
    reservationTable.add(BerlinID, 38, pIDElvis);
    
    // ----- 2. cancel --------------------------------------------------------------
    reservationTable.remove(BerlinID, pIDElvis);
    //reservationTable.add(TokioID, 2, pIDElvis);
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
    // ------------------------------------------------------------------------------
    
    mTables.push_back(passengerTable);
    mTables.push_back(flightTable);
    mTables.push_back(seatTable);
    mTables.push_back(reservationTable);
}
