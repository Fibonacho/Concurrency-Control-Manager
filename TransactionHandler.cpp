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
    //std::lock_guard<std::mutex> locker(m);
    size_t s = mTransactions.size();
    
    if (s > 0)
    {
        for (int i = 0; i < pTimes; i++)
        {
            //m.lock();
            int random = RandomInt((int)mTransactions.size());
            Transaction* t = new Transaction(mTransactions[random]);
            t->call(); //local variable
            
            delete t;
            //m.unlock();
            //mTransactions[random].call();
        }
    }
}

void TransactionHandler::work()
{
    //std::lock_guard<std::mutex> guard(m);
    //m.lock();
    int i = 0;
    while (!mQueue.empty())
    {
        //m.unlock();
        //m.lock();
        Transaction* t = mQueue.front();
        mQueue.pop();
        //m.unlock();
        
        t->call();
        
        //m1.lock();
        //std::cout << std::this_thread::get_id() << ": " << i << std::endl;
        //m1.unlock();
        
        i++;
    }
    //delete t;
    
    //m1.lock();
    //std::cout << "I am " <<  std::this_thread::get_id() << " and I did " << i << " transactions. " << std::endl;
    //m1.unlock();
}

void TransactionHandler::run(const int pThreads, const int pCount)
{
    size_t s = mTransactions.size();
    if (s > 0)
    {
        for (int i = 0; i < pCount; i++) //add pCount random transactions to the queue
        {
            int random = RandomInt((int)mTransactions.size());
            Transaction* t = new Transaction(mTransactions[random]);
            //m.lock();
            mQueue.push(t);
            //m.unlock();
        }
    }

    // mQueue
    // now create pThreads threads:
    for (int i = 0; i < pThreads; i++)
    {
        // pCount threads call callRandom
        std::thread* t = new std::thread(&TransactionHandler::work, this);
        mThreads.push_back(t);
    }
    
    int i = 0;
    for (auto thread: mThreads)
    {
        thread->join();
        //std::cout needs a lock
        std::cout << " done " << i << std::endl;
        i++;
    }
}

void TransactionHandler::addTransaction(Transaction pTransaction)
{
    mTransactions.push_back(pTransaction);
}

