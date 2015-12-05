//  ---------------------------------------------------
//  Transaction:
//  - a transaction has a locking mode
//  - a transaction can acquire a lock for a storage unit
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "Lock.h"
#include <vector>
#include <thread>

class StorageUnit;
class Transaction
{
private:
    // c++ function pointer to a function with no arguments and the return value void (none)
    typedef void (*Function)(void);
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
    // release a lock, i.e. set locking mode to 0 = Lock::LockingMode::unlocked
    void releaseLocks();
    // tell if an object is unlocked, returns true if none of the elements in mObjectLocks is locked, false if any object is locked in any mode
    bool isUnlocked() const;
    
    std::vector<ObjectLock> mObjectLocks;
    Function mFunction;
public:
    Transaction(Function pFunction);
    
    void addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit);
    // call a transaction
    // - first acquire all locks
    // - then execute the function using the function pointer
    // - in the end release the lock again
    void call();
};

#endif
