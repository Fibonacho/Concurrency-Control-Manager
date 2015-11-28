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
        
        std::cout << rowFlight->mData.mID << " (" << &(rowFlight->mData.mID) << ") "
                  << rowFlight->mData.mDestination << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

BookingDatabase::Flights::Flight* BookingDatabase::Flights::getRandomFlight() const
{
    if (mChilds.size() == 0)
        return nullptr;
    
    int random = RandomInt((int)mChilds.size()-1);
    StorageUnit* flight = mChilds[random];
    Row<Flight>* flightrow = static_cast<Row<Flight>*>(flight);
    if (flightrow != nullptr)
        return &flightrow->mData;
    else return nullptr;
}

int BookingDatabase::Flights::getRandomFlightID() const
{
    Flight* data = getRandomFlight();
    if (data == nullptr)
        return -1;
    else
        return data->mID;
}

int BookingDatabase::Flights::add(std::string pDestination)
{
    // first check if the flight has already been inserted
    // add a value to the linked list
    Row<Flight>* row = new Row<Flight>(*this);
    row->mData.mID = getNewID();
    std::cout << pDestination << " ID stored at " << &row->mData.mID << std::endl;
    row->mData.mDestination = pDestination;
    addRow(row);
    return row->mData.mID;
}

