//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Monkey.h"

int Monkey::getX()
{
	return this->x;
}

int Monkey::getY()
{
	return this->y;
}

char *Monkey::getStatus()
{
	return this->pStatus;
};

void Monkey::printStatus()
{
	Trace::out("Monkey (Status): %s\n", this->pStatus);
}


//---  End of File ---
