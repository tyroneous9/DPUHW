//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <string.h>
#include "_UnitTestConfiguration.h"
#include "D.h"

// ---------------------------------------------------------------------------------
// Do NOT modify this File!
//
//   Modifying tests is an academic integrity violation
//
// Do NOT change anything in this  file
//             or DIE (evil laughter....)
// ---------------------------------------------------------------------------------

TEST(Test_D_Enable, TestConfig::ALL)
{
#if Test_D_Enable

	// Did you do any work?
	FILE_MODIFIED_CHECK(".\\..\\D\\D.h", ".\\Basics5\\D\\D.h", 0x3339e7f4);

	Audi *pCar = new Audi();

	CHECK(pCar->color == Volkswagon::Color::Black);
	CHECK(pCar->numDoors == 4);
	CHECK(pCar->wheelDrive == 4);
	CHECK(pCar->wings == 0);

	delete pCar;

#endif
} TEST_END

// -- End of File ---
