#include "Lock.h"

Lock::Lock(): mLockingMode(LockingMode::unlocked) //, mLockOwner(nullptr)
{
}

void Lock::Exclusive() //const Transaction pTransaction)
{
    mLockingMode = LockingMode::exclusive;
    //mLockOwner = pTransaction;
}

void Lock::Shared() //const Transaction pTransaction)
{
    mLockingMode = LockingMode::shared;
    //mLockOwner = pTransaction;
}

void Lock::Release()
{
    mLockingMode = LockingMode::unlocked;
    //mLockOwner = nullptr;
}

// tell if locking mode is exclusive
bool Lock::isExclusiveLocked() const
{
    return (mLockingMode == LockingMode::exclusive);
}

// tell if locking mode is shared
bool Lock::isSharedLocked() const
{
    return (mLockingMode == LockingMode::shared);
}

// tell if resource is unlocked (locking mode is 0)
bool Lock::isUnlocked() const
{
    return (mLockingMode == LockingMode::unlocked);
}
