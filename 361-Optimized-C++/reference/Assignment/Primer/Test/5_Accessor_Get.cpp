//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Accessor_Get, TestConfig::ALL)
{
#if Accessor_Get

	// Specialized constructor
	Dog rex(5, 7, 9);

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

	// test getters
	CHECK(rex.getX() == 5);
	CHECK(rex.getY() == 7);
	CHECK(rex.getZ() == 9);

#endif
} TEST_END

// --- End of File ---
