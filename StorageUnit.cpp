#include "StorageUnit.h"

StorageUnit::StorageUnit(StorageUnit* parent): mParent(parent)
{
}

StorageUnit::~StorageUnit()
{
    // free all the memory of the storage unit
    for (auto child: mChilds)
        delete child;
    delete mParent;
}

bool StorageUnit::isLeaf() const
{
    return mChilds.size() == 0;
}

bool StorageUnit::isRoot() const
{
    return mParent == nullptr;
}
