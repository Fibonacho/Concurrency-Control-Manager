#include "Passengers.h"
#include "Row.h"
#include <iostream>
#include "Common.h"

BookingDatabase::Passengers::Passengers(Database& database): Table(database)
{
}

int BookingDatabase::Passengers::add(std::string pName)
{
    Row<Passenger>* row = new Row<Passenger>(*this);
    row->mData.mName = pName;
    row->mData.mPID = getNewID();
    addRow(row);
    std::cout << "Passenger " << row->mData.mPID << " " << pName << " at " << &row->mData.mPID << std::endl;
    return row->mData.mPID;
}

BookingDatabase::Passengers::Passenger* BookingDatabase::Passengers::getRandomPassenger() const
{
    if (mChilds.size() == 0)
        return nullptr;
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* passenger = mChilds[random];
    Row<Passenger>* passengerRow = static_cast<Row<Passenger>*>(passenger);
    if (passengerRow != nullptr)
        return &passengerRow->mData;
    else return nullptr;
}

int BookingDatabase::Passengers::getRandomPassengerID() const
{
    Passenger* data = getRandomPassenger();
    if (data == nullptr)
        return -1;
    else
        return data->mPID;
}

void BookingDatabase::Passengers::display() const
{
    std::cout << "----------------------------" << std::endl << "Display Passengers: " << std::endl;
    for(auto passenger: mChilds)
    {
        Row<Passenger>* rowPassenger = static_cast<Row<Passenger>*>(passenger);
        
        std::cout << rowPassenger->mData.mPID << " (" << &(rowPassenger->mData.mPID) << ") "
        << rowPassenger->mData.mName << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}