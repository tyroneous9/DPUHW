//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "UnitTestBufferManager.h"
#include "B.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Public1, TestConfig::ALL)
{
#if Public1

	if (1)  // used to control scope in this test
	{
		B dataB;
		A *pA = &dataB;
		CHECK(pA->getX() == 5);
	}

	if (1)   // used to control scope in this test
	{
		A *pA = new B;
		delete pA;
	}

	CHECK(UnitTestBufferManager::getInstance()->getCount() == 0);

#endif
} TEST_END


// End of File
