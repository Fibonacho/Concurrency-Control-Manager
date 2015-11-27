//  ---------------------------------------------------
//  StorageUnit:
//  - represents a storage unit in the databse
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

#include <list>

class StorageUnit //: public ILockable
{
protected:
    //childs
    std::list<StorageUnit*> mChilds;
    //parent of the storage unit, nullptr for the root = the database itself
    StorageUnit* mParent;
    
    bool isLeaf() const;
    bool isRoot() const;
public:
    StorageUnit(StorageUnit* parent);
    virtual ~StorageUnit();
};

#endif