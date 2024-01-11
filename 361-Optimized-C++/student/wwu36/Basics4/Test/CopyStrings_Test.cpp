//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "CopyingStrings.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

static char *d1 = nullptr;
static char *d2 = nullptr;
static char *d3 = nullptr;

TEST_WITH_TEARDOWN(copy_strings, TestConfig::ALL)
{
#if copy_strings

	d1 = new char[10];
	d2 = new char[10];
	d3 = new char[10];

	char *s2 = "12480973";
	char *s;

	s = StringCopy_1(d1, s2);
	CHECK((int)s == (int)d1);
	CHECK(strcmp(d1, s2) == 0);

	s = StringCopy_2(d2, s2);
	CHECK((int)s == (int)d2);
	CHECK(strcmp(d2, s2) == 0);

	s = StringCopy_3(d3, s2);
	CHECK((int)s == (int)d3);
	CHECK(strcmp(d3, s2) == 0);

	// I HATE string.h lack of protection for null
	// --> WOW
	// strcpy( s1, 0 );
	// strcpy( 0, s2 );
	delete d1;
	d1 = nullptr;
	delete d2;
	d2 = nullptr;
	delete d3;
	d3 = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(copy_strings)
{
	delete d1;
	delete d2;
	delete d3;
}




// ---  End of File ---
