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
    
    std::string destinations[] = {"Tokio", "NY", "Berlin", "London", "Salzburg",
        "Vienna", "Amsterdam", "LA", "SF", "Rio de Janeiro"};
    std::string passengers[]   = {"Johanna", "Elvis", "Eva", "Rick", "Glenn", "Maggie",
        "Michonne", "Carol", "Daryl", "Andrea", "Joey", "Phoebe", "Chandler", "Monica",
        "Rachel", "Ross", "Richard", "Carl", "John", "James"};
    //int numbOfSeats = 1000;

    // initialize the booking database (creates the tables)
    BookingDatabase::initializeData(destinations, passengers);
    // initialize the transaction handler with the 4 transactions
    BookingDatabase::initializeTransactionHandlerSerial();
    //BookingDatabase::initializeTransactionHandlerConcurrent();
    // run(pThreads, pCount) --> run pThreads that call callRandom() pCount times
    BookingDatabase::transactionHandler.run(10, 2);
    std::cin.get();
    return 0;
}
