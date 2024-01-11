//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Assignment_Operator, TestConfig::ALL)
{
#if Assignment_Operator

	// Specialized Constructor
	Dog fido(5, 7, 9);

	CHECK(((TestDog &)fido).x == 5);
	CHECK(((TestDog &)fido).y == 7);
	CHECK(((TestDog &)fido).z == 9);

	// Specialized Constructor
	Dog rex(1, 2, 3);

	CHECK(((TestDog &)rex).x == 1);
	CHECK(((TestDog &)rex).y == 2);
	CHECK(((TestDog &)rex).z == 3);

	// Assignment operator
	rex = fido;

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

#endif
} TEST_END

// --- End of File ---
