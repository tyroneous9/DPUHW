//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include <vector>
#include <list>
#include "_UnitTestConfiguration.h"

extern int B[];

void Problem_B(std::vector<int>& UnitTest_B_orig,
		 	   std::vector<int>& UnitTest_B_insert,
			   std::vector<int>& UnitTest_B_sort);

TEST(STL_List, TestConfig::ALL)
{
#if STL_List

	std::vector<int> UnitTest_B_orig;
	std::vector<int> UnitTest_B_insert;
	std::vector<int> UnitTest_B_sort;

	Problem_B(UnitTest_B_orig, UnitTest_B_insert, UnitTest_B_sort);

	CHECK(B[0] == 66);
	CHECK(B[1] == 77);
	CHECK(B[2] == 33);
	CHECK(B[3] == 22);
	CHECK(B[4] == 88);
	CHECK(B[5] == 11);
	CHECK(B[6] == 99);
	CHECK(B[7] == 44);

	CHECK(UnitTest_B_orig.size() == 8);
	CHECK(UnitTest_B_orig[0] == 66);
	CHECK(UnitTest_B_orig[1] == 77);
	CHECK(UnitTest_B_orig[2] == 33);
	CHECK(UnitTest_B_orig[3] == 22);
	CHECK(UnitTest_B_orig[4] == 88);
	CHECK(UnitTest_B_orig[5] == 11);
	CHECK(UnitTest_B_orig[6] == 99);
	CHECK(UnitTest_B_orig[7] == 44);
		 
	CHECK(UnitTest_B_insert.size() == 9);
	CHECK(UnitTest_B_insert[0] == 66);
	CHECK(UnitTest_B_insert[1] == 77);
	CHECK(UnitTest_B_insert[2] == 33);
	CHECK(UnitTest_B_insert[3] == 22);
	CHECK(UnitTest_B_insert[4] == 55);
	CHECK(UnitTest_B_insert[5] == 88);
	CHECK(UnitTest_B_insert[6] == 11);
	CHECK(UnitTest_B_insert[7] == 99);
	CHECK(UnitTest_B_insert[8] == 44);
		  
	CHECK(UnitTest_B_sort.size() == 9);
	CHECK(UnitTest_B_sort[0] == 99);
	CHECK(UnitTest_B_sort[1] == 88);
	CHECK(UnitTest_B_sort[2] == 77);
	CHECK(UnitTest_B_sort[3] == 66);
	CHECK(UnitTest_B_sort[4] == 55);
	CHECK(UnitTest_B_sort[5] == 44);
	CHECK(UnitTest_B_sort[6] == 33);
	CHECK(UnitTest_B_sort[7] == 22);
	CHECK(UnitTest_B_sort[8] == 11);

#endif
} TEST_END


// ---  End of File ---
