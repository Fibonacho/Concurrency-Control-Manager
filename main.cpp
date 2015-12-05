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
#include "BookingDatabase.h"
#include "UnitTestLocking.h"

int main(int argc, const char * argv[]) {
    UnitTestLocking::test();
    
    std::vector<std::string> destinationList;
    destinationList.push_back("Tokio");
    destinationList.push_back("Salzburg");
    destinationList.push_back("Amsterdam");
    
    std::vector<std::string> passengerList;
    passengerList.push_back("Glenn");
    passengerList.push_back("Rick");
    passengerList.push_back("Daryl");
    // this small value is only for easier testing, should later be 100 or seomthing
    int AverageSeatCount = 10; // will later be solved differently

    // initialize the booking database (creates the tables)
    BookingDatabase::initializeData(destinationList, passengerList, AverageSeatCount);
    // initialize the transaction handler with the 4 transactions
    BookingDatabase::initializeTransactionHandlerSerial();
    // BookingDatabase::initializeTransactionHandlerConcurrent();
    // run(pThreads, pCount) --> run pThreads that call callRandom() pCount times
    // BookingDatabase::db.ForceLockExclusive();
    BookingDatabase::transactionHandler.run(10, 10);
    std::cin.get();
    return 0;
}
