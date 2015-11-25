//Database

#include <list>
#include "Instruction.h"

class Transaction
{
private:
    std::list<Instruction> mInstructions;
public:
    void execute();
    
    /*bool insert(int value, Table table);
    bool insert(int value1, int value2, Table table);
    bool removeRow(int id, Table table);
    int getCount();*/
};
