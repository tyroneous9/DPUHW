//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include <vector>
#include <set>

#include "_UnitTestConfiguration.h"

#include "ZipCode.h"

extern ZipCode data[];


void Problem_C(std::vector< ZipCode >& UnitTest_ZipSort,
				ZipCode& UnitTest_Bee,
				ZipCode& UnitTest_Zip);

TEST(STL_Set, TestConfig::ALL)
{
#if STL_Set	

	std::vector< ZipCode > UnitTest_ZipSort;
	ZipCode UnitTest_Bee;
	ZipCode UnitTest_Zip;

	Problem_C(UnitTest_ZipSort, UnitTest_Bee, UnitTest_Zip);

	ZipCode *p = &data[0];

	CHECK(p != nullptr);

	CHECK(strcmp(p[0].s,"Bug") == 0 );
	CHECK(p[0].zip == 0xABCD);
	CHECK(strcmp(p[1].s, "Dog") == 0);
	CHECK(p[1].zip == 0x1331);
	CHECK(strcmp(p[2].s, "Cat") == 0);
	CHECK(p[2].zip == 0x8844);
	CHECK(strcmp(p[3].s, "Pig") == 0);
	CHECK(p[3].zip == 0xBB77);
	CHECK(strcmp(p[4].s, "Bee") == 0);
	CHECK(p[4].zip == 0xFFEE);
	CHECK(strcmp(p[5].s, "Nbt") == 0);
	CHECK(p[5].zip == 0xCC99);

	CHECK(strcmp(UnitTest_ZipSort[0].s, "Cat") == 0);
	CHECK(UnitTest_ZipSort[0].zip == 0x8844);
	CHECK(strcmp(UnitTest_ZipSort[1].s, "Nbt") == 0);
	CHECK(UnitTest_ZipSort[1].zip == 0xCC99);
	CHECK(strcmp(UnitTest_ZipSort[2].s, "Bee") == 0);
	CHECK(UnitTest_ZipSort[2].zip == 0xFFEE);
	CHECK(strcmp(UnitTest_ZipSort[3].s, "Pig") == 0);
	CHECK(UnitTest_ZipSort[3].zip == 0xBB77);
	CHECK(strcmp(UnitTest_ZipSort[4].s, "Dog") == 0);
	CHECK(UnitTest_ZipSort[4].zip == 0x1331);
	CHECK(strcmp(UnitTest_ZipSort[5].s, "Bug") == 0);
	CHECK(UnitTest_ZipSort[5].zip == 0xABCD);

	CHECK(UnitTest_Bee.zip == 0xFFEE);
	CHECK(strcmp(UnitTest_Bee.s, "Bee") == 0);
		  
	CHECK(UnitTest_Zip.zip == 0xBB77);
	CHECK(strcmp(UnitTest_Zip.s, "Pig") == 0);

#endif

} TEST_END

// --- End of File ---
