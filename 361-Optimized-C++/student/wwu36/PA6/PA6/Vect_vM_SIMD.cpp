//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_vM_SIMD.h"
#include "Matrix_vM_SIMD.h"

Vect_vM_SIMD::Vect_vM_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

//------------------------------
// For No proxy:
//------------------------------

Vect_vM_SIMD proxyvM(const Vect_vM_SIMD& v, __m128 col1, __m128 col2, __m128 col3, __m128 col4) {
	Vect_vM_SIMD productV;
	productV._m = _mm_mul_ps(_mm_set1_ps(v.x), col1);
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.y), col2));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.z), col3));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.w), col4));
	return productV;
}

Vect_vM_SIMD Vect_vM_SIMD::operator * (const Matrix_vM_SIMD &ma) const
{
	return proxyvM(*this, ma.v0._m, ma.v1._m, ma.v2._m, ma.v3._m);			

};


// ---  End of File ---------------


