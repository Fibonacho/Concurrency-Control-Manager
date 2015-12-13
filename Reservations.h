//  ---------------------------------------------------
//  Reservations:
//  - Reservations Table
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include "Table.h"
#include "Database.h"

namespace BookingDatabase {
    class Reservations: public Table
    {
    private:
        // book a seat on a flight
        bool book(int pFID, int pSID, int pPID);
    public:
        struct Reservation
        {
            int mPID; // Passenger ID
            int mSID; // Seat ID
            int mFID; // Flight ID (redundant data)
            
            Reservation(int pPID, int pSID, int pFID): mPID(pPID), mFID(pFID), mSID(pSID) {}
            Reservation(): mPID(-1), mFID(-1), mSID(-1) {}
        };
        
        Reservations(Database* database);
        virtual ~Reservations();
        
        // book a flight for passenger pPID and flight pFID
        bool book(int pFID, int pPID, std::vector<int> &pFlightSeatIDs);
        // remove a reservation with flight id pFID and passenger id pPID
        // i.e. delete a certain row from the reservations table
        bool removeRes(int pFID, int pPID);
        // tell if passenger with id pPID has booked flight with id pFID
        bool hasBooked(int pFID, int pPID) const;
        
        // get / print booked flights of a passenger with id pPID
        bool getBookedFlights(const int pPID);
        // print number of reservations (sum of rows)
        void printReservationSum();
        // remove a random reservation
        // i.e. delete a random row from the reservations table
        void removeRes();
        // display reservations, i.e. print content of reservation table to console
        // print every row in a new line
        void display() const;
        // get a random reservation
        Reservation* getRandom();
    };
}

#endif
