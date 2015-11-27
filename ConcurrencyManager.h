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

enum class LockingMode {
    unlocked = 0,
    shared = 1,
    exclusive = 2,
};

class ConcurrencyManager //: public ILockManager
{
    //knows all locks on a specific database
    //decides if a lock can be aquired
    virtual bool getSL(StorageUnit* storageUnit); //get lock on a specific storage unit
    virtual bool getXL(StorageUnit* storageUnit);
public:
    //virtual bool Read(); //Txn* txn, const Key& key) = 0;
    //virtual bool Write(); //Txn* txn, const Key& key) = 0;
    //virtual void Release(); //Txn* txn, const Key& key) = 0;
    
    // Sets '*owners' to contain the txn IDs of all txns holding the lock, and
    // returns the current LockMode of the lock: UNLOCKED if it is not currently
    // held, SHARED or EXCLUSIVE if it is, depending on the current state.
    //virtual LockMode Status(); //const Key& key, vector<Txn*>* owners) = 0;
};

#endif