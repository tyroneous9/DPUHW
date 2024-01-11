//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include <vector>
#include "_UnitTestConfiguration.h"

extern int A[];

void Problem_A(std::vector<int> &UnitTest_A_orig, 
	           std::vector<int> &UnitTest_A_insert, 
			   std::vector<int> &pUnitTest_A_sort);

TEST(STL_Vector, TestConfig::ALL)
{
#if STL_Vector

	std::vector<int> UnitTest_A_orig;   
	std::vector<int> UnitTest_A_insert; 
	std::vector<int> UnitTest_A_sort;   

	Problem_A(UnitTest_A_orig, UnitTest_A_insert, UnitTest_A_sort);

	CHECK(A[0] == 6);
	CHECK(A[1] == 7);
	CHECK(A[2] == 3);
	CHECK(A[3] == 2);
	CHECK(A[4] == 8);
	CHECK(A[5] == 1);
	CHECK(A[6] == 9);
	CHECK(A[7] == 4);

	CHECK(UnitTest_A_orig.size() == 8);
	CHECK(UnitTest_A_orig[0]== 6);
	CHECK(UnitTest_A_orig[1] == 7);
	CHECK(UnitTest_A_orig[2] == 3);
	CHECK(UnitTest_A_orig[3] == 2);
	CHECK(UnitTest_A_orig[4] == 8);
	CHECK(UnitTest_A_orig[5] == 1);
	CHECK(UnitTest_A_orig[6] == 9);
	CHECK(UnitTest_A_orig[7] == 4);
		  
	CHECK(UnitTest_A_insert.size() == 9);
	CHECK(UnitTest_A_insert[0] == 6);
	CHECK(UnitTest_A_insert[1] == 7);
	CHECK(UnitTest_A_insert[2] == 3);
	CHECK(UnitTest_A_insert[3] == 2);
	CHECK(UnitTest_A_insert[4] == 5);
	CHECK(UnitTest_A_insert[5] == 8);
	CHECK(UnitTest_A_insert[6] == 1);
	CHECK(UnitTest_A_insert[7] == 9);
	CHECK(UnitTest_A_insert[8] == 4);

	CHECK(UnitTest_A_sort.size() == 9);
	CHECK(UnitTest_A_sort[0] == 1);
	CHECK(UnitTest_A_sort[1] == 2);
	CHECK(UnitTest_A_sort[2] == 3);
	CHECK(UnitTest_A_sort[3] == 4);
	CHECK(UnitTest_A_sort[4] == 5);
	CHECK(UnitTest_A_sort[5] == 6);
	CHECK(UnitTest_A_sort[6] == 7);
	CHECK(UnitTest_A_sort[7] == 8);
	CHECK(UnitTest_A_sort[8] == 9);

#endif
} TEST_END

// ---  End of File ---
