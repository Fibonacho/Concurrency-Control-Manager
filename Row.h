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
// #include <iostream>
#include <mutex>

template <typename T>
class Row: public StorageUnit
{
private:
    T mData;
    //std::mutex mRead;
    //std::mutex mWrite;
public:
    T getData() const
    {
        // needs a shared lock
        return mData;
    }
    const T* getDataPtr() const
    {
        return &mData;
    }
    void setData(T pData) //this needs to lock
    {
        // needs an exclusive lock
        // std::lock_guard<std::mutex> guard(mWrite);
        mData = pData;
    }
    Row(StorageUnit* table): StorageUnit(table) {};
    Row(StorageUnit* table, T pData): StorageUnit(table), mData(pData) {}; //this doesn't need a lock
    virtual ~Row() { }
};

#endif
