#include "Passengers.h"
#include "Row.h"
// #include <iostream>
#include "Common.h"
#include "LogFile.h"
#include <string>

BookingDatabase::Passengers::Passengers(Database* database): Table(database)
{
}

BookingDatabase::Passengers::~Passengers()
{
}

int BookingDatabase::Passengers::add(std::string pName)
{
    Passenger passenger;
    passenger.mName = pName;
    passenger.mPID = getNewID();
    Row<Passenger>* row = new Row<Passenger>(this, passenger);
    addRow(row);
    //if (mDataConsoleOutput) std::cout << "Passenger " << row->getData().mPID << " " << pName << std::endl;
    return row->getData().mPID;
}

const BookingDatabase::Passengers::Passenger* BookingDatabase::Passengers::getRandom()
{
    if (mChilds.size() == 0)
        return nullptr;
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* passenger = mChilds[random];
    Row<Passenger>* passengerRow = static_cast<Row<Passenger>*>(passenger);
    if (passengerRow != nullptr)
        return passengerRow->getDataPtr();
    else return nullptr;
}

int BookingDatabase::Passengers::getRandomID()
{
    const Passenger* const data = getRandom();
    return data->mPID;
}

void BookingDatabase::Passengers::display() const
{
    //std::cout << "----------------------------" << std::endl << "Display Passengers: " << std::endl;
    //mLogFile.write("--------------- display passengers: ");
    for(auto passenger: mChilds)
    {
        Row<Passenger>* rowPassenger = static_cast<Row<Passenger>*>(passenger);
       // mLogFile.write(std::to_string(rowPassenger->getData().mPID) + " " + rowPassenger->getData().mName);
    }
   // mLogFile.write("---------------");
}