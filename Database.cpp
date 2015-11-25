//Database

#include "Database.h"
#include "Flights.h"
#include "Seats.h"
#include "Reservations.h"
#include "Passengers.h"

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
    passengerTable.add("Eva");
    passengerTable.add("Elvis");
    passengerTable.add("Johanna");
    
    Reservations reservationsTable;

    mTables.push_back(passengerTable);
    mTables.push_back(flightTable);
    mTables.push_back(seatTable);
    mTables.push_back(reservationsTable);
}
