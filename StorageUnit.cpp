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

// returns true if the resource can be locked in exclusive mode (checks the locks of the childs / parents)
bool StorageUnit::ExclusivelyLockable() const
{
    // the ressource can be locked in exclusive mode if no child and no parent is locked at all
    StorageUnit* mNode = mParent;
    // tranverse over all parents until the root is reached
    while (mNode != nullptr)
    {
        // check if the parent is locked (shared or exclusive)
        if (!mNode->mLock.isUnlocked())
            return false;
        mNode = mNode->mParent;
    }
    
    for (auto child: mChilds)
    {
        if (child != nullptr)
        {
            if (!child->mLock.isUnlocked())
                return false;
        }
    }
    return true;
}

// returns true if the resource can be locked in shared mode (checks the locks of the childs / parents)
bool StorageUnit::SharedLockable() const
{
    // the source can be locked in shared mode if none child and parent is locked in exclusive mode (shared is fine)
    // the ressource can be locked in exclusive mode if no child and no parent is locked at all
    StorageUnit* mNode = mParent;
    // tranverse over all parents until the root is reached
    while (mNode != nullptr)
    {
        // check if the parent is locked (shared or exclusive)
        if (mNode->mLock.isExclusiveLocked())
            return false;
        mNode = mNode->mParent;
    }
    
    for (auto child: mChilds)
    {
        if (child != nullptr)
        {
            if (child->mLock.isExclusiveLocked())
                return false;
        }
    }
    return true;
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
