//Database

#include "ILocks.h"

#ifndef CONCURRENCY_MANAGER_H
#define CONCURRENCY_MANAGER_H

// will manage the access to the relations by locking and unlocking instructions

class ConcurrencyManager //: public ILockManager
{
    //knows all locks on a specific database
    //decides if a lock can be aquired
    virtual bool getSL();
    virtual bool getXL();
};

#endif