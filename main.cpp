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

// #include <iostream>
#include "BookingDatabase.h"
#include "UnitTestLocking.h"
#include <time.h>
#include <fstream>
#include "LogFile.h"
#include <iostream>

int main(int argc, const char * argv[]) {
    UnitTestLocking::test();
    //LogFile MainLogFile("log.txt");
    
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
    // this small value is only for easier testing, should later be 100 or seomthing
    // flights are generated with a max seat count of 1000, which are randomly distributed on the flights
    int MaxSeatCount = 5000;
    // flights have an average seat count
    int AverageSeatCount = 75;
    // number of passengers
    int PassengerCount = 100;
    // number of flights
    int FlightCount = 50;
    //if (argc != 2) std::cout << "usage: " << argv[0] <<" <concurrent/serial>\n";
  
    // The evaluation will be changed for the final evaluation
    // initialize the booking database (creates the tables)
    // BookingDatabase::initData(destinationList, passengerList, AverageSeatCount);
    BookingDatabase::initData(destinationList, passengerList, AverageSeatCount, MaxSeatCount, PassengerCount, FlightCount);
    // initialize the transaction handler with the 4 transactions
    BookingDatabase::initTransactionHandlerSerial();
    //BookingDatabase::mLogFile = &MainLogFile;
    // BookingDatabase::initTransactionHandlerConcurrent();
    // run(pThreads, pCount) --> run pThreads that call callRandom() pCount times
    
    int transactions = 50;
    int threads = 20;

    std::chrono::high_resolution_clock::time_point begin = std::chrono::high_resolution_clock::now();
    std::cout << " treads begin ..." << std::thread::hardware_concurrency() << std::endl;
    
    //BookingDatabase::db.ForceLockExclusive();

    BookingDatabase::transactionHandler.run(threads, transactions);
    
    //BookingDatabase::transactionHandler.callRandom(transactions);
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
    std::cout << " treads, " << transactions << " transactions: " << duration*1.0f/1000 << " ms" << std::endl;
    
    std::fstream filestr;
    filestr.open("output.txt", std::fstream::in | std::fstream::out | std::fstream::app);
    filestr << "CONCURRENT " << "\t" << "DEBUG" << "\t" << threads << "\t" << transactions << "\t" << duration*1.0f/1000 << " ms" << std::endl;
    
    std::cin.get();
    return 0;
}
