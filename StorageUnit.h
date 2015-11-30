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
    const bool isLeaf() const;
    const bool isRoot() const;
    const unsigned long childCount() const;
public:
    Lock mLock;
    const bool isEmpty() const;
    StorageUnit(StorageUnit* parent);
    virtual ~StorageUnit();
};

#endif