//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "M.h"

void vTableQuestions_O()
{
	O* pO = new O();
	delete pO;
	// Class O:  Question 90-99
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 90 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 91 , 3 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 92 , 0xF009);

	// 2nd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 93 , 0xF00E);

	// 3rd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 94 , 0xF00D);

	// 4th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 95 , 0 );

	// 5th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 96 , 0 );

	// 6th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 97 , 0 );

	// 7th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 98 , 0 );

	// 8th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 99 , 0 );

}

// ---  End of File ---------------
