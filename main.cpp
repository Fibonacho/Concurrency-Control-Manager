//  ---------------------------------------------------
//  main.cpp
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#include <iostream>
#include <chrono>
#include "BookingDatabase.h"
#include "UnitTestLocking.h"

int main(int argc, const char * argv[]) {

    // timestamp (begin)
    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();

    UnitTestLocking::test();
    
    std::vector<std::string> destinationList;
    destinationList.push_back("Tokio");
    destinationList.push_back("Salzburg");
    destinationList.push_back("Amsterdam");
    destinationList.push_back("New York");
    destinationList.push_back("Vienna");
    
    std::vector<std::string> passengerList;
    passengerList.push_back("Lori");
    passengerList.push_back("Glenn");
    passengerList.push_back("Rick");
    passengerList.push_back("Daryl");

    // flights are generated with a max seat count of 1000, which are randomly distributed on the flights
    int MaxSeatCount = 5000;
    // flights have an average seat count
    int AverageSeatCount = 75;
    // number of passengers
    int PassengerCount = 100;
    // number of flights
    int FlightCount = 50;

    // The evaluation will be changed for the final evaluation
    // initialize the booking database (creates the tables)
    BookingDatabase::initData(destinationList, passengerList, AverageSeatCount, MaxSeatCount, PassengerCount, FlightCount);
    // initialize the transaction handler with the 4 transactions
    BookingDatabase::initTransactionHandlerSerial();
        // BookingDatabase::initializeTransactionHandlerConcurrent();
    // run(pThreads, pCount) --> run pThreads that call callRandom() pCount times
    // BookingDatabase::db.ForceLockExclusive();
    BookingDatabase::transactionHandler.run(1, 10);

    // timestamp (end)
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

    std::cout << "Duration: " << duration << " microseconds" << std::endl;

    std::cin.get();
    return 0;
}
