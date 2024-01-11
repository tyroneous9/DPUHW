//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect4D_SIMD.h"


Vect4D_SIMD::Vect4D_SIMD(const float tx, const float ty, const float tz, const float tw)
	: x(tx), y(ty), z(tz), w(tw)
{
}


float Vect4D_SIMD::Dot(const Vect4D_SIMD &B) const
{
	//return this->x * B.x + this->y * B.y + this->z * B.z;
	__m128 A = _mm_mul_ps(_mm_set_ps1(this->x), _mm_set_ps1(B.x));
	A = _mm_add_ps(A, _mm_mul_ps(_mm_set_ps1(this->y), _mm_set_ps1(B.y)));
	A = _mm_add_ps(A, _mm_mul_ps(_mm_set_ps1(this->z), _mm_set_ps1(B.z)));
	return _mm_cvtss_f32(A);
}

Vect4D_SIMD Vect4D_SIMD::operator - (const Vect4D_SIMD &t) const
{
	Vect4D_SIMD v;
	v._m = _mm_sub_ps(this->_m, t._m);
	return v;

}

Vect4D_SIMD Vect4D_SIMD::operator + (const Vect4D_SIMD &t) const
{
	Vect4D_SIMD v;
	v._m = _mm_add_ps(this->_m, t._m);
	return v;
}


// ---  End of File ----


