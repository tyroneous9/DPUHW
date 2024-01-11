//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "answerRegistry.h"
#include "E.h"

void vTableQuestions_E()
{
	E* pE = new E();
	delete pE;
	// Class E:  Question 40-49
	// Only consider this class for this answer

	// Is there a vTable for this class?
	// (1 - true, 0 - false)

	QuestionAnswer( 40 , 1 );

	// How many jump vectors(pointers to functions) are in the vTable?
	//  (0 - no table, 1-N - number of jump vectors)?

	QuestionAnswer( 41 , 3 );

	// Next 8 questions, fill in the jump vector
	// Add the function label number 
	// Order is important, do not reorder the classes

	// 1st jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 42 , 0xe002);

	// 2nd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 43 , 0xe003);

	// 3rd jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 44 , 0xe005);

	// 4th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 45 , 0 );

	// 5th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 46 , 0 );

	// 6th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 47 , 0 );

	// 7th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 48 , 0 );

	// 8th jump vector ?
    // (label number, 0xFFFF - purecall, 0 - does not exist)

	QuestionAnswer( 49 , 0 );

}

// ---  End of File ---------------
