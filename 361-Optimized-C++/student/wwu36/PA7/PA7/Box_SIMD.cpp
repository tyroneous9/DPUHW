//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Box_SIMD.h"


Box_SIMD::ColResult Box_SIMD::Collide(const Sphere_SIMD &sphere)
{
	/*
	Vect4D A = sphere.Center - this->NearBottomLeftPoint;

	if(
		(A.Dot(this->BottomNorm) > sphere.Radius) ||
		(A.Dot(this->LeftNorm) > sphere.Radius) ||
		(A.Dot(this->FrontNorm) > sphere.Radius)
		)
	{
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
	*/
	Vect4D_SIMD A;
	ColResult result = Box_SIMD::ColResult::Inside;
	A._m = _mm_sub_ps(sphere.Center._m, this->NearBottomLeftPoint._m);
	if (
		(A.Dot(this->BottomNorm) > sphere.Radius) ||
		(A.Dot(this->LeftNorm) > sphere.Radius) ||
		(A.Dot(this->FrontNorm) > sphere.Radius)
		)
	{
		result = Box_SIMD::ColResult::Outside;
	}
	else
	{
		Vect4D_SIMD B = sphere.Center - this->FarTopRightPoint;

		if (
			(B.Dot(this->BackNorm) > sphere.Radius) ||
			(B.Dot(this->RightNorm) > sphere.Radius) ||
			(B.Dot(this->TopNorm) > sphere.Radius)
			)
		{
			result = Box_SIMD::ColResult::Outside;
		}
	}
	return result;
}


// --- End of File ---
