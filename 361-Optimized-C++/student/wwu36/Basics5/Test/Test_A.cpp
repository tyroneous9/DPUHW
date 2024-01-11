//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <string.h>
#include "_UnitTestConfiguration.h"
#include "A.h"

// ---------------------------------------------------------------------------------
// Do NOT modify this File!
//
//   Modifying tests is an academic integrity violation
//
// Do NOT change anything in this  file
//             or DIE (evil laughter....)
// ---------------------------------------------------------------------------------

TEST(Test_A_Enable, TestConfig::ALL)
{
#if Test_A_Enable

	A data(32);

	CHECK(data.getFirst() == 33);
	CHECK(data.getSecond() == 32);

#endif
} TEST_END

// --- End of File ---
