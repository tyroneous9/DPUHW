//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Row_SIMD.h"
#include "Matrix_Row_SIMD.h"

Vect_Row_SIMD::Vect_Row_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}

Vect_Row_SIMD proxyvM(const Vect_Row_SIMD& v, __m128 col1, __m128 col2, __m128 col3, __m128 col4) {
	Vect_Row_SIMD productV;
	productV._m = _mm_mul_ps(_mm_set1_ps(v.x), col1);
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.y), col2));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.z), col3));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(_mm_set1_ps(v.w), col4));
	return productV;
}

Vect_Row_SIMD Vect_Row_SIMD::operator * (const Matrix_Row_SIMD &ma)
{
	return proxyvM(*this, ma.v0._m, ma.v1._m, ma.v2._m, ma.v3._m);

};


// ---  End of File ---------------


