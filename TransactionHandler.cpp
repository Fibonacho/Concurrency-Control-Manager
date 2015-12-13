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
    for (auto transaction: mTransactions)
    {
        transaction.call();
    }
}

void TransactionHandler::callRandom(const unsigned int pTimes)
{
    if (mTransactions.size() > 0)
    {
        for (int i = 0; i < pTimes; i++)
        {
            int random = RandomInt((int)mTransactions.size());
            mTransactions[random].call();
        }
    }
}

void TransactionHandler::run(const int pThreads, const int pCount)
{
    // pThreads are executed
    for (int i = 0; i < pThreads; i++)
    {
        // pCount threads call callRandom
        std::thread* t = new std::thread(&TransactionHandler::callRandom, this, pCount);
        mThreads.push_back(t);
    }
    
    for (auto thread: mThreads)
        thread->join();
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}

