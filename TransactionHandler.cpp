#include "TransactionHandler.h"
#include "Common.h"

TransactionHandler::TransactionHandler(Database &pDatabase) //: mIndex(0)
{
    mDatabase = &pDatabase;
}

TransactionHandler::~TransactionHandler()
{

}

void TransactionHandler::callAll()
{
    for(auto transaction: mTransactions)
        transaction.call();
}

void TransactionHandler::callRandom()
{
    // TODO: sleep random time
    int random = RandomInt((int)mTransactions.size());
    bool executedTransaction = false;
    while (!executedTransaction)
    {
        if (mTransactions[random].ObjectsUnlocked())
        {
            // mTransactions add a list of objects and their locks
            mTransactions[random].acquireLocks();
            mTransactions[random].call();
            mTransactions[random].releaseLocks();
            executedTransaction = true;
        }
        else Sleep(10); //wait for a specific time and try again
    }
}

//void TransactionHandler::stat(const int pThreads, const int pCount)
//{
    // TODO: x threads call callRandom(), pCount times
    // repeat some number of times (pCount)
    // select a transaction type randomly (callRandom)
    // select object (flight and passenger id) for transaction randomly (is done in the transaction itself)
    // invoke transaction (done in callRandom())
//}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}
