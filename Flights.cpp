#include "Flights.h"
//#include <iostream>
#include "Row.h"
#include "Common.h"
//#include "LogFile.h"
#include <string>

BookingDatabase::Flights::Flights(Database* database): Table(database) //, mLogFile(pLogFile)  LogFile* pLogFile
{
}

BookingDatabase::Flights::~Flights()
{
}

void BookingDatabase::Flights::display() const
{
    //mLogFile->write("---------------------------- Display Flights: ");
    for(auto flight: mChilds)
    {
        Row<Flight>* rowFlight = static_cast<Row<Flight>*>(flight);
    //    mLogFile->write(std::to_string(rowFlight->getData().mID) + " " + rowFlight->getData().mDestination);
    }
    //mLogFile->write("----------------------------");
}

const BookingDatabase::Flights::Flight* BookingDatabase::Flights::getRandom() const
{
    if (mChilds.size() == 0)
        return nullptr;
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* flight = mChilds[random];
    Row<Flight>* flightrow = static_cast<Row<Flight>*>(flight);
    if (flightrow != nullptr)
        return flightrow->getDataPtr();
    else return nullptr;
}

int BookingDatabase::Flights::getRandomID() const
{
    const Flight* const data = getRandom();
    return data->mID;
}

int BookingDatabase::Flights::add(std::string pDestination)
{
    // first check if the flight has already been inserted
    // add a value to the linked list
    Flight flight(getNewID(), pDestination);
    Row<Flight>* row = new Row<Flight>(this, flight);
    //if (mDataConsoleOutput)
    //    mLogFile.write("Flight to " + pDestination + " is stored.");
    addRow(row);
    return row->getData().mID;
}
