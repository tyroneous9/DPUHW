//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "Chunk.h"

//---------------------------------------------------------------------------
// Test Files:
// Single step throught, set break points, but do not modify it
//---------------------------------------------------------------------------

TEST(Test_API_Enable, TestConfig::ALL)
{
#if Test_API_Enable

	int val; 

	val = system("parse -t UV_TYPE -n player_1");
	CHECK(val == 0);

	val = system("parse �R UV_TYPE -n player_1");
	CHECK(val == -1);

	val = system("parse -n player_8888888888881 -t UV_TYPE");
	CHECK(val == -1);

	val = system("parse -t NORM_TYPE -n player_1");
	CHECK(val == -1);

	val = system("parse -t VERTS_TYPE -n ");
	CHECK(val == -1);

	val = system("parse -t UV_TYPE -n player_2");
	CHECK(val == 0);

	val = system("parse -n player_3 -t UV_TYPE");
	CHECK(val == 0);

	val = system("parse -T NORMS_TYPE -N player_4");
	CHECK(val == 0);

	val = system("parse -t VERTS_TYPE -n Fiat");
	CHECK(val == 0);

#endif
} TEST_END

// End of File
