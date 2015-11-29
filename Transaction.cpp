#include "Transaction.h"
#include "StorageUnit.h"

Transaction::Transaction(Function pFunction): mFunction(pFunction)
{
}
    
void Transaction::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit)
{
    mObjectLocks.push_back(ObjectLock(pLockingMode, pStorageUnit));
}
    
void Transaction::call()
{
    mFunction();
}
    
void Transaction::acquireLocks()
{
    for (auto objectLocks: mObjectLocks)
    {
        if (objectLocks.mLockingMode == Lock::LockingMode::exclusive)
            objectLocks.mStorageUnit->mLock.Exclusive();
        else if (objectLocks.mLockingMode == Lock::LockingMode::shared)
            objectLocks.mStorageUnit->mLock.Shared();
    }
}
    
void Transaction::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->mLock.Release();
}

bool Transaction::ObjectsUnlocked()
{
    for (auto objectLocks: mObjectLocks)
    {
        if (objectLocks.mStorageUnit->mLock.isExclusiveLocked() || objectLocks.mStorageUnit->mLock.isSharedLocked())
            return false;
    }
    return true;
}
