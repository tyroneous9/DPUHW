//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef C_INTERFACE_H
#define C_INTERFACE_H

enum ReturnType
{
	TEMPLATE_3_ARG,
	NON_TEMPLATE_INT_ARG,
	TEMPLATE_2_ARG,
	PLACEHOLDER
};

void C(ReturnType &val_1, ReturnType &val_2, ReturnType &val_3,
	   ReturnType &val_4, ReturnType &val_5, ReturnType &val_6,
	   ReturnType &val_7);


// ---  End of File ---------------

#endif