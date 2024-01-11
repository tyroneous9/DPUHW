//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ZIP_CODE_H
#define ZIP_CODE_H

// ----------------------------------
// MODIFY this file
// Add methods to this file and predicates (hint)
// ----------------------------------

struct ZipCode
{
	ZipCode();
	ZipCode(const ZipCode &r);
	ZipCode(const char *inS, const int inZip);
	~ZipCode();
	ZipCode & operator = (const ZipCode &in);

	bool operator < (const ZipCode &) const;


	// You need to leave the data alone... you can add methods
	int  zip;
	char s[4];
};

#endif

// ---  End of File ---
