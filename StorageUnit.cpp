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
        if (child != nullptr)
            delete child;
    if (mParent != nullptr)
        delete mParent;
}

/*const Lock StorageUnit::getLock() const
{
    return mLock;
}*/

// tell if storage unit is a leaf (i.e. has NO children)
const bool StorageUnit::isLeaf() const
{
    return mChilds.size() == 0;
}

// tell if storage unit is root (i.e. has no parent)
const bool StorageUnit::isRoot() const
{
    return mParent == nullptr;
}

// tell if storage unit is empty
const bool StorageUnit::isEmpty() const
{
    return isLeaf(); // a leaf or e.g. table or database is empty
}

// tell number of children (e.g. number of rows in a table)
const unsigned long StorageUnit::childCount() const
{
    return mChilds.size();
}
