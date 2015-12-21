//  ---------------------------------------------------
//  Lock:
//  - this class stores the lock modes etc.
//  - but does NOT know about their logic
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

class Transaction;
class Lock
{
public:
    enum class LockingMode {
        unlocked = 0,
        shared = 1,
        exclusive = 2,
    };
    
    Lock();
    
    void SetExclusive(Transaction* pTransaction);
    void SetShared(Transaction* pTransaction);
    bool Upgrade(Transaction* pTransaction);
    bool isOwner(Transaction* pTransaction, LockingMode pLockingMode) const;
    void Release();
    
    // returns true if locking mode is exclusive
    bool isExclusiveLocked() const;
    // returns true if locking mode is shared
    bool isSharedLocked() const;
    // returns true if the resource is unlocked (locking mode is 0)
    bool isUnlocked() const;
private:
    Transaction* mLockOwner;
    LockingMode mLockingMode;
};

#endif
