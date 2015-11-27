#include "Flights.h"
#include <iostream>
#include "Row.h"

BookingDatabase::Flights::Flights(Database& database): Table(database)
{
}

BookingDatabase::Flights::~Flights()
{
}

void BookingDatabase::Flights::display()
{
    for(auto flight: mChilds)
    {
        std::cout << static_cast<Row<Flight>>(*flight).mData.mID << " "
                  << static_cast<Row<Flight>>(*flight).mData.mDestination << std::endl;
    }
}

int BookingDatabase::Flights::add(std::string pDestination)
{
    // first check if the flight has already been inserted
    // add a value to the linked list
    Row<Flight>* row = new Row<Flight>(*this);
    row->mData.mID = getNewID();
    row->mData.mDestination = pDestination;
    addRow(row);
    return row->mData.mID;
}

