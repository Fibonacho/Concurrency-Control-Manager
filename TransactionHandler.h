//TransactionHandler

#include "Database.h"

class TransactionHandler
{
private:
   // operates on a Database ?!
    Database* mDatabase;
public:
    TransactionHandler(Database &pDatabase);
	~TransactionHandler();
};
