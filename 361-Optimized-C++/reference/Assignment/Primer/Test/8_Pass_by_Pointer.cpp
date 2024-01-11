//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Pass_by_Pointer, TestConfig::ALL)
{
#if Pass_by_Pointer

	// specialized constructor
	Dog rex(1, 2, 3);

	CHECK(((TestDog &)rex).x == 1);
	CHECK(((TestDog &)rex).y == 2);
	CHECK(((TestDog &)rex).z == 3);

	// specialized constructor
	Dog fido(5, 7, 9);

	CHECK(((TestDog &)fido).x == 5);
	CHECK(((TestDog &)fido).y == 7);
	CHECK(((TestDog &)fido).z == 9);

	// pass by Pointer (address of variable)
	rex.setByPtr(&fido);

	CHECK(((TestDog &)rex).x == 5);
	CHECK(((TestDog &)rex).y == 7);
	CHECK(((TestDog &)rex).z == 9);

	CHECK(((TestDog &)fido).x == 5);
	CHECK(((TestDog &)fido).y == 7);
	CHECK(((TestDog &)fido).z == 9);

#endif
} TEST_END

// --- End of File ---
