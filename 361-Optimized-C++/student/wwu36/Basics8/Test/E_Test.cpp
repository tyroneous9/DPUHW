//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "E.h"

TEST(Test_E, TestConfig::ALL)
{
#if Test_E

	// Fix add missing methods to E.h 
	//     Write the methods missing in the class template
	//     You cannot change the private data

	int val;
	bool bval;
	StackE<int> Stack_int;

	bval = Stack_int.empty();
	CHECK(bval == true);

	Stack_int.push(5);
	val = Stack_int.top();
	CHECK(val == 5);

	bval = Stack_int.empty();
	CHECK(bval == false);

	Stack_int.push(6);
	val = Stack_int.top();
	CHECK(val == 6);

	Stack_int.push(7);
	val = Stack_int.top();
	CHECK(val == 7);

	Stack_int.push(8);
	val = Stack_int.top();
	CHECK(val == 8);

	Stack_int.pop();
	val = Stack_int.top();
	CHECK(val == 7);

	Stack_int.pop();
	val = Stack_int.top();
	CHECK(val == 6);

	Stack_int.pop();
	val = Stack_int.top();
	CHECK(val == 5);

	bval = Stack_int.empty();
	CHECK(bval == false);

	Stack_int.pop();
	bval = Stack_int.empty();
	CHECK(bval == true);

#endif
} TEST_END

// ---  End of File ---------------
