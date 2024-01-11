//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "C.h"

// Overloading Function Templates
void C( ReturnType &val_1, ReturnType &val_2, ReturnType &val_3, 
	    ReturnType &val_4, ReturnType &val_5, ReturnType &val_6, 
	    ReturnType &val_7 ) 
{
	// Call the correct the function/template to get the desired effect

	// call min with 3 ints:  42, 7, 68  <--- Need to use stated parameters
	// example: val_1 = blahblah(42,7,68); <--- same parameters in the comment field
	val_1 = minC(42, 7, 68);

	// call min with 2 doubles by argument deduction:  42.0, 7.0
	// example: val_2 = blahblah(42.0, 7.0); 
	val_2 = minC(42.0, 7.0);

	// call min with 2 characters by argument deduction: 'a', 'b'
	// example: val_3 = blahblah('a', 'b'); 
	val_3 = minC('a', 'b');

	// call min with 2 int:  42, 7
	// example: val_4 = blahblah( 42, 7); 
	val_4 = minC(42, 7);

	// call min with 2 int by argument deduction:  42, 7
	// example: val_5 = blahblah( 42, 7); 
	val_5 = minC<int>(42, 7);

	// call min with 2 double no argument deduction:  42, 7
	// example: val_6 = blahblah( 42, 7); 
	val_6 = minC<double>(42.0, 7.0);

	// call min with 2 ints:  42, 'a'
	// example: val_7 = blahblah( 42, 'a'); 
	val_7 = minC(42, 'a');

}

// ---  End of File ---------------
