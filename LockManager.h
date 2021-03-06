//  ---------------------------------------------------
//  LockManager:
//  - knows about all locks
//  - could potentially handle dead locks
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef LOCKMANAGER_H
#define LOCKMANAGER_H

class LockManager
{
public:
    LockManager();
    virtual ~LockManager();
};

#endif