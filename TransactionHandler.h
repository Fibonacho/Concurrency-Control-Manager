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
    
    void stop();
    void start();
};
