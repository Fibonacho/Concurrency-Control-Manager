//Database

class ILockManager
{
	//Interface
	bool SL;
	bool XL;

	virtual bool getSL() = 0;
	virtual bool getXL() = 0;
};
