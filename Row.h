//  ---------------------------------------------------
//  Row:
//  - is a leaf
//  - parent is the table
//  - T is the type of the value
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef ROW_H
#define ROW_H

#include "StorageUnit.h"

template <typename T>
class Row: public StorageUnit
{
public:
    T mData;
    Row(StorageUnit& table): StorageUnit(table) {};
    
    
};

#endif
