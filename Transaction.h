//  ---------------------------------------------------
//  Transaction:
//  - a transaction has a locking mode
//  - a transaction can acquire a lock for a storage unit
//
//  Advanced Databases: Assignment 3 Concurrency Control
//
//
//  Johanna Wald  1520979  johanna.wald@stud.sbg.ac.at
//  Elvis Milas   1223926  elvis.milas@stud.sbg.ac.at
//  Eva Lugstein  1121035  eva.lugstein2@stud.sbg.ac.at
//  ---------------------------------------------------

#ifndef TRANSACTION_H
#define TRANSACTION_H


#include <vector>
#include "Command.h"
// a list of commands (each command has locks)

class StorageUnit;

class Transaction
{
private:
    // c++ function pointer to a function with no arguments and the return value void (none)
    std::vector<Command*> mCommands;
    
    // release a lock, i.e. set locking mode to 0 = Lock::LockingMode::unlocked
    void releaseLocks();
public:
    Transaction(); //Function pFunction
    void addCommand(Command* pCommand);
    void call();
};

#endif
