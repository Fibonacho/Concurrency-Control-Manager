//Database

#ifndef ILOCKS
#define ILOCKS

class ILocks
{
protected:
    //Interface
	bool SL;
	bool XL;

    virtual bool getSL();
    virtual bool getXL();
};

#endif