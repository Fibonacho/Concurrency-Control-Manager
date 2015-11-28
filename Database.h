//  ---------------------------------------------------
//  Database:
//  - The database has a concurrencyManager where locks are aquired
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
#include "ConcurrencyManager.h"

class Database: public StorageUnit
{
private:
    ConcurrencyManager mConcurrencyManager;
public:
    void AddTable(StorageUnit& table);
    Database();
};

#endif
