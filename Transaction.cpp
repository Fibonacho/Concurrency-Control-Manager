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
            // StorageUnit::Exclusive checks if the lock can be given and locks returns true / false if successful
            //bool exclusive =
            locked = (((objectLock.mLockingMode == Lock::LockingMode::exclusive) && objectLock.mStorageUnit->LockExclusive()) ||
                      ((objectLock.mLockingMode == Lock::LockingMode::shared) && (objectLock.mStorageUnit->LockShared()) ));
            /*{
                //objectLock.mStorageUnit->mLock.Exclusive();
                locked = true;
            }*/
            /*else if ((objectLock.mLockingMode == Lock::LockingMode::shared) && (!objectLock.mStorageUnit->Shared()))
            {
                //objectLock.mStorageUnit->mLock.Shared();
                locked = true;
            }*/
            if (!locked)
                sleep(10); //try again later
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
