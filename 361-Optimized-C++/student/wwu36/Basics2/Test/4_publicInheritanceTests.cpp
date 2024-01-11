//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "UnitTestBufferManager.h"
#include "P.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

TEST(Public4, TestConfig::ALL)
{
#if Public4

	P data;

	CHECK(data.a == 11);
	CHECK(data.b == 22);
	CHECK(data.c == 33);
	CHECK(data.d == 44);

	CHECK(sizeof(P) == 24);

	N *pN = &data;
	O *pO = &data;

	CHECK(pN->a == 11);
	CHECK(pN->b == 22);

	CHECK(pO->a == 11);
	CHECK(pO->c == 33);

	P data1(5, 6, 7, 8);

	CHECK(data1.a == 5);
	CHECK(data1.b == 6);
	CHECK(data1.c == 7);
	CHECK(data1.d == 8);

	pN = &data1;
	pO = &data1;

	CHECK(pN->a == 5);
	CHECK(pN->b == 6);

	CHECK(pO->a == 5);
	CHECK(pO->c == 7);

	CHECK(UnitTestBufferManager::getInstance()->getCount() == 0);

#endif
} TEST_END

// End of File
