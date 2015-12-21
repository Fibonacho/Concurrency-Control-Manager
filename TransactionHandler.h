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
//#include <mutex>
#include <queue>

class TransactionHandler
{
private:
    std::vector<Transaction> mTransactions;
    std::vector<std::thread*> mThreads;
    Database* mDatabase;
    //std::mutex m;
    //std::mutex m1;
    std::queue<Transaction*> mQueue;
public:
    TransactionHandler(Database &pDatabase);
    ~TransactionHandler();
    
    // pThreads threads call callRandom(), pCount times
    // repeat some number of times (pCount)
    // select a transaction type randomly (callRandom)
    // select object (flight and passenger id) for transaction randomly (is done in the transaction itself)
    // invoke transaction (done in callRandom())
    void run(const int pThreads, const int pCount);
    // call all transactions from Transaction-vector mTransactions
    void callAll();
    void work();
    // call a random transaction pTimes times (at least once)
    // from thread with id pID
    // sleep after calling transaction
    void callRandom(const unsigned int pTimes = 1);
    void addTransaction(Transaction pTransaction);
};
