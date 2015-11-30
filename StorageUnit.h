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
    Lock mLock;
    // tell if storage unit is empty
    const bool isEmpty() const;
    StorageUnit(StorageUnit* parent);
    virtual ~StorageUnit();
};

#endif