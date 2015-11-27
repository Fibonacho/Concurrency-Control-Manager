//Database
#include "DList.h"
#include "Table.h"
#include <string>
#include "Database.h"

class Passengers: public Table
{
private:
    struct Passenger
    {
        int mPID;
        std::string mName;
    };
    
    //DList<Passenger> mList;
public:
    //void initialize(); // override final;
    int add(std::string pName);
    //bool remove(int id); // override final;
    
    Passengers(Database& database);
};
