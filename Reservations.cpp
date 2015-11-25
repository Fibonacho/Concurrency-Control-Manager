#include "Reservations.h"

bool Reservations::add(Reservation pReservation)
{
    //is id already in the data structure
    mList.pushBack(pReservation);
    return true;
}

bool Reservations::remove(int id)
{
    //remove an item from the linked list
    return true;
}

void Reservations::initialize()
{
    //function initialize
    Reservations::Reservation reservation;
    reservation.sID = 3; //getRandomFreeSeat();
    reservation.pID = 3; //getRandomPassangerID(); we need a connection to the flight "table"
    //add(passeger);
    //more ...
}
