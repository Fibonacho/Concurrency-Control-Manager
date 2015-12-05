#include "Transaction.h"
#include "StorageUnit.h"
#include "Common.h"
#include <iostream>

Transaction::Transaction(Function pFunction): mFunction(pFunction)
{
}
    
void Transaction::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit)
{
    mObjectLocks.push_back(ObjectLock(pLockingMode, pStorageUnit));
}


void Transaction::call(const unsigned i)
{
    acquireLocks();
    mFunction();

    int waitingTime = RandomInt(100);
    std::cout << "function waits " << waitingTime/1000.0 << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
    
    releaseLocks();
    std::cout << "Transaction " << i << " call successfully completed " << std::endl;
}

void Transaction::acquireLocks()
{
    // could take a while
    for (auto objectLock: mObjectLocks)
    {
        bool locked = false;
        while (!locked)
        {
            // check if storage unit is not already locked
            // StorageUnit::Exclusive checks if the lock can be given and locks returns true / false if successful
            bool XL = (objectLock.mLockingMode == Lock::LockingMode::exclusive) && objectLock.mStorageUnit->LockExclusive();
            bool SL = (objectLock.mLockingMode == Lock::LockingMode::shared) && objectLock.mStorageUnit->LockShared();
            locked = (XL || SL);

            if (!locked)
            {
                std::cout << "waiting ..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // try again in a second
            }
        }
    }
}

void Transaction::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->ReleaseLocks();
}

bool Transaction::isUnlocked() const
{
    for (auto objectLocks: mObjectLocks)
    {
        if (objectLocks.mStorageUnit->ExclusiveLockable())
            return false;
    }
    return true;
}
