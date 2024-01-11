//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST( Nyble_SpecialOps, TestConfig::ALL)
{	
#if Nyble_SpecialOps

	Nyble A(5);
	Nyble B;

	B = ~A;

	CHECK( A.getData() == 5 );
	CHECK( B.getData() == 0xA );

	Nyble C(0xC);
	Nyble D;

	D = ~C;

	CHECK(C.getData() == 0xC);
	CHECK(D.getData() == 3);

#endif
} TEST_END

//---  End of File ---
