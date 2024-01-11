//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "M.h"

void vTableQuestions_M()
{
	M* pM = new M();
	delete pM;
	// Class M:  Question 70-79
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 70 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 71 , 2 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 72 , 0xF003);

	// 2nd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 73 , 0xF005);

	// 3rd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 74 , 0 );

	// 4th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 75 , 0 );

	// 5th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 76 , 0 );

	// 6th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 77 , 0 );

	// 7th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 78 , 0 );

	// 8th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 79 , 0 );

}

// ---  End of File ---------------
