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

void TransactionHandler::callAll()
{
    for(auto transaction: mTransactions)
    {
        transaction();
    }
}

void TransactionHandler::callRandom()
{
    // TODO: sleep random time
    int random = RandomInt((int)mTransactions.size()-1);
    mTransactions[random]();
}

void TransactionHandler::start(const int pThreads, const int pCount)
{
    // TODO: x threads call callRandom(), pCount times
    // repeat some number of times (pCount)
    // select a transaction type randomly (callRandom)
    // select object (flight and passenger id) for transaction randomly (is done in the transaction itself)
    // invoke transaction (done in callRandom())
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}
