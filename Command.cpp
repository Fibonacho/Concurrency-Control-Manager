#include "Command.h"
#include "StorageUnit.h"
#include <iostream>
#include <thread>
#include "Common.h"

Command::Command(Function pFunction): mFunction(pFunction)
{
}

void Command::addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit)
{
    mObjectLocks.push_back(ObjectLock(pLockingMode, pStorageUnit));
}

void Command::acquireLocks()
{
    // could take a while (because the command is maybe waiting)
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
            {
                std::cout << "waiting ..." << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(10)); // try again in a second
            }
        }
    }
}

void Command::releaseLocks()
{
    for (auto objectLocks: mObjectLocks)
        objectLocks.mStorageUnit->ReleaseLocks();
}

void Command::call()
{
    acquireLocks();
    mFunction();
    int waitingTime = RandomInt(100);
    std::cout << "function waits " << waitingTime/1000.0 << " seconds" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(waitingTime));
    // the locks are not release - they are released at the end (after all commands are executed)
}
