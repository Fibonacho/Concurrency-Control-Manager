#include "Reservations.h"
#include "Row.h"
#include "Common.h"
#include <iostream>
#include <algorithm>

BookingDatabase::Reservations::Reservations(Database& database): Table(database)
{
}

BookingDatabase::Reservations::~Reservations()
{
}

bool BookingDatabase::Reservations::removeRes(int pFID, int pPID)
{
    for (auto child: mChilds)
    {
        Row<Reservation>* reservation = static_cast<Row<Reservation>*>(child);
        if (reservation != nullptr)
        {
            if ((reservation->getData().mPID == pPID) && (reservation->getData().mFID == pFID))
            {
                mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), child), mChilds.end());
                return true;
                break;
            }
        }
    }
    return false;
}

void BookingDatabase::Reservations::removeRes()
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
            if (reservation->getData().mPID == pPID)
                std::cout << reservation->getData().mFID << " " << std::endl;
        }
        std::cout << std::endl;
    }
}

void BookingDatabase::Reservations::display() const
{
    std::cout << "----------------------------" << std::endl << "Display Reservations: " << std::endl;
    for(auto res: mChilds)
    {
        Row<Reservation>* rowRes = static_cast<Row<Reservation>*>(res);
        
        std::cout << "FID: " << rowRes->getData().mFID << ", SID: " << rowRes->getData().mSID << ", PID: " << rowRes->getData().mPID << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

void BookingDatabase::Reservations::printReservationSum()
{
    std::cout << "Sum of Reservations: " << childCount() << std::endl;
}

bool BookingDatabase::Reservations::hasBooked(int pFID, int pPID) const
{
    // iterate over childs and check if flight has already been booked 
    for (auto child: mChilds)
    {
        Row<Reservation>* row = static_cast<Row<Reservation>*>(child);
        if (row != nullptr)
        {
            if ((row->getData().mFID == pFID) && (row->getData().mPID))
                return true;
        }
    }
    return false;
}

bool BookingDatabase::Reservations::book(int pFID, int pSID, int pPID)
{
    // check if the seat ID is within the flight range
    if (pSID == -1)
        return false;
    
    // the passenger has already booked the flight
    // "A passenger can book more flights, but each flight only once."

    if (hasBooked(pFID, pPID))
        return false;
    
    Reservation reservation(pPID, pSID, pFID);
    Row<Reservation>* row = new Row<Reservation>(*this, reservation);
    addRow(row);
    std::cout << "Added reservation to seat " << row->getData().mSID << " for passenger " << row->getData().mPID << " and flight " << row->getData().mFID << std::endl;
    return true;
}

bool BookingDatabase::Reservations::book(int pFID, int pPID, std::vector<int> &pFlightSeatIDs)
{
    // returns false if the flight is already booked by the passenger or the flight is full
    // get list of seat ids of specific flight
    // remove all seats from pFlightSeatIDs which are already booked and then just get a random seat for the passenger by:
    // iterating over all reservations
    for (auto child: mChilds)
    {
        Row<Reservation>* row = static_cast<Row<Reservation>*>(child);
        // remove the booked reservations from the vector of free seats
        pFlightSeatIDs.erase(std::remove(pFlightSeatIDs.begin(), pFlightSeatIDs.end(), row->getData().mSID), pFlightSeatIDs.end());
    }
    if (pFlightSeatIDs.size() == 0)
        return false; // the flight is booked out
    int random = RandomInt((int)pFlightSeatIDs.size());
    int FreeSeatID = pFlightSeatIDs[random];
    bool booked = book(pFID, FreeSeatID, pPID);
    return booked;
}

BookingDatabase::Reservations::Reservation BookingDatabase::Reservations::getRandomReservation()
{
    if (mChilds.size() == 0)
        return Reservation();
        
    int random = RandomInt((int)mChilds.size());
    StorageUnit* child = mChilds[random];
    Row<Reservation>* childRow = static_cast<Row<Reservation>*>(child);
    if (childRow != nullptr)
        return childRow->getData();
    else return Reservation();
}
