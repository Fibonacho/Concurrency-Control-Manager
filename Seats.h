//Database

#include "ITable.h"
#include "DList.h"

class Seats: public ITable
{
private:
    struct Seat
    {
        int sID; //seat ID
        int fID; //flight ID
    };
    
    DList<Seat> mList;
public:
    virtual void initialize() override final;
    bool add(Seat pSeat);
    virtual bool remove(int id) override final;
    
};
