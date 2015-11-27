//  ---------------------------------------------------
//  Table:
//  - mChilds from StorageUnit are the Rows of the Table
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef TABLE_H
#define TABLE_H

#include "StorageUnit.h"
#include "Database.h"

class Table: public StorageUnit
{
    int mID;
public:
    Table(Database& database): StorageUnit(database), mID(0)
    {
       // database.AddTable(*this);
    };
    
    void addRow(StorageUnit* row) {
        //check if id has already been taken!?
        this->mChilds.push_back(row);
    }
protected:
    int getNewID()
    {
        mID++;
        return mID;
    }
};

#endif
