//Database

#include "Table.h"
#include "DList.h"
#include <list>
#include "Database.h"

class Seats: public Table
{
private:
    struct Seat
    {
        int mSID; //seat ID
        int* mFID; //pointer to the flight ID (in case it changes)
    };
    
    //DList<Seat> mList;
public:
    //void initialize();// override final;
    
    bool add(int &pFID, int pCount);
    //bool remove(int id);// override final;
    
    //std::list<int> getSeatList(const int pFID);
    
    Seats(Database& database);
};
