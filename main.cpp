//
//  main.cpp
//  DatabaseAssignment3
//
//  Created by Johanna Wald on 25.11.15.
//  Copyright © 2015 Johanna Wald. All rights reserved.
//

#include <iostream>
#include "Flights.h"
#include "DList.h"

int main(int argc, const char * argv[]) {
    int a;
    Flights f;
    //f.testFunction();
    std::cout << "Hello, World!\n";
    std::cin >> a;
    std::cout << (a + 100) << std::endl;
    
    int arr[] = { 4, 6, 8, 32, 19 } ;
    DList<int> dlist (arr);
    dlist.pushBack(11);
    dlist.pushFront(100);
    while (dlist)
        std::cout << dlist.popBack()  << " ";
    
    return 0;
}
