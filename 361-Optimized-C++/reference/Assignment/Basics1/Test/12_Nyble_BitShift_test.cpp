//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Nyble_BitShift, TestConfig::ALL)
{
#if Nyble_BitShift

	// Remember everything wraps around the 4 bits of the Nyble
	Nyble A(10);
	Nyble B;

	B = A << 1;

	CHECK( A.getData() == 10 );
	CHECK( B.getData() == 5 );

	B = B << 1;

	CHECK( B.getData() == 10 );

	Nyble C(1);
	Nyble D;

	D = C << 1;
	
	CHECK( C.getData() == 1 );
	CHECK( D.getData() == 2 );

	D = D << 1;

	CHECK( D.getData() == 4 );

	D = D << 1;

	CHECK( D.getData() == 8 );

	D = D << 1;

	CHECK( D.getData() == 1 );

	Nyble E(3);
	Nyble F;
	
	F = E << 1;
	
	CHECK( E.getData() == 3 );
	CHECK( F.getData() == 6 );

	F = F << 1;

	CHECK( F.getData() == 12 );

	F = F << 1;

	CHECK( F.getData() == 9 );

	F = F << 1;

	CHECK( F.getData() == 3 );

	Nyble G(7);
	Nyble H;

	H = G << 0;

	CHECK( H.getData() == 7);

	H = G << 1; 

	CHECK( H.getData() == 0xE );

	H = G << 2;

	CHECK( H.getData() == 0xD );

	H = G << 3;

	CHECK( H.getData() == 0xB );

	H = G << 4;

	CHECK( H.getData() == 0x7 );

#endif
} TEST_END

//---  End of File ---
