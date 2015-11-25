//Table

#include "Instruction.h"
#include <iostream>

void Instruction::execute()
{
    // may waits ... check if lock is on table etc.
    std::cout << "execute instruciton" << std::endl;
}
