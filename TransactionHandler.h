//TransactionHandler

#include "Database.h"

class TransactionHandler
{
private:
    //the transaction handler operates on a specific database
    Database* mDatabase;
public:
    TransactionHandler(Database &pDatabase);
	~TransactionHandler();
    
    //void
    void stop();
    void start();
    
    void Transaction1();
    void Transaction2();
    void Transaction3();
    
    //holds a list of transactions (function pointers)
};
