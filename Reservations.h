//  ---------------------------------------------------
//  Passengers:
//  - Passengers Table
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
    public:
        struct Reservation
        {
            int mPID; // Passenger ID
            int mSID; // Seat ID
            int mFID; // Flight ID (redundant data)
        };
        // Pointer to the List auf Flights
        // std::vector<int>* mFlightList; //probably not needed
        // Pointer to the List of Passengers
        // std::vector<int>* mPassengerList;
        
        Reservations(Database& database);

        bool book(int pFID, int pSID, int pPID);
        bool book(int pFID, int pPID);
        bool removeRes(int pFID, int pPID);
        bool hasBooked(int pFID, int pPID) const;
    
        // get flights for a specific passenger and a random one
        void getBookedFlights(const int pPID);
        void printReservationSum();
        void book();
        void removeRes();
        void display() const;
        Reservation* getRandomReservation();
    };
}

#endif
