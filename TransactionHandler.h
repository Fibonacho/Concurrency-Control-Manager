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
    
    void run(const int pThreads, const int pCount);
    void callAll();
    void callRandom(const int pID, const int pTimes = 1);
    void addTransaction(Transaction pTransaction);
};
