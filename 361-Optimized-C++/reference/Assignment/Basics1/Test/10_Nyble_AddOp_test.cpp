//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Nyble_AddOp, TestConfig::ALL)
{
#if Nyble_AddOp

	Nyble A(3);
	Nyble B(4);
	Nyble C;

	CHECK( A.getData() == 3 );
	CHECK( B.getData() == 4 );
	CHECK( C.getData() == 0 );

	C = A + B;

	CHECK( A.getData() == 3 );
	CHECK( B.getData() == 4 );
	CHECK( C.getData() == 7 );

	Nyble D(5);
	Nyble E(13);

	D += E;

	CHECK( D.getData() == 2 );
	CHECK( E.getData() == 13);

	Nyble F(8);
	Nyble G;

	G = F + 3;

	CHECK( F.getData() == 8 );
	CHECK( G.getData() == 11 );

	Nyble H(14);
	Nyble I;

	I = 7 + H;

	CHECK( H.getData() == 14 );
	CHECK( I.getData() == 5 );

#endif
} TEST_END

//---  End of File ---
