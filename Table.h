//Database

#ifndef TABLE_H
#define TABLE_H

//#include "ILockManager.h"

class Table //: public ILockManager
{
    //get new primary ID
    int mID;
    
    void initialize();
    //virtual bool add(int value) = 0;
    bool remove(int id);
public:
    Table(): mID(0) {};
protected:
    int getNewID()
    {
        mID++;
        return mID;
    }
};

#endif
