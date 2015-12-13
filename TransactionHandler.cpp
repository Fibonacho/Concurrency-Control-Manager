#include "TransactionHandler.h"
#include "Common.h"
#include <sstream>
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
    for (unsigned int i = 0; i < pTimes; i++)
    {
        int random = RandomInt((int)mTransactions.size());
        mTransactions[random].call();
    }
}

void TransactionHandler::run(const int pThreads, const int pCount)
{
    // pThreads are executed
    for (int i = 0; i < pThreads; i++)
    {
        // pCount threads call callRandom
        std::thread* t = new std::thread(&TransactionHandler::callRandom, this, pCount);

        // store thread id and begin time of thread
        mRuntime.mID = t->get_id();
        mRuntime.mTimepoint = std::chrono::high_resolution_clock::now();
        mThreadRuntime.push_back(mRuntime);

        mThreads.push_back(t);
    }
    
    for (auto thread: mThreads)
    {
        thread->join();
        std::chrono::high_resolution_clock::time_point begin = mRuntime.mTimepoint;
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();

        // TODO: update mRuntime.mTimepoint with runtime (end - begin)
    }
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}

void TransactionHandler::printRuntimes()
{
    for (auto runtime: mThreadRuntime)
    {
        // print runtime.mTimepoint (to string)
    }
}