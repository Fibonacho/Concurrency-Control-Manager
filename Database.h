//  ---------------------------------------------------
//  Database:
//  - a database has a ConcurrencyManager where
//    (exclusive and shared) locks are aquired
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include "StorageUnit.h"

class LockManager;
class Database: public StorageUnit
{
private:
    //add a pointer to a lock manager
    LockManager* const mLockManager;
public:
    // adds a table to the childs of the database, this is called automatically in the constructor of the table
    void AddTable(StorageUnit* table);
    Database(LockManager* const pLockManager);
    virtual ~Database();
};

#endif
