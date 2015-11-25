//Database

#include "Table.h"
#include "DList.h"

class Seats: public Table
{
private:
    struct Seat
    {
        int mSID; //seat ID
        int mFID; //flight ID
    };
    
    DList<Seat> mList;
public:
    //void initialize();// override final;
    
    bool add(int pFID, int pCount);
    bool remove(int id);// override final;
    
};
