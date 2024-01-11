//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Monkey.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

Monkey *pGreen_mono = nullptr;
Monkey *pBlue_mono = nullptr;

TEST_WITH_TEARDOWN( Monkey_AssignmentOp2, TestConfig::ALL)
{
#if Monkey_AssignmentOp2

	// reset
	Monkey::numStringsCreated = 0;
	Monkey::numStringsDestroyed = 0;

	CHECK( Monkey::numStringsCreated == 0 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	pGreen_mono = new Monkey();

	CHECK( pGreen_mono->getX() == 878 );
	CHECK( pGreen_mono->getY() == 979 );
	CHECK( strcmp(pGreen_mono->getStatus(),"This string was initialized by a default constructor!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 1 );
	CHECK( Monkey::numStringsDestroyed == 0 );
	
	pBlue_mono = new Monkey( 777, 666 );

	CHECK( pBlue_mono->getX() == 777 );
	CHECK( pBlue_mono->getY() == 666 );
	CHECK( strcmp(pBlue_mono->getStatus(),"ThIs tring was initilizxd by a clever user!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 2 );
	CHECK( Monkey::numStringsDestroyed == 0 );

	*pBlue_mono = *pGreen_mono;

	CHECK( pBlue_mono->getX() == 878 );
	CHECK( pBlue_mono->getY() == 979 );
	CHECK( strcmp(pBlue_mono->getStatus(),"This string was initialized by a default constructor!") == 0) ; 
	CHECK( Monkey::numStringsCreated == 3 );
	CHECK( Monkey::numStringsDestroyed == 1 );

	delete pBlue_mono;
	pBlue_mono = nullptr;

	CHECK( Monkey::numStringsCreated == 3 );
	CHECK( Monkey::numStringsDestroyed == 2 );

	delete pGreen_mono;
	pGreen_mono = nullptr;

	CHECK( Monkey::numStringsCreated == 3 );
	CHECK( Monkey::numStringsDestroyed == 3 );

#endif
} TEST_END

TEST_TEARDOWN(Monkey_AssignmentOp2)
{
	delete pGreen_mono;
	delete pBlue_mono;
}



//---  End of File ---
