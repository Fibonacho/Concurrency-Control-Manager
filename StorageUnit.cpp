#include "StorageUnit.h"
#include <iostream>

StorageUnit::StorageUnit(StorageUnit* parent): mParent(parent)
{
}

StorageUnit::~StorageUnit()
{
    // free all the memory of the storage unit
    for (auto child: mChilds)
    {
        if (child->mChilds.size() == 0) { }
    }
}

// returns true if the resource can be locked in exclusive mode (checks the locks of the childs / parents)
bool StorageUnit::ExclusiveLockable() const
{
    // check if the object itself is not locked in any mode
    if (!mLock.isUnlocked())
        return false;
        
    // the ressource can be locked in exclusive mode if no child and no parent is locked at all
    StorageUnit* mNode = mParent;
    // traverse over all parents until the root is reached
    while (mNode != nullptr)
    {
        // check if the parent is locked (shared or exclusive)
        if (!mNode->mLock.isUnlocked())
            return false;
        mNode = mNode->mParent;
    }
    return childsExclusiveLockable(this);
}

bool StorageUnit::childsSharedLockable(const StorageUnit* const pParent) const
{
    for (auto child: pParent->mChilds)
    {
        if (child != nullptr)
        {
            // should not be locked in exclusive mode
            if (child->mLock.isExclusiveLocked()) return false;
            
            // if the table is filled with data also check the rows of the table
            if (child->childCount() > 0)
            {
                if (!childsSharedLockable(child))
                    return false;
            }
        }
    }
    return true;
}

bool StorageUnit::childsExclusiveLockable(const StorageUnit* const pParent) const
{
    for (auto child: pParent->mChilds)
    {
        if (child != nullptr)
        {
            // should be unlocked
            if (!child->mLock.isUnlocked()) return false;
            
            // if the storage unit is filled with data (mChilds) also check those (recursively)
            if (child->childCount() > 0)
            {
                if (!childsExclusiveLockable(child)) return false;
            }
        }
    }
    return true;
}

// returns true if the resource can be locked in shared mode (checks the locks of the childs / parents)
bool StorageUnit::SharedLockable() const
{
    // check if the object itself is exclusively locked
    if (mLock.isExclusiveLocked())
        return false;
    
    // the source can be locked in shared mode if none child and parent is locked in exclusive mode (shared is fine)
    StorageUnit* mNode = mParent;
    // traverse over all parents until the root is reached
    while (mNode != nullptr)
    {
        // check if the parent is locked (shared or exclusive)
        if (mNode->mLock.isExclusiveLocked())
            return false;
        mNode = mNode->mParent;
    }
    // the resource can be locked in exclusive mode (if no child and no parent is locked at all)
    return childsSharedLockable(this);
}

const bool StorageUnit::isLeaf() const
{
    return mChilds.size() == 0;
}

const bool StorageUnit::isRoot() const
{
    return mParent == nullptr;
}

bool StorageUnit::LockExclusive()
{
    if (ExclusiveLockable())
    {
        mLock.SetExclusive();
        return true;
    }
    return false;
}

bool StorageUnit::LockShared()
{
    if (SharedLockable())
    {
        mLock.SetShared();
        return true;
    }
    return false;
}

void StorageUnit::ForceLockExclusive()
{
    // DO ONLY USE FOR TESTING!
    // DO ONLY USE FOR TESTING!
    // DO ONLY USE FOR TESTING!
    mLock.SetExclusive();
}

void StorageUnit::ForceLockShared()
{
    // DO ONLY USE FOR TESTING!
    // DO ONLY USE FOR TESTING!
    // DO ONLY USE FOR TESTING!
    mLock.SetShared();
}

void StorageUnit::ReleaseLocks()
{
    mLock.Release();
}

const bool StorageUnit::isEmpty() const
{
    return isLeaf(); // a leaf or e.g. table or database is empty
}

const unsigned long StorageUnit::childCount() const
{
    return mChilds.size();
}

StorageUnit* StorageUnit::getChild(const unsigned int pIndex)
{
    if (pIndex > childCount())
        return nullptr;
    else return mChilds[pIndex];
}

StorageUnit* StorageUnit::getFirstChild()
{
    if (isEmpty())
        return nullptr;
    else return mChilds[0];
}
