//  ---------------------------------------------------
//  Command:
//  - each command has locks
//  - a command can acquire a lock for a storage unit
//
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


#include "Lock.h"
#include <vector>
//#inclue "LogFile.h"
#include <mutex>

class StorageUnit;
class Transaction;
class Command
{
private:
    //LogFile* mLogFile;
    typedef bool (*Function)(void);
    Function mFunction;
    // the parent of the command
    Transaction* const mTransaction;
    std::mutex m;
    
    struct ObjectLock
    {
        Lock::LockingMode mLockingMode;
        StorageUnit* const mStorageUnit;
        
        ObjectLock(Lock::LockingMode pLockingMode, StorageUnit* const pStorageUnit): mLockingMode(pLockingMode), mStorageUnit(pStorageUnit) {}
    };
    std::vector<ObjectLock> mObjectLocks;
    
    // acquire a lock for a storage unit
    // if an object should be locked exclusively, it has to be unlocked before, try again later
    // if an object has to be locked in shared mode, it only has to be NOT in exclusive lock mode
    void acquireLocks();
public:
    Command(Transaction* const pTransaction, Function pFunction); //, LogFile* pLogFile);
    Command(const Command& pCommand); // LogFile* pLogFile);
   
    // release the locks stored in the object lock list
    void releaseLocks();
    // call a command
    // - first acquire all locks
    // - then execute the function using the function pointer
    // - the locks are not released yet; this is done in the transaction itself
    void call();
    // add a necessary object lock to the list / those storage units added will be acquired before the command is executed
    void addObjectLock(Lock::LockingMode pLockingMode, StorageUnit* const pStorageUnit);
};

#endif
