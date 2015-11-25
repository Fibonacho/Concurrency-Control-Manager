//Database

#include "Table.h"
#include "DList.h"

class Reservations: public Table
{
private:
    struct Reservation
    {
        int pID; //passenger ID
        int sID; //seat ID
    };
    
    DList<Reservation> mList;
public:
    void initialize(); //override final;
    bool add(Reservation pReservation);
    //bool add(pID, s)
    bool remove(int id); //override final;
    
};
