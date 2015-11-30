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

// call a transaction
// - first acquire all locks
// - then execute the function
// - and in the end release the lock again
void Transaction::call()
{
    acquireLocks();
    mFunction();
    releaseLocks();
}

// acquire a lock for a storage unit
// if an object should be locked exclusively, it has to be unlocked before
// if an object has to be locked in shared mode, it only has to be NOT in exclusive lock mode
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
            else Sleep(10); //try again later
        }
    }
}
    
// release a lock, i.e. set locking mode to 0
void Transaction::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->mLock.Release();
}

// tell if an object is unlocked
bool Transaction::isUnlocked() const
{
    for (auto objectLocks: mObjectLocks)
    {
        if (objectLocks.mStorageUnit->mLock.isExclusiveLocked() || objectLocks.mStorageUnit->mLock.isSharedLocked())
            return false;
    }
    return true;
}
