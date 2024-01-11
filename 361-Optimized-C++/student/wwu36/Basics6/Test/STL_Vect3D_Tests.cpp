//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include <vector>

#include "_UnitTestConfiguration.h"
#include "Vect.h"

extern Vect V[];

void Problem_D(std::vector< Vect >& UnitTest_V_orig,
			   std::vector< Vect >& UnitTest_V_sort);

TEST(STL_Vect3D, TestConfig::ALL)
{
#if STL_Vect3D

	std::vector< Vect > UnitTest_V_orig;
	std::vector< Vect > UnitTest_V_sort;

	Problem_D(UnitTest_V_orig,
		      UnitTest_V_sort);

	CHECK( V[0].a == 3 &&  V[0].b == 5 &&  V[0].c == 6);
	CHECK( V[1].a == 6 &&  V[1].b == 5 &&  V[1].c == 3);
	CHECK( V[2].a == 3 &&  V[2].b == 4 &&  V[2].c == 7);
	CHECK( V[3].a == 7 &&  V[3].b == 2 &&  V[3].c == 5);
	CHECK( V[4].a == 1 &&  V[4].b == 3 &&  V[4].c == 5);
	CHECK( V[5].a == 3 &&  V[5].b == 2 &&  V[5].c == 5);
	CHECK( V[6].a == 2 &&  V[6].b == 3 &&  V[6].c == 4);
	CHECK( V[7].a == 3 &&  V[7].b == 5 &&  V[7].c == 5);
	CHECK( V[8].a == 7 &&  V[8].b == 3 &&  V[8].c == 2);
	CHECK( V[9].a == 4 &&  V[9].b == 3 &&  V[9].c == 2);
	CHECK(V[10].a == 1 && V[10].b == 7 && V[10].c == 1);

	CHECK(UnitTest_V_orig.size() == 11);
	CHECK(UnitTest_V_orig[0].a == 3  && UnitTest_V_orig[0].b == 5  && UnitTest_V_orig[0].c == 6);
	CHECK(UnitTest_V_orig[1].a == 6  && UnitTest_V_orig[1].b == 5  && UnitTest_V_orig[1].c == 3);
	CHECK(UnitTest_V_orig[2].a == 3  && UnitTest_V_orig[2].b == 4  && UnitTest_V_orig[2].c == 7);
	CHECK(UnitTest_V_orig[3].a == 7  && UnitTest_V_orig[3].b == 2  && UnitTest_V_orig[3].c == 5);
	CHECK(UnitTest_V_orig[4].a == 1  && UnitTest_V_orig[4].b == 3  && UnitTest_V_orig[4].c == 5);
	CHECK(UnitTest_V_orig[5].a == 3  && UnitTest_V_orig[5].b == 2  && UnitTest_V_orig[5].c == 5);
	CHECK(UnitTest_V_orig[6].a == 2  && UnitTest_V_orig[6].b == 3  && UnitTest_V_orig[6].c == 4);
	CHECK(UnitTest_V_orig[7].a == 3  && UnitTest_V_orig[7].b == 5  && UnitTest_V_orig[7].c == 5);
	CHECK(UnitTest_V_orig[8].a == 7  && UnitTest_V_orig[8].b == 3  && UnitTest_V_orig[8].c == 2);
	CHECK(UnitTest_V_orig[9].a == 4  && UnitTest_V_orig[9].b == 3  && UnitTest_V_orig[9].c == 2);
	CHECK(UnitTest_V_orig[10].a == 1 && UnitTest_V_orig[10].b == 7 && UnitTest_V_orig[10].c == 1);
		 															
	CHECK(UnitTest_V_sort.size() == 11);							
	CHECK(UnitTest_V_sort[0].a == 1  && UnitTest_V_sort[0].b == 3  && UnitTest_V_sort[0].c == 5);
	CHECK(UnitTest_V_sort[1].a == 1  && UnitTest_V_sort[1].b == 7  && UnitTest_V_sort[1].c == 1);
	CHECK(UnitTest_V_sort[2].a == 2  && UnitTest_V_sort[2].b == 3  && UnitTest_V_sort[2].c == 4);
	CHECK(UnitTest_V_sort[3].a == 3  && UnitTest_V_sort[3].b == 2  && UnitTest_V_sort[3].c == 5);
	CHECK(UnitTest_V_sort[4].a == 3  && UnitTest_V_sort[4].b == 4  && UnitTest_V_sort[4].c == 7);
	CHECK(UnitTest_V_sort[5].a == 3  && UnitTest_V_sort[5].b == 5  && UnitTest_V_sort[5].c == 5);
	CHECK(UnitTest_V_sort[6].a == 3  && UnitTest_V_sort[6].b == 5  && UnitTest_V_sort[6].c == 6);
	CHECK(UnitTest_V_sort[7].a == 4  && UnitTest_V_sort[7].b == 3  && UnitTest_V_sort[7].c == 2);
	CHECK(UnitTest_V_sort[8].a == 6  && UnitTest_V_sort[8].b == 5  && UnitTest_V_sort[8].c == 3);
	CHECK(UnitTest_V_sort[9].a == 7  && UnitTest_V_sort[9].b == 2  && UnitTest_V_sort[9].c == 5);
	CHECK(UnitTest_V_sort[10].a == 7 && UnitTest_V_sort[10].b == 3 && UnitTest_V_sort[10].c == 2);

#endif
} TEST_END

// ---  End of File ---
