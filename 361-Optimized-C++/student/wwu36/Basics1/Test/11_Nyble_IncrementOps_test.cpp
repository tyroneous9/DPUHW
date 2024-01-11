//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Nyble_IncrementOps, TestConfig::ALL)
{
#if Nyble_IncrementOps

	Nyble A(10);
	Nyble B;

	// increment operators should wrap, just like eveything else
	B = ++A;

	CHECK( B.getData() == 11 );
	CHECK( A.getData() == 11 );

	B = ++A;

	CHECK( B.getData() == 12 );
	CHECK( A.getData() == 12 );

	++A;
	++A;
	B = ++A;

	CHECK( B.getData() == 15 );
	CHECK( A.getData() == 15 );
	
	B = ++A;

	CHECK( B.getData() == 0 );
	CHECK( A.getData() == 0 )
		
	B = ++A;

	CHECK( B.getData() == 1 );
	CHECK( A.getData() == 1 );

	Nyble C(3);
	Nyble D;

	D = C++;

	CHECK( C.getData() == 4 );
	CHECK( D.getData() == 3 );
	
	Nyble E(0xE);
	Nyble F;

	F = E++;
	
	CHECK( E.getData() == 0xF );
	CHECK( F.getData() == 0xE );

	F = E++;
	
	CHECK( E.getData() == 0 );
	CHECK( F.getData() == 0xF );

	F = E++;
	
	CHECK( E.getData() == 1 );
	CHECK( F.getData() == 0 );

#endif
} TEST_END

//---  End of File ---
