//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <string.h>
#include "_UnitTestConfiguration.h"
#include "G.h"

// ---------------------------------------------------------------------------------
// Do NOT modify this File!
//
//   Modifying tests is an academic integrity violation
//
// Do NOT change anything in this  file
//             or DIE (evil laughter....)
// ---------------------------------------------------------------------------------

TEST(Test_G_Enable, TestConfig::ALL)
{
#if Test_G_Enable

	// Create the array
	int *pData = ArrayOfInt(10);

	// initialize the array
	for (int i = 0; i < 10; i++)
	{
		pData[i] = i;
	} 

	// print the array members
	for (int i = 0; i < 10; i++)
	{
		CHECK(i == pData[i]);
	}

	delete pData;

#endif
} TEST_END
	
// --- End of File ---
