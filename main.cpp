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

int main(int argc, const char * argv[]) {
    // initialize the booking database (creates the tables)
    BookingDatabase::initializeData();
    // initialize the transaction handler with the 4 transactions
    BookingDatabase::initializeTransactionHandler();
    // start the transaction handler with x threads
    BookingDatabase::transactionHandler.call();
    std::cin.get();
    return 0;
}
