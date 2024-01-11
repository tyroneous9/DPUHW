//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Monkey.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

Monkey *pRed_mono = nullptr;

TEST_WITH_TEARDOWN( Monkey_NewFunction, TestConfig::ALL)
{
#if Monkey_NewFunction

	// reset
	Monkey::numStringsCreated = 0;
	Monkey::numStringsDestroyed = 0;

	CHECK( Monkey::numStringsCreated == 0 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	pRed_mono = new Monkey();

	CHECK( pRed_mono->getX() == 878 );
	CHECK( pRed_mono->getY() == 979 );
	CHECK( strcmp(pRed_mono->getStatus(),"This string was initialized by a default constructor!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	delete pRed_mono;
	pRed_mono = nullptr;

	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 1 );

#endif
} TEST_END

TEST_TEARDOWN(Monkey_NewFunction)
{
	delete pRed_mono;
} 



//---  End of File ---
