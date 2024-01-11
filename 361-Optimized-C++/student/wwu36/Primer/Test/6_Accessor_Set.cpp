//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Accessor_Set, TestConfig::ALL)
{
#if	Accessor_Set

	// Specialized constructor
	Dog rex(1, 2, 3);

	CHECK(((TestDog &)rex).x == 1);
	CHECK(((TestDog &)rex).y == 2);
	CHECK(((TestDog &)rex).z == 3);

	// test Setters
	rex.setX(5);
	rex.setY(7);
	rex.setZ(9);

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

#endif
} TEST_END

// --- End of File ---
