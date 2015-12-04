#include "Flights.h"
#include <iostream>
#include "Row.h"
#include "Common.h"

BookingDatabase::Flights::Flights(Database& database): Table(database)
{
}

BookingDatabase::Flights::~Flights()
{
    std::cout << "Flights destructur " << std::endl;
}

void BookingDatabase::Flights::display() const
{
    std::cout << "----------------------------" << std::endl << "Display Flights: " << std::endl;
    for(auto flight: mChilds)
    {
        Row<Flight>* rowFlight = static_cast<Row<Flight>*>(flight);
        std::cout << rowFlight->getData().mID << " " << rowFlight->getData().mDestination << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

BookingDatabase::Flights::Flight BookingDatabase::Flights::getRandomFlight() const
{
    if (mChilds.size() == 0)
        return Flight();
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* flight = mChilds[random];
    Row<Flight>* flightrow = static_cast<Row<Flight>*>(flight);
    if (flightrow != nullptr)
        return flightrow->getData();
    else return Flight();
}

int BookingDatabase::Flights::getRandomFlightID() const
{
    Flight data = getRandomFlight();
    return data.mID;
}

int BookingDatabase::Flights::add(std::string pDestination)
{
    // first check if the flight has already been inserted
    // add a value to the linked list
    Flight flight(getNewID(), pDestination);
    Row<Flight>* row = new Row<Flight>(*this, flight);
    std::cout << pDestination << " ID stored." << std::endl;
    addRow(row);
    return row->getData().mID;
}
