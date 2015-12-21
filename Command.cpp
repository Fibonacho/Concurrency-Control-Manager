#include "Command.h"
#include "StorageUnit.h"
// #include <iostream>
#include <thread>
#include "Common.h"
#include "Transaction.h"
//#include "LogFile.h"
#include <iostream>

Command::Command(Transaction* const pTransaction, Function pFunction): mTransaction(pTransaction), mFunction(pFunction)
{
     mTransaction->addCommand(this);
}

Command::Command(const Command& pCommand): mTransaction(pCommand.mTransaction), mFunction(pCommand.mFunction)
{
}

void Command::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* const pStorageUnit)
{
    mObjectLocks.push_back(ObjectLock(pLockingMode, pStorageUnit));
}

void Command::acquireLocks()
{
    // could take a while (because the command is maybe waiting)
    for (auto objectLock: mObjectLocks)
    {
        bool locked = false;
        while (!locked)
        {
            // check if storage unit is not already locked
            // StorageUnit::Exclusive checks if the lock can be given and locks returns true / false if successful
            m.lock();
            bool XL = (objectLock.mLockingMode == Lock::LockingMode::exclusive) && objectLock.mStorageUnit->LockExclusive(mTransaction);
            bool SL = (objectLock.mLockingMode == Lock::LockingMode::shared) && objectLock.mStorageUnit->LockShared(mTransaction);
            locked = (XL || SL);
            
            // check for lock upgrades
            // check for upgrades
            if ((!locked) && (objectLock.mLockingMode == Lock::LockingMode::exclusive))
            {
                // Lockupgrade
                bool l = objectLock.mStorageUnit->LockUpgrade(mTransaction);
                locked = l;
            }
            m.unlock();
            
            if (!locked)
            {
                std::cout << "waiting ... " << std::endl;
                //mLogFile->write("waiting ...");
                std::this_thread::sleep_for(std::chrono::milliseconds(50)); // try again in a second
            }
        }
    }
}

void Command::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->ReleaseLocks();
}

void Command::call()
{
    acquireLocks();
    //m.lock();
    mFunction();
    //m.unlock();
    int waitingTime = RandomInt(100);
    auto a = (waitingTime/100.0);
    // mLogFile->write("Command::call - duration: " + std::to_string(a) + " seconds");
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
    // the locks are not release - they are released at the end (after all commands are executed)
}
