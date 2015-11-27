//Database

/* 
 
 Transaction:
 - 1. book
 - 2. cancel
 - 3. list flights
 - 4. get reservation sum
*/

#include <vector>
#include "Instruction.h"

class Transaction
{
private:
    std::vector<Instruction> mInstructions;
public:
    void execute();
    
    /*bool insert(int value, Table table);
    bool insert(int value1, int value2, Table table);
    bool removeRow(int id, Table table);
    int getCount();*/
    
};
