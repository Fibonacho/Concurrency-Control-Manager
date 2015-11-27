//  ---------------------------------------------------
//  Row:
//  - is the leaf of the store unit tree
//  - the parent of a row is a table
//  - T is the type of the value stored in the row
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
#include <iostream>

template <typename T>
class Row: public StorageUnit
{
public:
    T mData;
    Row(StorageUnit& table): StorageUnit(table) {};
    ~Row() {std::cout << "row destructor " << std::endl;}
};

#endif
