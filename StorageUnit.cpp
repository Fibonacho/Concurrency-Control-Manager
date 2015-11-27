#include "StorageUnit.h"
#include <iostream>

StorageUnit::StorageUnit(StorageUnit* parent): mParent(parent)
{
}

StorageUnit::~StorageUnit()
{
    // free all the memory of the storage unit
    std::cout << "~StorageUnit" << std::endl;
    for (auto child: mChilds)
        delete child;
    delete mParent;
}

const bool StorageUnit::isLeaf() const
{
    return mChilds.size() == 0;
}

const bool StorageUnit::isRoot() const
{
    return mParent == nullptr;
}

const unsigned long StorageUnit::childCount() const
{
    return mChilds.size();
}
