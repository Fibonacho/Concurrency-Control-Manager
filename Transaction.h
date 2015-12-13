//  ---------------------------------------------------
//  Transaction:
//  - a transaction is a list of commands (they have object locks)
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

class StorageUnit;

class Transaction
{
private:
    // c++ function pointer to a function with no arguments and the return value void (none)
    std::vector<Command*> mCommands;
    
    // release all locks of each command (i.e. set locking mode to 0 = Lock::LockingMode::unlocked)
    void releaseLocks();
public:
    Transaction(); //Function pFunction
    // add a command to the transaction
    void addCommand(Command* pCommand);
    // call all command in the command list (iterates over all commands and "calls" them and then releases the locks again)
    void call();
};

#endif
