//  ---------------------------------------------------
//  TransactionHandler
//  - operates on a specific database
//  - holds a list of transactions (function pointers)
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#include "Database.h"
#include <vector>
#include "Transaction.h"
#include <thread>

class TransactionHandler
{
private:
    std::vector<Transaction> mTransactions;
    std::vector<std::thread*> mThreads;
    Database* mDatabase;

public:
    TransactionHandler(Database &pDatabase);
    ~TransactionHandler();

    // union object to store a thread's id together with its runtime
    union ThreadRuntime
    {
        ThreadRuntime() {}
        // cID, cTP ("c" for "constructor")
        ThreadRuntime(std::thread::id cID, std::chrono::high_resolution_clock::time_point cTP): mID(cID), mTimepoint(cTP) {}
        ~ThreadRuntime() {}
        std::thread::id mID;
        std::chrono::high_resolution_clock::time_point mTimepoint;
    } mRuntime;
    // vector to store runtime values of every thread
    std::vector<ThreadRuntime> mThreadRuntime;

    // pThreads threads call callRandom(), pCount times
    // repeat some number of times (pCount)
    // select a transaction type randomly (callRandom)
    // select object (flight and passenger id) for transaction randomly (is done in the transaction itself)
    // invoke transaction (done in callRandom())
    void run(const int pThreads, const int pCount);
    // call all transactions from Transaction-vector mTransactions
    void callAll();
    // call a random transaction pTimes times (at least once)
    // from thread with id pID
    // sleep after calling transaction
    void callRandom(const unsigned int pTimes = 1);
    void addTransaction(Transaction pTransaction);
    void printRuntimes();
};
