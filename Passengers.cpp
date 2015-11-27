#include "Passengers.h"
#include "Row.h"

BookingDatabase::Passengers::Passengers(Database& database): Table(database)
{
}

int* BookingDatabase::Passengers::add(std::string pName)
{
    Row<Passenger>* row = new Row<Passenger>(*this);

    row->mData.mName = pName;
    row->mData.mPID = getNewID();
    addRow(row);
    return &row->mData.mPID;
}
