//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef SPHERE_SIMD_H
#define SPHERE_SIMD_H

#include "Vect4D_SIMD.h"

// ------------------------------
// DO NOT MODIFY 
// ------------------------------

class Sphere_SIMD
{


public:

	Sphere_SIMD() = default;
	Sphere_SIMD(const Sphere_SIMD &tmp) = default;
	Sphere_SIMD &operator=(const Sphere_SIMD &tmp) = default;
	~Sphere_SIMD() = default;



	void Print();

	// Center point
	Vect4D_SIMD Center;
	float  Radius;
	float  pad[3]; // align pad

};

#endif

// ---  End of File ---
