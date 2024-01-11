//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOX_SIMD_H
#define BOX_SIMD_H

#include "Vect4D_SIMD.h"
#include "Sphere_SIMD.h"

// ------------------------------
// DO NOT MODIFY 
// ------------------------------

class Box_SIMD
{
public:
	enum class ColResult
	{
		Inside,
		Outside
	};


public:

	Box_SIMD() = default;
	Box_SIMD(const Box_SIMD &tmp) = default;
	Box_SIMD &operator=(const Box_SIMD &tmp) = default;
	~Box_SIMD() = default;


	ColResult Collide(const Sphere_SIMD &sphere);


	// Box point on Opposite corners of a box
	Vect4D_SIMD NearBottomLeftPoint;
	Vect4D_SIMD FarTopRightPoint;

	// Face Normals for each side of box
	Vect4D_SIMD TopNorm;
	Vect4D_SIMD LeftNorm;
	Vect4D_SIMD FrontNorm;
	Vect4D_SIMD BackNorm;
	Vect4D_SIMD RightNorm;
	Vect4D_SIMD BottomNorm;
	
};

#endif

// ---  End of File ---
