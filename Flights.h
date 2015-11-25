//Database

#include "ITable.h"
#include "DList.h"

class Flights: public ITable
{
private:
    DList<int> mList;
public:
    virtual void initialize() override final;
    bool add(int pValue);
    virtual bool remove(int id) override final;
    
    int getRandomfID();
    Flights();
    ~Flights();
};

