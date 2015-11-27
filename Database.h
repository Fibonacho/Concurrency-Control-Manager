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

#include <list>
#include "Table.h"
#include "Instruction.h"
#include "StorageUnit.h"
#include "ConcurrencyManager.h"

class Database: public StorageUnit
{
private:
    //LockManager of the database where locks are managed
    ConcurrencyManager mConcurrencyManager;
    std::list<Instruction> mInstructions;
public:
    void AddTable(StorageUnit& table);
    
    Database();

    //void CreateBookingDB(); -> our database is then a specific database of
};

#endif