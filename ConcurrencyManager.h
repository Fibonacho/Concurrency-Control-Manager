//  ---------------------------------------------------
//  ConcurrencyManager:
//  - will manage the access to the relations by locking and unlocking instructions
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef CONCURRENCY_MANAGER_H
#define CONCURRENCY_MANAGER_H

#include "StorageUnit.h"

class ConcurrencyManager //: public ILockManager
{
    std::vector<Lock*> mLocks; // maybe useful
    // knows all locks on a specific database
    // decides if a lock can be aquired
    bool getSharedLock(StorageUnit* pStorageUnit); //get lock on a specific storage unit
    bool getExclusiveLock(StorageUnit* pStorageUnit);
    void releaseLock(StorageUnit* pStorageUnit);
public:

};

#endif