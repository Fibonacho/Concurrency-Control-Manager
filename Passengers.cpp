#include "Passengers.h"
#include "Row.h"

Passengers::Passengers(Database& database): Table(database)
{
}

int Passengers::add(std::string pName)
{
    //is id already in the data structure
    /*Passenger passenger;
    passenger.mPID = getNewID();
    passenger.mName = pName;
    mList.pushBack(passenger);
    return passenger.mPID;*/
    
    Row<Passenger> row(*this);
    row.mData.mName = pName;
    row.mData.mPID = getNewID();
    addRow(row);
    return row.mData.mPID;
}

/*bool Passengers::remove(int id)
{
    //remove an item from the linked list
    return true;
}

void Passengers::initialize()
{
    //function initialize
    Passengers::Passenger passeger;
    passeger.mID = 4; //getNewID();;
    passeger.mName = "Eva";
    add(passeger);
    
    Passengers::Passenger passeger2;
    passeger2.mID = 8; //getNewID();
    passeger2.mName = "Elvis";
    add(passeger2);
}
*/