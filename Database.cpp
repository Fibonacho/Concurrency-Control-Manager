#include "Database.h"
#include "Flights.h"
#include "Seats.h"
#include "Reservations.h"
#include "Passengers.h"
#include <stdlib.h>
#include <time.h>
#include "LockManager.h"

Database::Database(LockManager* pLockManager): StorageUnit(nullptr), mLockManager(pLockManager)
{

}

Database::~Database()
{

}

void Database::AddTable(StorageUnit* table)
{
    mChilds.push_back(table);
}
