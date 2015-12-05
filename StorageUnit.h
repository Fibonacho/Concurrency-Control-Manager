//  ---------------------------------------------------
//  StorageUnit:
//  - represents a storage unit in the database
//  - a storage unit has a parent and can have children
//  - if childs are empty the storage unit is a leaf
//  - if the root is null, the storage unit is the
//    database itself
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef STORAGEUNIT_H
#define STORAGEUNIT_H

#include <vector>
#include "Lock.h"

class StorageUnit
{
private:
    // lock object
    Lock mLock;
    // checks recursively if the childs of pParent are lockable in exclusive mode
    bool childsExclusiveLockable(const StorageUnit* const pParent) const;
    // checks recursively if the childs of pParent are lockable in shared mode
    bool childsSharedLockable(const StorageUnit* const pParent) const;
protected:
    std::vector<StorageUnit*> mChilds;
    StorageUnit* mParent;
    // returns true if the storage unit is a leaf (i.e. has NO children)
    const bool isLeaf() const;
    // returns if the storage unit is root (i.e. has no parent)
    const bool isRoot() const;
    // get number of children (e.g. number of rows in a table)
    const unsigned long childCount() const;
public:
    // returns true if the resource can be locked in exclusive mode (checks the locks of the childs / parents)
    bool ExclusiveLockable() const;
    // returns true if the resource can be locked in shared mode (checks the locks of the childs / parents)
    bool SharedLockable() const;
    
    // set the lock to exclusive or shared after checking if it's even allowed
    bool LockExclusive();
    bool LockShared();
    // releases the locks
    void ReleaseLocks();
    
    // DO ONLY USE FOR TESTING!
    // sets the lock to exclusive or shared (attention: does not check if it's even ok - conflicts are possible)
    void ForceLockExclusive();
    void ForceLockShared();
    
    // tell if storage unit is empty
    const bool isEmpty() const;
    
    StorageUnit* getChild(const unsigned int pIndex);
    StorageUnit* getFirstChild();
    StorageUnit(StorageUnit* parent);
    virtual ~StorageUnit();
};

#endif