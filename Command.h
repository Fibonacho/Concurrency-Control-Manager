//  ---------------------------------------------------
//  Command:
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef COMMAND_H
#define COMMAND_H

// a list of commands (each command has locks)

#include "Lock.h"
#include <vector>

class StorageUnit;
class Command
{
private:
    typedef bool (*Function)(void);
    
    //std::thread* mThread;
    struct ObjectLock
    {
        Lock::LockingMode mLockingMode;
        StorageUnit* mStorageUnit;
        
        ObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit): mLockingMode(pLockingMode), mStorageUnit(pStorageUnit) {}
    };
    // acquire a lock for a storage unit
    // if an object should be locked exclusively, it has to be unlocked before, try again later
    // if an object has to be locked in shared mode, it only has to be NOT in exclusive lock mode
    void acquireLocks();
    //void releaseLocks();
    
    std::vector<ObjectLock> mObjectLocks;
    Function mFunction;
public:
    void addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit);
    
    void call();
    void releaseLocks();
    
    // call a transaction
    // - first acquire all locks
    // - then execute the function using the function pointer
    // - in the end release the lock again
    Command(Function pFunction);
};

#endif
