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

typedef void (*Transaction)(void);

class TransactionHandler
{
private:
    std::vector<Transaction> mTransactions;
    Database* mDatabase;
public:
    TransactionHandler(Database &pDatabase);
	~TransactionHandler();
    
    void stop();
    void start(const int pThreads);
    void addTransaction(Transaction pTransaction);
};
