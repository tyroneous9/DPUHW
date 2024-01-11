//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Align.h"

//-------------------------------------------------------------
// PrintME()
//
// Write your alignment printing function here
//-------------------------------------------------------------

Align::Info Align::PrintME(void *pData, int StructSize, char *pString)
{
	// Use Trace::out2(...) to display the data layout and padding

        // NOTE:   out2() NOT out()
        //         it won't be graded without out2()

	// Mimic the KeenanSampleOutput_Debug.txt

        // EXACtLY or the grading system will give a 0
	
	AZUL_REPLACE_ME(pData);
	AZUL_REPLACE_ME(StructSize);
	AZUL_REPLACE_ME(pString);

	Info info;
	info.NumBytesOfPadding = 0;
	info.NumTotalBytes = 0;

	return info;
}

// ---  End of File ---

