#include "TransactionHandler.h"

TransactionHandler::TransactionHandler(Database &pDatabase)
{
    mDatabase = &pDatabase;
}

TransactionHandler::~TransactionHandler()
{

}
