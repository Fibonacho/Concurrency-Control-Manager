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
        transaction.call();
}

void TransactionHandler::callRandom(const int pID, const int pTimes)
{
    for (int i = 0; i < pTimes; i++)
    {
        int random = RandomInt((int)mTransactions.size());
        std::cout << "---- callRandom Thread " << pID << " " << random << std::endl;
        mTransactions[random].call();
        // sleep random time - between 1 and 10 seconds
        int r = RandomInt(10) + 1;
        std::cout << "sleep for " << r << " seconds " << std::endl;
        sleep(r);
    }
}

void TransactionHandler::run(const int pThreads, const int pCount)
{
    // pThreads are executed
    for (int i = 0; i < pThreads; i++)
    {
        std::cout << "Loop " << i << std::endl;
        // pCount threads call callRandom
        std::thread* t = new std::thread(&TransactionHandler::callRandom, this, i, pCount);
        t->join();
        //std::cout << "Thread started " << std::endl;
        mThreads.push_back(t);
    }
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}

