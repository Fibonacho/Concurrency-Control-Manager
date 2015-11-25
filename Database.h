//Database

//#include "ILockManager.h"
#include <list>
#include "Table.h"

class Database
{
private: //public:
    //LockManager
    std::list<Table> mTables;

public:
    Database();

    void CreateFlightReservationDB();
};
