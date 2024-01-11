//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "MiddlewareNative.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

Vect2D_Native::Vect2D_Native()
	: x(22.0f), y(33.0f)
{
	s_const++;
}

void Vect2D_Native::setX(float val)
{
	this->x = val;
	s_setx++;
}

void Vect2D_Native::setY(float val)
{
	this->y = val;
	s_sety++;
}

float Vect2D_Native::getX()
{
	s_getx++;
	return this->x;
}

float Vect2D_Native::getY()
{
	s_gety++;
	return this->y;
}

void Vect2D_Native::setID(int val)
{
	s_setid++;
	this->s_id = val;
}

int Vect2D_Native::getID()
{
	s_getid++;
	return this->s_id;
}

// --- End of File ---
