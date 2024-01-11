//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Nyble.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Nyble_SpecialOps3, TestConfig::ALL)
{
#if Nyble_SpecialOps3

	// You have to use the casting operator for the next code segment below
	// Do not use another technique, please single step through your code

	// Read the PDF for operation
	Nyble E(13);
	unsigned int MonkeyVal(0);

	MonkeyVal = E;

	CHECK(MonkeyVal == 10);
	CHECK(E.getData() == 13);

#endif
} TEST_END

//---  End of File ---
