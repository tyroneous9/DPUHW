//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Monkey.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

Monkey *pYellow_mono = nullptr;

TEST_WITH_TEARDOWN( Monkey_AssignmentOp, TestConfig::ALL)
{
#if Monkey_AssignmentOp

	// reset
	Monkey::numStringsCreated = 0;
	Monkey::numStringsDestroyed = 0;

	CHECK( Monkey::numStringsCreated == 0 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	pYellow_mono = new Monkey( 444, 555 );

	CHECK( pYellow_mono->getX() == 444 );
	CHECK( pYellow_mono->getY() == 555 );
	CHECK( strcmp(pYellow_mono->getStatus(),"ThIs tring was initilizxd by a clever user!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	*pYellow_mono = *pYellow_mono;

	CHECK( pYellow_mono->getX() == 444 );
	CHECK( pYellow_mono->getY() == 555 );
	CHECK( strcmp(pYellow_mono->getStatus(),"ThIs tring was initilizxd by a clever user!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	delete pYellow_mono;
	pYellow_mono = nullptr;

	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 1 );

#endif
} TEST_END

TEST_TEARDOWN(Monkey_AssignmentOp)
{
	delete pYellow_mono;
}



//---  End of File ---
