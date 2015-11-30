#include "Seats.h"
#include "Row.h"
#include "Common.h"
#include <iostream>

BookingDatabase::Seats::Seats(Database& database): Table(database)
{
}

BookingDatabase::Seats::~Seats()
{
    std::cout << "Seats destructur " << std::endl;
}

int BookingDatabase::Seats::returnSID(StorageUnit* su) const
{
    if (su != nullptr)
        return static_cast<Row<Seat>*>(su)->getData().mSID;
    else
        return -1;
}

// get a free seat (randomly chosen) of flight with id pFID 
int BookingDatabase::Seats::getFreeSeat(int pFID)
{
    // flights are stored in a serial order
    return returnSID(mChilds[RandomInt((int)mChilds.size())]);
}

// get a "list" of all seats (a vector object containing int values)
std::vector<int> BookingDatabase::Seats::getSeats(int pFID) const
{
    std::vector<int> list;
    for (auto child: mChilds)
    {
        Row<Seat>* row = static_cast<Row<Seat>*>(child);
        if (row != nullptr)
        {
            if (row->getData().mFID == pFID)
                list.push_back(row->getData().mSID);
        }
    }
    return list;
}

// add a new seat with id pFID to seats table
int BookingDatabase::Seats::add(int pFID) //, int pCount) //pFID as pointer
{
    Seat seat;
    seat.mSID = getNewID();
    seat.mFID = pFID;

    Row<Seat>* row = new Row<Seat>(*this, seat);
    addRow(row);
    std::cout << "Added seat " << row->getData().mSID << " to flight " << pFID << " (" << &pFID << ")" << std::endl;
    return row->getData().mSID;
}

// add pCount seats to flight with id pFID
void BookingDatabase::Seats::add(int pFID, int pCount)
{
    for (int i = 0; i < pCount; i++)
        add(pFID);
}

// get a random seat
BookingDatabase::Seats::Seat BookingDatabase::Seats::getRandomSeat() const
{
    if (mChilds.size() == 0)
        return Seat();
    
    int random = RandomInt((int)mChilds.size());
    StorageUnit* seat = mChilds[random];
    Row<Seat>* seatRow = static_cast<Row<Seat>*>(seat);
    if (seatRow != nullptr)
        return seatRow->getData();
    else return Seat();
}

// get a random seat id
int BookingDatabase::Seats::getRandomSeatID() const
{
    Seat data = getRandomSeat();
    return data.mSID;
}

BookingDatabase::Seats::Seat BookingDatabase::Seats::getRandomSeat(int pFID) const
{
    //TODO
    int random = RandomInt((int)mChilds.size());
    StorageUnit* seat = mChilds[random];
    Row<Seat>* seatRow = static_cast<Row<Seat>*>(seat);
    if (seatRow != nullptr)
        return seatRow->getData();
    else return Seat();
}

