//Database

#include "ITable.h"
#include "DList.h"

class Reservations: public ITable
{
private:
    struct Reservation
    {
        int pID; //passenger ID
        int sID; //seat ID
    };
    
    DList<Reservation> mList;
public:
    virtual void initialize() override final;
    bool add(Reservation pReservation);
    virtual bool remove(int id) override final;
    
};
