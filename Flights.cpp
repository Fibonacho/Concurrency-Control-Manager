//Flight

#include "Flights.h"
#include <iostream>


Flights::Flights()
{
    //dlist.push_back(11);
    //constructor
    /*int arr[] = { 4, 6, 8, 32, 19 } ;
    DList<int> dlist (arr);
    dlist.push_back(11);
    dlist.push_front(100);
    while (dlist)
        std::cout << dlist.pop_back()  << " ";*/
}

Flights::~Flights()
{
    //destructor
}

void Flights::display()
{
    /*for(auto flight: mList.begin())
    {
        std::cout << Flights
    }*/
}

int Flights::add(std::string pDestination)
{
    //first check if the flight has already been inserted
    //add a value to the linked list
    Flight flight;
    flight.mID = getNewID();
    flight.mDestination = pDestination;
    mList.pushBack(flight);
    return flight.mID;
}

int Flights::getRandomfID()
{
    return 5; //get a random flight id from the list
}

bool Flights::remove(int id)
{
    //remove an item from the linked list
    return true;
}

