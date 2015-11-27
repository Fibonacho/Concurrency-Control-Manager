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

class Reservations: public Table
{
private:
    
    //should have a pointer on all valid flight ids and passanger ids
    struct Reservation
    {
        int* pID; // Passenger ID
        int* sID; // Seat ID
        int* fID; // Flight ID (redundant data)
    };
public:
    Reservations(Database& database);

    bool add(int* pFID, int* pSID, int* pPID);
    bool remove(int pFID, int pPID);
    bool book(int& pFID, int& pSID, int& pPID);
    
    // get flights for a specific passenger and a random one
    void getBookedFlights(const int pPID);
    void getBookedFlights();
    void printReservationSum();
    void book();
    void remove();
};

#endif
