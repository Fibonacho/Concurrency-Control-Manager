#include "Transaction.h"
#include "StorageUnit.h"
#include "Common.h"

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
            if ((objectLock.mLockingMode == Lock::LockingMode::exclusive) && objectLock.mStorageUnit->mLock.isUnlocked())
            {
                objectLock.mStorageUnit->mLock.Exclusive();
                locked = true;
            }
            else if ((objectLock.mLockingMode == Lock::LockingMode::shared) && (!objectLock.mStorageUnit->mLock.isExclusiveLocked()))
            {
                objectLock.mStorageUnit->mLock.Shared();
                locked = true;
            }
            else sleep(10); //try again later
        }
    }
}
    
void Transaction::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->mLock.Release();
}

bool Transaction::isUnlocked() const
{
    for (auto objectLocks: mObjectLocks)
    {
        if (objectLocks.mStorageUnit->mLock.isExclusiveLocked() || objectLocks.mStorageUnit->mLock.isSharedLocked())
            return false;
    }
    return true;
}
