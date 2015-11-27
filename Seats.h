//Database

#include "Table.h"
#include "DList.h"
#include <list>
#include "Database.h"

class Seats: public Table
{
private:
    //int mIndex;
    struct Seat
    {
        int mSID; //seat ID
        int* mFID; //pointer to the flight ID (in case it changes)
        
        Seat(int pSID, int* pFID): mSID(pSID), mFID(pFID) {};
        Seat() {};
    };
    
    int* returnSID(StorageUnit* su);
    //std::list<Seat> mSeatIndizing;
    //DList<Seat> mList;
    
public:
    //void initialize();// override final;
    
    int add(int &pFID); //, int pCount);
    void add(int &pFID, int pCount);
    int* getSeat(int pIndex) const;
    int* getSeat(int* pFID); //get seat of flight
    int* getSeat(int pIndex, int* pFID); //get seat number x of flight pFID
    int* getSeat();
    
    //bool remove(int id);// override final;
    
    //std::list<int> getSeatList(const int pFID);
    
    Seats(Database& database);
};
