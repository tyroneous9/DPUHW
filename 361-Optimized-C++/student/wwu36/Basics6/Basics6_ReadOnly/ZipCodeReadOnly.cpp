//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "ZipCode.h"

ZipCode::ZipCode()
	: zip(0)
{
	this->s[0] = 0;
	this->s[1] = 0;
	this->s[2] = 0;
	this->s[3] = 0;
}

ZipCode::ZipCode(const ZipCode& r)
	: zip(r.zip)
{
	this->s[0] = r.s[0];
	this->s[1] = r.s[1];
	this->s[2] = r.s[2];
	this->s[3] = r.s[3];
}

ZipCode::ZipCode(const char* inS, const int inZip)
	:zip(inZip)
{
	this->s[0] = inS[0];
	this->s[1] = inS[1];
	this->s[2] = inS[2];
	this->s[3] = inS[3];
}

ZipCode::~ZipCode()
{
}

ZipCode& ZipCode::operator = (const ZipCode& in)
{
	this->zip = in.zip;
	this->s[0] = in.s[0];
	this->s[1] = in.s[1];
	this->s[2] = in.s[2];
	this->s[3] = in.s[3];
	return *this;
}


// ---  End of File ---