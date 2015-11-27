#include "Seats.h"
#include "Row.h"
#include "Common.h"
#include <iostream>

Seats::Seats(Database& database): Table(database)
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

int* Seats::getSeat(int pIndex) const
{
    StorageUnit* su = mChilds[pIndex];
    if (su != nullptr)
        return &static_cast<Row<Seat>*>(su)->mData.mSID;
    else
        return nullptr;
}

int* Seats::returnSID(StorageUnit* su)
{
    if (su != nullptr)
        return &static_cast<Row<Seat>*>(su)->mData.mSID;
    else
        return nullptr;
}

int* Seats::getSeat(int* pFID) //get seat of flight
{
    //check for pFID
    //while ()
    return returnSID(mChilds[RandomInt(mChilds.size())]);
}

int* Seats::getSeat()
{
    //returns a random seat
    return returnSID(mChilds[RandomInt(mChilds.size())]);
}

int* Seats::getSeat(int pIndex, int* pFID) //get seat number x of flight pFID
{
    int a;
    return &a;
}

int Seats::add(int& pFID) //, int pCount) //pFID as pointer
{
    //mSeatIndizing.push_back(Seat(pCount, &pFID));
    //mIndex += pCount;
    
    //for (int i = 0; i < pCount; i++)
    //{
        Row<Seat>* row = new Row<Seat>(*this);
        row->mData.mSID = getNewID();
        row->mData.mFID = &pFID;
        addRow(row);
        
        /*Seats::Seat seat;
        seat.mSID = getNewID();
        seat.mFID = pFID;
        mList.pushBack(seat);*/
        std::cout << " Added seat number " << row->mData.mSID << " to the flight " << pFID << std::endl;
    //}
    return row->mData.mSID;
}

void Seats::add(int &pFID, int pCount)
{
    for (int i = 0; i < pCount; i++)
        add(pFID);
}

/*std::list<int> Seats::getSeatList(const int pFID)
{
    std::list<int> list;
    
    int count  = mList.count();
    for (int i = 0; i < count; i++)
        //horrible runtime, sorry for this
    {
        Seat seat = mList.returnElement(i);
        if (seat.mFID == pFID)
            list.push_back(seat.mSID);
    }
    return list;
}*/

