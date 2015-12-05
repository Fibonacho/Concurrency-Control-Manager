#include "Transaction.h"
#include "StorageUnit.h"
#include "Common.h"
#include <thread>

Transaction::Transaction(Function pFunction): mFunction(pFunction)
{
}
    
void Transaction::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit)
{
    mObjectLocks.push_back(ObjectLock(pLockingMode, pStorageUnit));
}


void Transaction::call()
{
    acquireLocks();
    mFunction();
    //std::thread t = GetCurrentThread();
    //t->sleep_for(1000);
    
    int r = RandomInt(1000000000);
    for (int i = 0; i < r; i++) {}
        
    releaseLocks();
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
                sleep(10); //try again later - should be handeled using an event listener
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
