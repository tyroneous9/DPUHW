//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "A.h"

void vTableQuestions_B()
{
	A* pA;
	pA = new B();
	delete pA;
	// Class B:  Question 10-19
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 10 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 11 , 4 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 12 , 0xa004);

	// 2nd jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 13 , 0xa006);

	// 3rd jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 14 , 0xa007);

	// 4th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 15 , 0xa008);

	// 5th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 16 , 0 );

	// 6th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 17 , 0 );

	// 7th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 18 , 0 );

	// 8th jump vector ?
	// (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 19 , 0 );

}

// ---  End of File ---------------
