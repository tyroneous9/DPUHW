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
	/*
	data A:
	  0x00: 00 00 00 00 
	  0x04: 00 aa aa aa 
	------------------------
	size : 8  padding : 3 

	data B:
	  0x00: 00 00 00 00 
	  0x04: 00 00 00 00 
	  0x08: 00 aa aa aa 
	  0x0c: 00 00 00 00 
	------------------------
	size : 16  padding : 3 
	*/
	Info info;
	info.NumBytesOfPadding = 0;
	info.NumTotalBytes = StructSize;

	unsigned char* pStr = (unsigned char*)pData;
	Trace::out2("%s:",  pString);
	int j = 0;
	for (int i = 0; i < StructSize; i++) {
		if(j%4 == 0)
			Trace::out2("\n  0x%02x: ", j);
		j += 1;
		Trace::out2("%02x ", pStr[i]);
		if (pStr[i] == 0xaa)
			info.NumBytesOfPadding += 1;
	}
	Trace::out2("\n------------------------\n");
	Trace::out2("size : %d  padding : %d\n", StructSize, info.NumBytesOfPadding);

	return info;
}

// ---  End of File ---

