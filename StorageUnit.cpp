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

// returns true if the resource can be locked in exclusive mode (checks the locks of the childs / parents)
bool StorageUnit::allowExclusiveLock() const
{
    // the ressource can be locked in exclusive mode if none child and parent is locked at all
    return false;
}

// returns true if the resource can be locked in shared mode (checks the locks of the childs / parents)
bool StorageUnit::allowSharedLock() const
{
    // the source can be locked in shared mode if none child and parent is locked in exclusive mode (shared is fine)
    return false;
}

const bool StorageUnit::isLeaf() const
{
    return mChilds.size() == 0;
}

const bool StorageUnit::isRoot() const
{
    return mParent == nullptr;
}

const bool StorageUnit::isEmpty() const
{
    return isLeaf(); // a leaf or e.g. table or database is empty
}

const unsigned long StorageUnit::childCount() const
{
    return mChilds.size();
}
