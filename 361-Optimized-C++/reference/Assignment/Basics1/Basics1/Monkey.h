//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MONKEY_H
#define MONKEY_H

//----------------------------------------------------------------------------
// Feel free to add extra methods in the class
// You need to explicitly define and implement the Big four operators
// Do not add extra member data into class
// Do not add code here (that goes in *.cpp)
//----------------------------------------------------------------------------

class Monkey
{
public:

	// insert your code here

	// accessors
	int getX();
	int getY();
	char *getStatus();
	void printStatus();

	// global variables (incremented each creation or destruction)
	static int numStringsCreated;
	static int numStringsDestroyed;

private:
        // Do not change this data
	int x;
	int y;
	char *pStatus;
};


#endif

//---  End of File ---
