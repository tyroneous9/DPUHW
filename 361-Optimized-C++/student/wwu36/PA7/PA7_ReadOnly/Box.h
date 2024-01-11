//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef BOX_H
#define BOX_H

#include "Vect4D.h"
#include "Sphere.h"

// ------------------------------
// DO NOT MODIFY 
// ------------------------------

class Box
{
public:
	enum class ColResult
	{
		Inside,
		Outside
	};


public:

	Box() = default;
	Box(const Box &tmp) = default;
	Box &operator=(const Box &tmp) = default;
	~Box() = default;


	ColResult Collide(const Sphere &sphere);


	// Box point on Opposite corners of a box
	Vect4D NearBottomLeftPoint;
	Vect4D FarTopRightPoint;

	// Face Normals for each side of box
	Vect4D TopNorm;
	Vect4D LeftNorm;
	Vect4D FrontNorm;
	Vect4D BackNorm;
	Vect4D RightNorm;
	Vect4D BottomNorm;
	
};

#endif

// ---  End of File ---
