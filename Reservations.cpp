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

bool BookingDatabase::Reservations::removeRes(int pFID, int pPID)
{
    for (auto child: mChilds)
    {
        Row<Reservation>* reservation = static_cast<Row<Reservation>*>(child);
        if (reservation != nullptr)
        {
            //mChilds.erase(std::remove(mChilds.begin(), mChilds.end(), ' '), mChilds.end());

            if ((reservation->mData.mPID == pPID) && (reservation->mData.mFID == pFID))
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
            if (reservation->mData.mPID == pPID)
                std::cout << reservation->mData.mFID << " " << std::endl;
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
        
        std::cout << "FID: " << rowRes->mData.mFID << ", SID: " << rowRes->mData.mSID << ", PID: " << rowRes->mData.mPID << std::endl;
    }
    std::cout << "----------------------------" << std::endl;
}

void BookingDatabase::Reservations::printReservationSum()
{
    std::cout << "Sum of Reservations: " << childCount() << std::endl;
}

bool BookingDatabase::Reservations::hasBooked(int pFID, int pPID) const
{
    //iterate over childs and check if the passanger pPID has already booked the flight pFID
    for (auto child: mChilds)
    {
        Row<Reservation>* row = static_cast<Row<Reservation>*>(child);
        if (row != nullptr)
        {
            if ((row->mData.mFID == pFID) && (row->mData.mPID))
                return true;
        }
    }
    return false;
}

bool BookingDatabase::Reservations::book(int pFID, int pSID, int pPID)
{
    //check if the seat ID is within the flight range
    if (pSID == -1)
        return false;
    
    // the passanger has already booked the flight
    // "A passenger can book more flights, but each flight only once."

    if (hasBooked(pFID, pPID))
        return false;
    
    Row<Reservation>* row = new Row<Reservation>(*this);
    row->mData.mSID = pSID;
    row->mData.mFID = pFID;
    row->mData.mPID = pPID;
    addRow(row);
    
    std::cout << "Added reservation to seat " << row->mData.mSID << " for passanger " << row->mData.mPID << " and flight " << row->mData.mFID << std::endl;
    return true;
}

bool BookingDatabase::Reservations::book(int pFID, int pPID, std::vector<int> &pFlightSeatIDs)
{
    // book a flight for passanger pPID and flight pFID
    // returns false if the flight is already booked by the passanger or the flight is full
    // get list of seat ids of specific flight
    // remove all seats from pFlightSeatIDs which are already booked and then just get a random seat for the passanger by:
    // iterate over all reservations
    for (auto child: mChilds)
    {
        Row<Reservation>* row = static_cast<Row<Reservation>*>(child);
        // remove the booked reservations from the vector of free seats
        pFlightSeatIDs.erase(std::remove(pFlightSeatIDs.begin(), pFlightSeatIDs.end(), row->mData.mSID), pFlightSeatIDs.end());
    }
    if (pFlightSeatIDs.size() == 0)
        return false; // the flight is booked out
    int random = RandomInt((int)pFlightSeatIDs.size());
    int FreeSeatID = pFlightSeatIDs[random];
    bool booked = book(pFID, FreeSeatID, pPID);
    return booked;
}

BookingDatabase::Reservations::Reservation* BookingDatabase::Reservations::getRandomReservation()
{
    if (mChilds.size() == 0)
        return nullptr;
        
    int random = RandomInt((int)mChilds.size());
    StorageUnit* child = mChilds[random];
    Row<Reservation>* childRow = static_cast<Row<Reservation>*>(child);
    if (childRow != nullptr)
        return &childRow->mData;
    else return nullptr;
}
