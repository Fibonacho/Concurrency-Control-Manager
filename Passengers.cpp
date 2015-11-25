#include "Passengers.h"

bool Passengers::add(Passenger pPasseger)
{
    //is id already in the data structure
    mList.pushBack(pPasseger);
    return true;
}

bool Passengers::remove(int id)
{
    //remove an item from the linked list
    return true;
}

void Passengers::initialize()
{
    //function initialize
    Passengers::Passenger passeger;
    passeger.mID = getNewID();;
    passeger.mName = "Eva";
    add(passeger);
    
    Passengers::Passenger passeger2;
    passeger2.mID = getNewID();
    passeger2.mName = "Elvis";
    add(passeger2);
}
