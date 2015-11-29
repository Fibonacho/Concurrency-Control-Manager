//  ---------------------------------------------------
//  Transaction:
//  -
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

class StorageUnit;

class Transaction
{
private:
    typedef void (*Function)(void);
    
    struct ObjectLock //create new file for this
    {
        Lock::LockingMode mLockingMode;
        StorageUnit* mStorageUnit;
        
        ObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit): mLockingMode(pLockingMode), mStorageUnit(pStorageUnit) {}
    };
    
    std::vector<ObjectLock> mObjectLocks;
    Function mFunction;
public:
    Transaction(Function pFunction);
    
    void addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* pStorageUnit);
    void call();
    void acquireLocks();
    void releaseLocks();
    bool ObjectsUnlocked();
};

#endif
