//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Box.h"


Box::ColResult Box::Collide(const Sphere &sphere)
{
	ColResult result = Box::ColResult::Inside;

	Vect4D A = sphere.Center - this->NearBottomLeftPoint;

	if(
		(A.Dot(this->BottomNorm) > sphere.Radius) ||
		(A.Dot(this->LeftNorm) > sphere.Radius) ||
		(A.Dot(this->FrontNorm) > sphere.Radius)
		)
	{
		result = Box::ColResult::Outside;
	}
	else
	{
		Vect4D B = sphere.Center - this->FarTopRightPoint;

		if(
			(B.Dot(this->BackNorm) > sphere.Radius) ||
			(B.Dot(this->RightNorm) > sphere.Radius) ||
			(B.Dot(this->TopNorm) > sphere.Radius)
			)
		{
			result = Box::ColResult::Outside;
		}
	}

	//Trace::out("Result: %s \n", result == Box::ColResult::Inside ? "Inside" : "Outside");


	return result;
}

// --- End of File ---
