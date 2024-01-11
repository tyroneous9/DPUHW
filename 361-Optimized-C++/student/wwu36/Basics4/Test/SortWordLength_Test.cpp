//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "SortStrings.h"

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

static char *r1 = nullptr;
static char *r2 = nullptr;
static char *r3 = nullptr;
static char *t1 = nullptr;
static char *t2 = nullptr;
static char *t3 = nullptr;

TEST_WITH_TEARDOWN(sort_strings_wordlength, TestConfig::ALL)
{
#if sort_strings_wordlength

	char *s1 = "everclear cider bier daiquiri bacardi";
	char *s2 = "pug beagle chihuahua akita doberman";
	char *s3 = "blue azul rojo red green verde blanco white noir black";

	char *a1 = "bier cider bacardi daiquiri everclear";
	char *a2 = "pug akita beagle doberman chihuahua";
	char *a3 = "red azul blue noir rojo black green verde white blanco";

	r1 = new char[strlen(s1) + 1];
	r2 = new char[strlen(s2) + 1];
	r3 = new char[strlen(s3) + 1];

	t1 = new char[strlen(s1) + 2];
	t1[strlen(s1) + 1] = 0xE;
	t2 = new char[strlen(s2) + 2];
	t2[strlen(s2) + 1] = 0xE;
	t3 = new char[strlen(s3) + 2];
	t3[strlen(s3) + 1] = 0xE;

	ReorderWordLength(s1, r1);
	CHECK(strcmp(r1, a1) == 0);

	// concatenation overrun check
	ReorderWordLength(s1, t1);
	CHECK(strcmp(t1, a1) == 0);
	CHECK(t1[strlen(s1) + 1] == 0xE);

	ReorderWordLength(s2, r2);
	CHECK(strcmp(r2, a2) == 0);

	// concatenation overrun check
	ReorderWordLength(s2, t2);
	CHECK(strcmp(t2, a2) == 0);
	CHECK(t2[strlen(s2) + 1] == 0xE);

	ReorderWordLength(s3, r3);
	CHECK(strcmp(r3, a3) == 0);

	// concatenation overrun check
	ReorderWordLength(s3, t3);
	CHECK(strcmp(t3, a3) == 0);
	CHECK(t3[strlen(s3) + 1] == 0xE);

	delete r1;
	r1 = nullptr;
	delete r2;
	r2 = nullptr;
	delete r3;
	r3 = nullptr;

	delete t1;
	t1 = nullptr;
	delete t2;
	t2 = nullptr;
	delete t3;
	t3 = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(sort_strings_wordlength)
{
	delete r1;
	delete r2;
	delete r3;

	delete t1;
	delete t2;
	delete t3;
}

// ---  End of File ---
