#include "Passengers.h"
#include "Row.h"
#include <iostream>
#include "Common.h"

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
    if (mDataConsoleOutput)
        std::cout << "Passenger " << row->getData().mPID << " " << pName << std::endl;
    return row->getData().mPID;
}

BookingDatabase::Passengers::Passenger BookingDatabase::Passengers::getRandomPassenger() const
{
    if (mChilds.size() == 0)
        return Passenger();
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* passenger = mChilds[random];
    Row<Passenger>* passengerRow = static_cast<Row<Passenger>*>(passenger);
    if (passengerRow != nullptr)
        return passengerRow->getData();
    else return Passenger();
}

int BookingDatabase::Passengers::getRandomPassengerID() const
{
    Passenger data = getRandomPassenger();
    return data.mPID;
}

void BookingDatabase::Passengers::display() const
{
    std::cout << "----------------------------" << std::endl << "Display Passengers: " << std::endl;
    for(auto passenger: mChilds)
    {
        Row<Passenger>* rowPassenger = static_cast<Row<Passenger>*>(passenger);
        std::cout << rowPassenger->getData().mPID << " " << rowPassenger->getData().mName << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}