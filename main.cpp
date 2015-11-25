//
//  main.cpp
//  DatabaseAssignment3
//
//  Created by Johanna Wald on 25.11.15.
//  Copyright © 2015 Johanna Wald. All rights reserved.
//

#include <iostream>
#include "Database.h"

int main(int argc, const char * argv[]) {
    Database database;
    database.CreateFlightReservationDB();
    
    
    std::cout << "Hello, World!\n";
    
    std::cin.get();

    return 0;
}
