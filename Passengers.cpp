#include "Passengers.h"
#include "Row.h"
#include <iostream>

BookingDatabase::Passengers::Passengers(Database& database): Table(database)
{
}

int* BookingDatabase::Passengers::add(std::string pName)
{
    Row<Passenger>* row = new Row<Passenger>(*this);
    row->mData.mName = pName;
    row->mData.mPID = getNewID();
    addRow(row);
    std::cout << "Passenger " << row->mData.mPID << " " << pName << " at " << &row->mData.mPID << std::endl;
    return &row->mData.mPID;
}

void BookingDatabase::Passengers::display()
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