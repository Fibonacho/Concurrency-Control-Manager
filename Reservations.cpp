#include "Reservations.h"
#include "Row.h"
#include "Common.h"
// #include <iostream>
#include <algorithm>
#include "LogFile.h"

BookingDatabase::Reservations::Reservations(Database* database): Table(database)
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
                //mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), child), mChilds.end());
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

bool BookingDatabase::Reservations::getBookedFlights(const int pPID)
{
    for (auto child: mChilds)
    {
        //if (mDataConsoleOutput) std::cout << "List of flights of passenger " << pPID << ": ";
        Row<Reservations::Reservation>* reservation = static_cast<Row<Reservations::Reservation>*>(child);
        if (reservation != nullptr)
        {
            //if ((mDataConsoleOutput) && (reservation->getData().mPID == pPID))
            //    std::cout << reservation->getData().mFID << " " << std::endl;
        }
        //std::cout << std::endl;
    }
    return true;
}

void BookingDatabase::Reservations::display() const
{
    //if (mDataConsoleOutput) std::cout << "----------------------------" << std::endl << "Display Reservations: " << std::endl;
    for(auto res: mChilds)
    {
        Row<Reservation>* rowRes = static_cast<Row<Reservation>*>(res);
        //if (mDataConsoleOutput)
        //    std::cout << "FID: " << rowRes->getData().mFID << ", SID: " << rowRes->getData().mSID << ", PID: " << rowRes->getData().mPID << std::endl;
    }
    //if (mDataConsoleOutput)
    //    std::cout << "----------------------------" << std::endl;
}

bool BookingDatabase::Reservations::printReservationSum()
{
    //if (mDataConsoleOutput)
    //mLogFile.write("Sum of Reservations: " + std::to_string(childCount()));
    return true;
}

bool BookingDatabase::Reservations::hasBooked(int pFID, int pPID) const
{
    // iterate over childs and check if flight has already been booked 
    for (auto child: mChilds)
    {
        Row<Reservation>* row = static_cast<Row<Reservation>*>(child);
        if (row != nullptr)
        {
            if ((row->getData().mFID == pFID) && (row->getData().mPID) == pPID)
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
    Row<Reservation>* row = new Row<Reservation>(this, reservation);
    addRow(row);
    //if (mDataConsoleOutput)
     //   mLogFile.write("Added reservation to seat " + std::to_string(row->getData().mSID) + " for passenger " + std::to_string(row->getData().mPID) + " and flight " + std::to_string(row->getData().mFID));
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

const BookingDatabase::Reservations::Reservation* BookingDatabase::Reservations::getRandom()
{
    if (mChilds.size() == 0)
        return nullptr;
        
    int random = RandomInt((int)mChilds.size());
    StorageUnit* child = mChilds[random];
    Row<Reservation>* childRow = static_cast<Row<Reservation>*>(child);
    if (childRow != nullptr)
    {
        return childRow->getDataPtr();
    }
    else return nullptr;
}
