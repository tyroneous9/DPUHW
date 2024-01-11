//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef J_H
#define J_H

class Dog
{
public:
	int *pVal;
	int val;
	Dog(int val);
	~Dog();

	static int GetVal(Dog d);
};

#endif

// End of File
