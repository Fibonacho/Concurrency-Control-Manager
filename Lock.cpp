#include "Lock.h"

Lock::Lock(): mLockingMode(LockingMode::unlocked) //, mLockOwner(nullptr)
{
}

void Lock::SetExclusive() //const Transaction pTransaction)
{
    mLockingMode = LockingMode::exclusive;
    //mLockOwner = pTransaction;
}

void Lock::SetShared() //const Transaction pTransaction)
{
    mLockingMode = LockingMode::shared;
    //mLockOwner = pTransaction;
}

void Lock::Release()
{
    mLockingMode = LockingMode::unlocked;
    //mLockOwner = nullptr;
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
