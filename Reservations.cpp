#include "Reservations.h"

bool Reservations::add(Reservation pReservation)
{
    //is id already in the data structure
    mList.pushBack(pReservation);
    return true;
}

bool Reservations::remove(int pFID, int pPID)
{
    int count  = mList.count();
    for (int i = 0; i < count; i++)
    //horrible runtime, sorry for this
    {
        Reservation res = mList.returnElement(i);
        if ((res.pID == pPID) && (res.fID == pFID))
            mList.remove(i);
    }
    return false;
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

bool Reservations::book(int pFID, int pPID, int pSID)
{
    /*1. choose a specific passenger and specific flight
    check if passenger already booked the seat for that flight
        if already booked that flight; go back step 1.
        else continue
            2. list all seats from seats list of chosen flight
            3. remove seats from that list which are in reservations list
            4. choose a random seat from that (free seats) list
            5. check the reservations list if seat is listed or not
                if seat is in list reservations; choose another seat (go back step 4.)
    if seat is not listed check if it’s locked by another transaction
        if locked then wait (lock manager??)
            else: lock the seat, wait a random time and book the seat.
                unlock the seat
                6. create new row in list reservations with that reservation pID and sID.*/
    
    int count  = mList.count();
    for (int i = 0; i < count; i++)
    //horrible runtime, sorry for this
    {
        Reservation res = mList.returnElement(i);
        if ((res.pID == pPID) && (res.fID == pFID))
            return false;
    }
    
    //std::list<int> list = getSeats(fid);
    
    
    return true;
}

bool Reservations::add(int pFID, int pSID, int pPID)
{
    Reservations::Reservation reservation;
    reservation.fID = pFID;
    reservation.sID = pSID;
    reservation.pID = pPID;

    mList.pushBack(reservation);
    std::cout << "Added reservation to seat " << reservation.sID << " for passanger " << reservation.pID << " and flight " << reservation.fID << std::endl;
    return true;
}

uint Reservations::count() const
{
    return mList.count();
}

std::list<int> Reservations::getFlightIDs(const int pPID)
{
    std::list<int> list;
    int count  = mList.count();
    for (int i = 0; i < count; i++)
    //horrible runtime, sorry for this
    {
        Reservation res = mList.returnElement(i);
        if (res.pID == pPID)
            list.push_back(res.fID);
    }
    return list;
}

std::list<int> Reservations::getFreeSeats(std::list<int> &SeatList)
{
    int count  = mList.count();
    for (int i = 0; i < count; i++)
        //horrible runtime, sorry for this
    {
        Reservation res = mList.returnElement(i);
        SeatList.remove(res.sID);
    }
    return SeatList;
}
