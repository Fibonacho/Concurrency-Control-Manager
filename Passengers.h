//Database
#include "DList.h"
#include "ITable.h"
#include <string>

class Passengers: public ITable
{
private:
    struct Passenger
    {
        int mID;
        std::string mName;
    };
    
    DList<Passenger> mList;
public:
    virtual void initialize() override final;
    bool add(Passenger pPasseger);
    virtual bool remove(int id) override final;
    
};
