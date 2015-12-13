#include "Command.h"
#include "StorageUnit.h"
#include <iostream>
#include <thread>
#include "Common.h"
#include "Transaction.h"

Command::Command(Transaction* pTransaction, Function pFunction): mTransaction(pTransaction), mFunction(pFunction)
{
     mTransaction->addCommand(this);
}

void Command::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit)
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
            
            if (!locked)
            {
                std::cout << "waiting ..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // try again in a second
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
    mFunction();
    int waitingTime = RandomInt(100);
    std::cout << "function waits " << waitingTime/1000.0 << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
    // the locks are not release - they are released at the end (after all commands are executed)
}
