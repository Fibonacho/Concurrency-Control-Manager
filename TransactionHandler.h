//TransactionHandler

#include "Database.h"
#include <vector>

typedef void (*Transaction)(void);

class TransactionHandler
{
private:
    //int mIndex;
    std::vector<Transaction> mTransactions;
    
    //the transaction handler operates on a specific database
    Database* mDatabase;
public:
    TransactionHandler(Database &pDatabase);
	~TransactionHandler();
    
    //void
    void stop();
    void start();
    
    void addTransaction(Transaction pTransaction);
    
    //holds a list of transactions (function pointers)
};
