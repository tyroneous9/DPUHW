//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Copy_Constructor, TestConfig::ALL)
{
#if Copy_Constructor

	// Specialized Constructor
	Dog fido(5, 7, 9);

	CHECK(((TestDog &)fido).x == 5);
	CHECK(((TestDog &)fido).y == 7);
	CHECK(((TestDog &)fido).z == 9);

	// Copy Constructor
	Dog rex(fido);

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

#endif
} TEST_END

// --- End of File ---
