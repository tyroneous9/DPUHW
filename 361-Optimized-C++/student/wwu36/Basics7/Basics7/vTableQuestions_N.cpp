//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "M.h"

void vTableQuestions_N()
{
	N* pN = new N();
	delete pN;
	// Class N:  Question 80-89
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 80 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 81 , 3 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 82 , 0xF009);

	// 2nd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 83 , 0xF00A);

	// 3rd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 84 , 0xF008);

	// 4th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 85 , 0 );

	// 5th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 86 , 0 );

	// 6th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 87 , 0 );

	// 7th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 88 , 0 );

	// 8th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 89 , 0 );

}

// ---  End of File ---------------
