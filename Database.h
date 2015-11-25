//Database

//#include "ILockManager.h"
#include <list>
#include "Table.h"
#include "Instruction.h"

#ifndef DATABASE_H
#define DATABASE_H

class Database
{
private: //public:
    //LockManager
    std::list<Table> mTables;
    std::list<Instruction> mInstructions;
public:
    Database();

    void CreateBookingDB();
};

#endif