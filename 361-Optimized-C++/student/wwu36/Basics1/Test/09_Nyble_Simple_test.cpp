//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Nyble_Simple, TestConfig::ALL)
{
#if Nyble_Simple

	// default
	Nyble A;
	
	CHECK( sizeof(Nyble) == 1 );

	CHECK( A.getData() == 0 );

	// copy
	Nyble B(5);
	Nyble C(B);

	CHECK( B.getData() == 5 );
	CHECK( C.getData() == 5 );

	// Assign
	Nyble D;
	Nyble E(13);

	D = E;

	CHECK( D.getData() == 13 );
	CHECK( E.getData() == 13 );

	// quick walk
	for( unsigned int i = 0; i < 20; i++)
	{
		Nyble K(i);
		CHECK ( K.getData() < 16 );
	}

	// Random check
	Nyble F(4);
	Nyble G(15);
	Nyble H(16);
	Nyble I(17);
	Nyble J(33);
	Nyble K(0x5BC);

	CHECK( F.getData() == 4 );
	CHECK( G.getData() == 0xF );
	CHECK( H.getData() == 0 );
	CHECK( I.getData() == 1 );
	CHECK( J.getData() == 1 );
	CHECK(K.getData() == 12);

#endif
} TEST_END

//---  End of File ---
