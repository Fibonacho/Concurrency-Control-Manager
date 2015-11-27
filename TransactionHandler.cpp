#include "TransactionHandler.h"
#include "Common.h"

TransactionHandler::TransactionHandler(Database &pDatabase) //: mIndex(0)
{
    mDatabase = &pDatabase;
}

TransactionHandler::~TransactionHandler()
{

}

void TransactionHandler::stop()
{

}

void TransactionHandler::call()
{
    for(auto transaction: mTransactions)
        transaction();
}

void TransactionHandler::start(const int pThreads)
{

}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}
