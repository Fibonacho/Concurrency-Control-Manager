#include "Lock.h"

Lock::Lock(): mLockingMode(LockingMode::unlocked), mLockOwner(nullptr)
{
}

void Lock::Exclusive(const Transaction pTransaction)
{
    mLockingMode = LockingMode::exclusive;
    mLockOwner = pTransaction;
}

void Lock::Shared(const Transaction pTransaction)
{
    mLockingMode = LockingMode::shared;
    mLockOwner = pTransaction;
}

void Lock::Release()
{
    mLockingMode = LockingMode::unlocked;
    mLockOwner = nullptr;
}

