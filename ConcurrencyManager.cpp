//Table

#include "ConcurrencyManager.h"

bool ConcurrencyManager::getSharedLock(StorageUnit* pStorageUnit)
{
    // add item to mLocks
    // this function waits until the lock is acquired
    return false;
}

bool ConcurrencyManager::getExclusiveLock(StorageUnit* pStorageUnit)
{
    // add item to mLocks
    // this function waits until the lock is acquired
    return false;
}

void ConcurrencyManager::releaseLock(StorageUnit* pStorageUnit)
{
    // remove item from mLocks
}
