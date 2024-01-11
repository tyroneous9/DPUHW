//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SPHERE_H
#define SPHERE_H

#include "Vect4D.h"

// ------------------------------
// DO NOT MODIFY 
// ------------------------------

class Sphere
{


public:

	Sphere() = default;
	Sphere(const Sphere &tmp) = default;
	Sphere &operator=(const Sphere &tmp) = default;
	~Sphere() = default;



	void Print();

	// Center point
	Vect4D Center;
	float  Radius;
	float  pad[3]; // align pad

};

#endif

// ---  End of File ---
