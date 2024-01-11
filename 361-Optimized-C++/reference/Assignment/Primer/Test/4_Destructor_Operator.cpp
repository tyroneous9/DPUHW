//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "Dog.h"
#include "TestDog.h"

TEST(Destructor_Operator, TestConfig::ALL)
{
#if Destructor_Operator

	// Specialized Constructor
	Dog *pFido = new Dog(5, 7, 9);
	CHECK(pFido != nullptr);

	CHECK(((TestDog &)*pFido).x == 5);
	CHECK(((TestDog &)*pFido).y == 7);
	CHECK(((TestDog &)*pFido).z == 9);
	
	// Manually call the destructor
	// Do not pay attention to this advanced trick... only here for testing
	pFido->~Dog();

	// the destructor should do nothing... so make sure it did nothing
	CHECK(((TestDog &)*pFido).x == 5);
	CHECK(((TestDog &)*pFido).y == 7);
	CHECK(((TestDog &)*pFido).z == 9);

	delete pFido;

#endif
} TEST_END

// --- End of File ---
