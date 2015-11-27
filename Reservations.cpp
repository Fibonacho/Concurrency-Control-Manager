#include "Reservations.h"
#include "Row.h"
#include "Common.h"
#include <iostream>

BookingDatabase::Reservations::Reservations(Database& database): Table(database)
{
}

/*bool Reservations::add(Reservation pReservation)
{
    //is id already in the data structure
    mList.pushBack(pReservation);
    return true;
}
*/

bool BookingDatabase::Reservations::remove(int pFID, int pPID)
{
    for (auto child: mChilds)
    {
        Row<Reservation>* reservation = static_cast<Row<Reservation>*>(child);
        if (reservation != nullptr)
        {
            //mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), ' '), mChilds.end());
            
            int pID = *reservation->mData.pID;
            int fID = *reservation->mData.fID;
            if ((pID == pPID) && (fID == pFID))
            {
                mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), child), mChilds.end());
                return true;
                break;
            }
        }
    }
    return false;
}

void BookingDatabase::Reservations::remove()
{
    StorageUnit* child = mChilds[RandomInt((int)mChilds.size())];
    mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), child), mChilds.end());
}

void BookingDatabase::Reservations::getBookedFlights(const int pPID)
{
    for (auto child: mChilds)
    {
        std::cout << "List of flights of passenger " << pPID << ": ";
        Row<Reservations::Reservation>* reservation = static_cast<Row<Reservations::Reservation>*>(child);
        if (reservation != nullptr)
        {
            if (*reservation->mData.pID == pPID)
                std::cout << *reservation->mData.fID << " " << std::endl;
        }
        std::cout << std::endl;
    }
}

void BookingDatabase::Reservations::display()
{
    std::cout << "----------------------------" << std::endl << "Display Reservations: " << std::endl;
    for(auto res: mChilds)
    {
        Row<Reservation>* rowRes = static_cast<Row<Reservation>*>(res);
        
        std::cout << "FID: " << rowRes->mData.fID << ", SID: " << rowRes->mData.sID << ", PID: " << rowRes->mData.pID << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

void BookingDatabase::Reservations::getBookedFlights()
{
    //get random passanger
    int pid = 0;
    getBookedFlights(pid);
}

void BookingDatabase::Reservations::printReservationSum()
{
    std::cout << "Sum of Reservations: " << childCount() << std::endl;
}

/*
void Reservations::initialize()
{
    //function initialize
    Reservations::Reservation reservation;
    reservation.sID = 3; //getRandomFreeSeat();
    reservation.pID = 3; //getRandomPassangerID(); we need a connection to the flight "table"
    //add(passeger);
    //more ...
}*/

bool BookingDatabase::Reservations::book(int& pFID, int& pPID, int& pSID)
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
    
  /*  int count  = mList.count();
    for (int i = 0; i < count; i++)
    //horrible runtime, sorry for this
    {
        Reservation res = mList.returnElement(i);
        if ((res.pID == pPID) && (res.fID == pFID))
            return false;
    }
    
    //std::list<int> list = getSeats(fid);
    */
    
    return true;
}

void BookingDatabase::Reservations::book()
{ //call add
    // ----- 1. book transaction ----------------------------------------------------
    /*std::list<int> slist = seatTable.getSeatList(BerlinID);
     std::list<int> freeSeats = reservationTable.getFreeSeats(slist);
     srand(time(NULL));
     int randomValue = rand() % freeSeats.size();         // v1 in the range 0 to 99
     std::list<int>::iterator i = freeSeats.begin();
     std::advance(i, randomValue);
     reservationTable.book(1, 1, *i);*/
}

bool BookingDatabase::Reservations::add(int* pFID, int* pSID, int* pPID)
{
    if (pSID == nullptr)
        return false;
    
    Row<Reservation>* row = new Row<Reservation>(*this);
    //Row<Reservations::Reservation> row(*this);
    row->mData.sID = pSID;
    row->mData.fID = pFID;
    row->mData.pID = pPID;
    addRow(row);
    
    /*Reservations::Reservation reservation;
    reservation.fID = &pFID;
    reservation.sID = &pSID;
    reservation.pID = &pPID;

    mList.pushBack(reservation);*/
    std::cout << "Added reservation to seat " << *row->mData.sID << " for passanger " << *row->mData.pID << " and flight " << *row->mData.fID << std::endl;
    return true;
}

/*

std::list<int> Reservations::getFlightIDs(const int pPID)
{

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
}*/
