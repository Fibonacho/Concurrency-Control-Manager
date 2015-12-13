#include "Transaction.h"
#include "StorageUnit.h"
#include <iostream>
#include "Command.h"
#include <thread>

Transaction::Transaction()
{
}

void Transaction::call()
{
    for (auto command: mCommands)
        // does call acquire locks internally 
        command->call();
    releaseLocks();
}

void Transaction::releaseLocks()
{
    for (auto command: mCommands)
        command->releaseLocks();
}

void Transaction::addCommand(Command* pCommand)
{
    mCommands.push_back(pCommand);
}
