//
//  main.cpp
//  DatabaseAssignment3
//
//  Created by Johanna Wald on 25.11.15.
//  Copyright © 2015 Johanna Wald. All rights reserved.
//

#include <iostream>
#include "Database.h"
#include "TransactionHandler.h"

int main(int argc, const char * argv[]) {
    Database database;
    database.CreateBookingDB();
    
    TransactionHandler transactionHandler(database);
    
    std::cin.get();
    return 0;
}
