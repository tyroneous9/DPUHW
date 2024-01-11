//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "ComparingStrings.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

TEST(compare_strings, TestConfig::ALL)
{
#if compare_strings	

	char *s1 = "asf;ldj2";
	char *s2 = "asf;ldk2";
	char *s3 = "asf;lde2";
	char *s4 = "asf;lde21";

	CHECK(StringCompare_1(s1, s1) == 0);
	CHECK(StringCompare_2(s1, s1) == 0);
	CHECK(StringCompare_3(s1, s1) == 0);

	CHECK(StringCompare_1(s1, s2) == -1);
	CHECK(StringCompare_2(s1, s2) == -1);
	CHECK(StringCompare_3(s1, s2) == -1);

	CHECK(StringCompare_1(s1, s3) == 1);
	CHECK(StringCompare_2(s1, s3) == 1);
	CHECK(StringCompare_3(s1, s3) == 1);

	CHECK(StringCompare_1(s1, s4) == 1);
	CHECK(StringCompare_2(s1, s4) == 1);
	CHECK(StringCompare_3(s1, s4) == 1);

#endif
} TEST_END

// ---  End of File ---
