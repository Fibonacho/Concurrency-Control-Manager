#include "TransactionHandler.h"

TransactionHandler::TransactionHandler(Database &pDatabase)
{
    mDatabase = &pDatabase;
}

TransactionHandler::~TransactionHandler()
{

}

void TransactionHandler::stop()
{

}

void TransactionHandler::start()
{

}

void TransactionHandler::Transaction1() {}
void TransactionHandler::Transaction2() {}
void TransactionHandler::Transaction3() {}
