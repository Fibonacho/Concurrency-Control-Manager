#include "Seats.h"
#include "Row.h"
#include "Common.h"
#include <iostream>

BookingDatabase::Seats::Seats(Database& database): Table(database)
{
}

/*bool Seats::add(Seat pSeat)
{
    //is id already in the data structure
    mList.pushBack(pSeat);
    return true;
}*/

/*bool Seats::remove(int id)
{
    //remove an item from the linked list
    return true;
}*/

/*void Seats::initialize()
{
    //function initialize
    Seats::Seat seat;
    seat.sID = 2; //getNewID();
    seat.fID = 3; //getRandomfID(); we need a connection to the flight "table"
    //add(passeger);
    //more ...
}
*/

int BookingDatabase::Seats::getSeat(int pIndex) const
{
    StorageUnit* su = mChilds[pIndex];
    return returnSID(su);
}

int BookingDatabase::Seats::returnSID(StorageUnit* su) const
{
    if (su != nullptr)
        return static_cast<Row<Seat>*>(su)->mData.mSID;
    else
        return -1;
}

int BookingDatabase::Seats::getSeat(int pFID) //get seat of flight
{
    //check for pFID
    //while ()
    return returnSID(mChilds[RandomInt((int)mChilds.size())]);
}

int BookingDatabase::Seats::getSeat()
{
    //returns a random seat
    return returnSID(mChilds[RandomInt((int)mChilds.size())]);
}

int BookingDatabase::Seats::getSeat(int pIndex, int pFID) //get seat number x of flight pFID
{
    int a;
    return a;
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
    
    int random = RandomInt((int)mChilds.size()-1);
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
    int random = RandomInt((int)mChilds.size()-1);
    StorageUnit* seat = mChilds[random];
    Row<Seat>* seatRow = static_cast<Row<Seat>*>(seat);
    if (seatRow != nullptr)
        return &seatRow->mData;
    else return nullptr;
}

