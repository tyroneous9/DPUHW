//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_M_SIMD.h"
#include "Matrix_M_SIMD.h"

Matrix_M_SIMD::Matrix_M_SIMD(const Vect_M_SIMD &tV0,
							 const Vect_M_SIMD &tV1,
							 const Vect_M_SIMD &tV2,
							 const Vect_M_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Matrix_M_SIMD Matrix_M_SIMD::operator * (const Matrix_M_SIMD &mb) const
{
	Matrix_M_SIMD productM;

	productM.v0._m = _mm_mul_ps(_mm_set1_ps(this->v0.x), mb.v0._m);
	productM.v1._m = _mm_mul_ps(_mm_set1_ps(this->v1.x), mb.v0._m);
	productM.v2._m = _mm_mul_ps(_mm_set1_ps(this->v2.x), mb.v0._m);
	productM.v3._m = _mm_mul_ps(_mm_set1_ps(this->v3.x), mb.v0._m);

	productM.v0._m = _mm_add_ps(productM.v0._m, _mm_mul_ps(_mm_set1_ps(this->v0.y), mb.v1._m));
	productM.v1._m = _mm_add_ps(productM.v1._m, _mm_mul_ps(_mm_set1_ps(this->v1.y), mb.v1._m));
	productM.v2._m = _mm_add_ps(productM.v2._m, _mm_mul_ps(_mm_set1_ps(this->v2.y), mb.v1._m));
	productM.v3._m = _mm_add_ps(productM.v3._m, _mm_mul_ps(_mm_set1_ps(this->v3.y), mb.v1._m));

	productM.v0._m = _mm_add_ps(productM.v0._m, _mm_mul_ps(_mm_set1_ps(this->v0.z), mb.v2._m));
	productM.v1._m = _mm_add_ps(productM.v1._m, _mm_mul_ps(_mm_set1_ps(this->v1.z), mb.v2._m));
	productM.v2._m = _mm_add_ps(productM.v2._m, _mm_mul_ps(_mm_set1_ps(this->v2.z), mb.v2._m));
	productM.v3._m = _mm_add_ps(productM.v3._m, _mm_mul_ps(_mm_set1_ps(this->v3.z), mb.v2._m));

	productM.v0._m = _mm_add_ps(productM.v0._m, _mm_mul_ps(_mm_set1_ps(this->v0.w), mb.v3._m));
	productM.v1._m = _mm_add_ps(productM.v1._m, _mm_mul_ps(_mm_set1_ps(this->v1.w), mb.v3._m));
	productM.v2._m = _mm_add_ps(productM.v2._m, _mm_mul_ps(_mm_set1_ps(this->v2.w), mb.v3._m));
	productM.v3._m = _mm_add_ps(productM.v3._m, _mm_mul_ps(_mm_set1_ps(this->v3.w), mb.v3._m));

	return productM;
}


// ---  End of File ---------------
