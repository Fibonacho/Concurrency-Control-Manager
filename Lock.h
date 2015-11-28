//  ---------------------------------------------------
//  Lock:
//  - this class stores the lock modes etc. but doesn't know about their logic
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef LOCK_H
#define LOCK_H

typedef void (*Transaction)(void);

class Lock
{
public:
    enum class LockingMode {
        unlocked = 0,
        shared = 1,
        exclusive = 2,
    };
    
    Lock();
    
    void Exclusive(const Transaction pTransaction);
    void Shared(const Transaction pTransaction);
    void Release();
private:
    LockingMode mLockingMode;
    // if LockingMode is unlocked the lockOwner has to be nullptr
    Transaction mLockOwner;
};

#endif
