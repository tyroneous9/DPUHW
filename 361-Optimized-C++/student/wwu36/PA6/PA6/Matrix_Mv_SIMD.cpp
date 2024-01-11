//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Mv_SIMD.h"
#include "Matrix_Mv_SIMD.h"

Matrix_Mv_SIMD::Matrix_Mv_SIMD(const Vect_Mv_SIMD &tV0,
							   const Vect_Mv_SIMD &tV1,
							   const Vect_Mv_SIMD &tV2,
							   const Vect_Mv_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Vect_Mv_SIMD proxymV(const Vect_Mv_SIMD& v, Vect_Mv_SIMD colx, Vect_Mv_SIMD coly, Vect_Mv_SIMD colz, Vect_Mv_SIMD colw) {
	Vect_Mv_SIMD productV;
	productV._m = _mm_mul_ps(colx._m, _mm_set1_ps(v.x));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(coly._m, _mm_set1_ps(v.y)));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(colz._m, _mm_set1_ps(v.z)));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(colw._m, _mm_set1_ps(v.w)));

	return productV;
}

Vect_Mv_SIMD Matrix_Mv_SIMD::operator * (const Vect_Mv_SIMD &v) const
{
	return proxymV(v, Vect_Mv_SIMD(this->v0.x, this->v1.x, this->v2.x, this->v3.x), 
					Vect_Mv_SIMD(this->v0.y, this->v1.y, this->v2.y, this->v3.y),
					Vect_Mv_SIMD(this->v0.z, this->v1.z, this->v2.z, this->v3.z),
					Vect_Mv_SIMD(this->v0.w, this->v1.w, this->v2.w, this->v3.w)
	);
}


// ---  End of File ---------------
