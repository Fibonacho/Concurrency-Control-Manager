//  ---------------------------------------------------
//  Database:
//  - comment todo
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
    //LockManager of the database where locks are managed
    ConcurrencyManager mConcurrencyManager;
public:
    void AddTable(StorageUnit& table);
    //add bedingung?!
    //static void CreaetBookingDB();
    Database();

    //void CreateBookingDB(); -> our database is then a specific database of
};

#endif