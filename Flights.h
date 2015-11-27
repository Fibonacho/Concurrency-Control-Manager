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
        //std::list<int> mSeats;
    };
public:
    int add(std::string pDestination);
    void display();
    
    Flights(Database& database);
    ~Flights();
};

