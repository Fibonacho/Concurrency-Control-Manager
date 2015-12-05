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
private:
    int mID;
public:
    bool mDataConsoleOutput = false;
    
    Table(Database* database);
    virtual ~Table();
    void addRow(StorageUnit* row);
    long getRowCount();
protected:
    int getNewID();
};

#endif
