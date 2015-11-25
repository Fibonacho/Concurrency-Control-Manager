//Database

#include "ILockManager.h"

class ITable //: public ILockManager
{
    //get new primary ID
    int mID;
    
    virtual void initialize() = 0;
    //virtual bool add(int value) = 0;
    virtual bool remove(int id) = 0;
public:
    ITable(): mID(1) {};
protected:
    int getNewID()
    {
        return mID;
        mID++;
    }
};
