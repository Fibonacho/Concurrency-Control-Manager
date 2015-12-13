#include "Lock.h"
#include "Transaction.h"

Lock::Lock(): mLockingMode(LockingMode::unlocked), mLockOwner(nullptr)
{
}

void Lock::SetExclusive(Transaction* pTransaction)
{
    mLockingMode = LockingMode::exclusive;
    mLockOwner = pTransaction;
}

void Lock::SetShared(Transaction* pTransaction)
{
    mLockingMode = LockingMode::shared;
    mLockOwner = pTransaction;
}

bool Lock::Upgrade(Transaction* pTransaction)
{
    if (mLockingMode == LockingMode::shared)
    {
        if (mLockOwner == pTransaction)
        {
            mLockingMode = LockingMode::exclusive;
            return true;
        }
    }
    return false;
}

bool Lock::isOwner(Transaction* pTransaction, LockingMode pLockingMode)
{
    return ((mLockOwner == pTransaction) && (pLockingMode == mLockingMode));
}

void Lock::Release()
{
    mLockingMode = LockingMode::unlocked;
    mLockOwner = nullptr;
}

bool Lock::isExclusiveLocked() const
{
    return (mLockingMode == LockingMode::exclusive);
}

bool Lock::isSharedLocked() const
{
    return (mLockingMode == LockingMode::shared);
}

bool Lock::isUnlocked() const
{
    return (mLockingMode == LockingMode::unlocked);
}
