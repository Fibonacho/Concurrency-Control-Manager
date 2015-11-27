//Database

#include "Table.h"
//#include "DList.h"
#include <string>
#include "Database.h"

class Flights: public Table
{
private:
    struct Flight
    {
        int mID;
        std::string mDestination;
    };
    
    //DList<Flight> mList;
public:
    
    //void initialize(); //override final;
    int add(std::string pDestination); //generates an ID automatically - do we want this?!
    //bool add(int pID, int pValue); //needs to check for primary key condition
    //bool remove(int id); //override final;
    //void display();
    
    //int getRandomfID();
    Flights(Database& database);
    ~Flights();
};

