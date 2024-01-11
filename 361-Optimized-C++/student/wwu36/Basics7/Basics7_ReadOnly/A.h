//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef A_H
#define A_H

class A
{
public:
	A()
	: x(5), y(6)
	{
		// Label:  0xa001

		// Delete me:
		//   to show off issue
		// this->getX();
	}
	

	virtual int weight() = 0;
	virtual int maximum() = 0;
	virtual int minimum() = 0;

	int getX()
	{	
		// Delete me:
		//   to show off issue
		// this->weight();
		// Label:  0xa002
		return this->x;
	}

	int getY()
	{
		// Label:  0xa003
		return this->y;
	}

	virtual ~A()
	{
		// Label:  0xa004
	}

protected:
	int x;
	int y;
};

class B : public A
{
public:
	B()
	: z(7)
	{
		// Label:  0xa005
	}

	int weight( )
	{
		// Label:  0xa006
		int sum = this->x + this->y + this->z;
		return (sum);
	}

	int maximum()
	{
		// Label:  0xa007
		int maxVal = this->x;

		if( this->x > this->y )
		{
			if( this->z > this->x )
			{
				maxVal = this->z;
			}
			else
			{
				maxVal = this->x;
			}
		}
		else
		{  // y >= x
			if( this->y > this->z )
			{
				maxVal = y;
			}
			else
			{
				maxVal = this->z;
			}
		}
		return maxVal;
	}

	int minimum()
	{
		// Label:  0xa008
		int minVal = this->x;

		if( this->x < this->y )
		{
			if( this->z < this->x )
			{
				minVal = this->z;
			}
			else
			{
				minVal = this->x;
			}
		}
		else
		{  // y <= x
			if( this->y < this->z )
			{
				minVal = y;
			}
			else
			{
				minVal = this->z;
			}
		}
		return minVal;
	}

	int getZ()
	{
		// Label:  0xa009
		return this->z;
	}

	~B()
	{
		// Label:  0xa00a
	}


private:
	int z;

};

#endif

// ---  End of File ---------------
