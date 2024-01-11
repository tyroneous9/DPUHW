//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "UnitTestBufferManager.h"
#include "H.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Public3, TestConfig::ALL)
{
#if Public3

	H data;

	CHECK(data.a == 11);
	CHECK(data.b == 22);
	CHECK(data.c == 33);
	CHECK(data.d == 44);

	CHECK(sizeof(H) == 24);

	F *pF = &data;
	G *pG = &data;

	CHECK(pF->a == 11);
	CHECK(pF->b == 22);

	CHECK(pG->a == 11);
	CHECK(pG->c == 33);

	CHECK(UnitTestBufferManager::getInstance()->getCount() == 0);

#endif
} TEST_END

// End of File
