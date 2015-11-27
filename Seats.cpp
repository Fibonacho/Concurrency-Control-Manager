#include "Seats.h"
#include "Row.h"

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

bool Seats::add(int& pFID, int pCount) //pFID as pointer
{
    for (int i = 0; i < pCount; i++)
    {
        Row<Seat> row(*this);
        row.mData.mSID = getNewID();
        row.mData.mFID = &pFID;
        addRow(row);
        
        /*Seats::Seat seat;
        seat.mSID = getNewID();
        seat.mFID = pFID;
        mList.pushBack(seat);*/
        std::cout << " Added seat number " << row.mData.mSID << " to the flight " << pFID << std::endl;
    }
    return true; //exception handeling missing
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

