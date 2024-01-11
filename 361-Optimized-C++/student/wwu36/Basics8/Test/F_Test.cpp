//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "F.h"

TEST(Test_F, TestConfig::ALL)
{
#if Test_F

	// Modify F.h
	//
	// There should be two classes defined in this header
	//     Generalized template class
	//     Full class specification class 
	//
	// Generalized: Cut & Paste from E.h for the general class template
	//     Then add full specialization
	//
	// Write a full class specialization for float
	//     in this class when you push() a float it pushes the little data twice
	//     in this class when you pop() it pops a singe element off the stack
	//     top() and empty() behave the same.


	// Do not change the code below is a no no -----------------------

	int val;
	bool bval;
	StackF<int> Stack_int;

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

	// ----- float ---------------

	float fval;
	StackF<float> Stack_float;

	bval = Stack_float.empty();
	CHECK(bval == true);

	Stack_float.push(55.0f);
	fval = Stack_float.top();
	CHECK(fval == 55.0f);

	bval = Stack_float.empty();
	CHECK(bval == false);

	Stack_float.push(88.0f);
	fval = Stack_float.top();
	CHECK(fval == 88.0f);

	// ---- start to pop -------------
	Stack_float.pop();
	fval = Stack_float.top();
	CHECK(fval == 88.0f);

	bval = Stack_float.empty();
	CHECK(bval == false);

	Stack_float.pop();
	fval = Stack_float.top();
	CHECK(fval == 55.0f);

	bval = Stack_float.empty();
	CHECK(bval == false);

	Stack_float.pop();
	fval = Stack_float.top();
	CHECK(fval == 55.0f);

	bval = Stack_float.empty();
	CHECK(bval == false);

	Stack_float.pop();
	bval = Stack_float.empty();
	CHECK(bval == true);

#endif
} TEST_END

// ---  End of File ---------------
