//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Monkey.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Monkey_SimpleCreate, TestConfig::ALL)
{
#if Monkey_SimpleCreate

	// reset
	Monkey::numStringsCreated = 0;
	Monkey::numStringsDestroyed = 0;

	CHECK( Monkey::numStringsCreated == 0 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	Monkey	red_mono;

	CHECK( sizeof(Monkey) == 12 );
	CHECK( red_mono.getX() == 878 );
	CHECK( red_mono.getY() == 979 );
	CHECK( strcmp(red_mono.getStatus(),"This string was initialized by a default constructor!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 0 );

#endif
} TEST_END

//---  End of File ---
