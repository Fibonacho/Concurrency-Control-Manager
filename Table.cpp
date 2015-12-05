#include "Table.h"
#include <iostream>

Table::Table(Database* database): StorageUnit(database), mID(0)
{
    database->AddTable(this);
}

Table::~Table()
{
}

void Table::addRow(StorageUnit* row) {
    this->mChilds.push_back(row);
}

long Table::getRowCount()
{
    return childCount();
}

int Table::getNewID()
{
    mID++;
    return mID;
}
