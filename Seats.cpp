#include "Seats.h"
#include "Row.h"
#include "Common.h"
#include <iostream>

BookingDatabase::Seats::Seats(Database& database): Table(database)
{
}

int BookingDatabase::Seats::returnSID(StorageUnit* su) const
{
    if (su != nullptr)
        return static_cast<Row<Seat>*>(su)->mData.mSID;
    else
        return -1;
}

int BookingDatabase::Seats::getFreeSeat(int pFID) //get seat of flight
{
    // flights are stored in a serial order
    return returnSID(mChilds[RandomInt((int)mChilds.size())]);
}

std::vector<int> BookingDatabase::Seats::getSeats(int pFID) const
{
    std::vector<int> list;
    for (auto child: mChilds)
    {
        Row<Seat>* row = static_cast<Row<Seat>*>(child);
        if (row != nullptr)
        {
            if (row->mData.mFID == pFID)
                list.push_back(row->mData.mSID);
        }
    }
    return list;
}

int BookingDatabase::Seats::add(int pFID) //, int pCount) //pFID as pointer
{
    Row<Seat>* row = new Row<Seat>(*this);
    row->mData.mSID = getNewID();
    row->mData.mFID = pFID;
    addRow(row);
    std::cout << "Added seat " << row->mData.mSID << " (" << &row->mData.mSID << ") to flight " << pFID << " (" << &pFID << ")" << std::endl;
    return row->mData.mSID;
}

void BookingDatabase::Seats::add(int pFID, int pCount)
{
    for (int i = 0; i < pCount; i++)
        add(pFID);
}

BookingDatabase::Seats::Seat* BookingDatabase::Seats::getRandomSeat() const
{
    if (mChilds.size() == 0)
        return nullptr;
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* seat = mChilds[random];
    Row<Seat>* seatRow = static_cast<Row<Seat>*>(seat);
    if (seatRow != nullptr)
        return &seatRow->mData;
    else return nullptr;
}

int BookingDatabase::Seats::getRandomSeatID() const
{
    Seat* data = getRandomSeat();
    if (data == nullptr)
        return -1;
    else
        return data->mSID;
}

BookingDatabase::Seats::Seat* BookingDatabase::Seats::getRandomSeat(int pFID) const
{
    //TODO
    int random = RandomInt((int)mChilds.size());
    StorageUnit* seat = mChilds[random];
    Row<Seat>* seatRow = static_cast<Row<Seat>*>(seat);
    if (seatRow != nullptr)
        return &seatRow->mData;
    else return nullptr;
}

