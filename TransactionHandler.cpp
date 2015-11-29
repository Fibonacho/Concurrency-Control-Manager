#include "TransactionHandler.h"
#include "Common.h"
#include <iostream>

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

void TransactionHandler::callRandom(const int pID, const int pTimes)
{
    for (int i = 0; i < pTimes; i++)
    {
        // TODO: sleep random time
        int random = RandomInt((int)mTransactions.size());
        std::cout << "---- callRandom Thread " << pID << " " << random << std::endl;
        mTransactions[random].call();
    }
}

// TODO: x threads call callRandom(), pCount times
// repeat some number of times (pCount)
// select a transaction type randomly (callRandom)
// select object (flight and passenger id) for transaction randomly (is done in the transaction itself)
// invoke transaction (done in callRandom())

void TransactionHandler::run(const int pThreads, const int pCount)
{
    // pCount treads call callRandom
    //std::cout << "Started " <
    for (int i = 0; i < pThreads; i++)
    {
        std::thread* t = new std::thread(&TransactionHandler::callRandom, this,  i, pCount);
        t->join();
        mThreads.push_back(t);
    }
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}
