//Database

#include "Table.h"
#include "DList.h"
#include <list>
#include "Database.h"

class Reservations: public Table
{
private:
    struct Reservation
    {
        int* pID; //passenger ID
        int* sID; //seat ID
        int* fID; //flight id - can maybe removed later
    };
    
    //DList<Reservation> mList;
public:
    //void initialize(); //override final;
    //bool add(Reservation pReservation);
    bool add(int& pFID, int* pSID, int& pPID);
    bool remove(int pFID, int pPID); //override final;
    
    //bool add(pID, s)
    //bool book(int pFID, int pPID);
    //bool book(int pFID, int pSID, int pPID);
    
    //std::list<int> getFlightIDs(const int pPID);
    
    //std::list<int> getFreeSeats(std::list<int> &SeatList);
    
    Reservations(Database& database);

};
