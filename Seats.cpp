#include "Seats.h"

bool Seats::add(Seat pSeat)
{
    //is id already in the data structure
    mList.pushBack(pSeat);
    return true;
}

bool Seats::remove(int id)
{
    //remove an item from the linked list
    return true;
}

void Seats::initialize()
{
    //function initialize
    Seats::Seat seat;
    seat.sID = getNewID();
    seat.fID = 3; //getRandomfID(); we need a connection to the flight "table"
    //add(passeger);
    //more ...
}
