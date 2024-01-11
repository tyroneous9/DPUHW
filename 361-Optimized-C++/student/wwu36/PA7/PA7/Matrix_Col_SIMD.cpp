//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Vect_Col_SIMD.h"
#include "Matrix_Col_SIMD.h"

Matrix_Col_SIMD::Matrix_Col_SIMD(const Vect_Col_SIMD &tV0,
	const Vect_Col_SIMD &tV1,
	const Vect_Col_SIMD &tV2,
	const Vect_Col_SIMD &tV3)
	: v0(tV0), v1(tV1), v2(tV2), v3(tV3)
{
}

Vect_Col_SIMD proxymV(const Vect_Col_SIMD& v, Vect_Col_SIMD colx, Vect_Col_SIMD coly, Vect_Col_SIMD colz, Vect_Col_SIMD colw) {
	Vect_Col_SIMD productV;
	productV._m = _mm_mul_ps(colx._m, _mm_set1_ps(v.x));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(coly._m, _mm_set1_ps(v.y)));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(colz._m, _mm_set1_ps(v.z)));
	productV._m = _mm_add_ps(productV._m, _mm_mul_ps(colw._m, _mm_set1_ps(v.w)));

	return productV;
}

Vect_Col_SIMD Matrix_Col_SIMD::operator * (const Vect_Col_SIMD& vb)
{
	return proxymV(vb, Vect_Col_SIMD(this->v0.x, this->v1.x, this->v2.x, this->v3.x),
		Vect_Col_SIMD(this->v0.y, this->v1.y, this->v2.y, this->v3.y),
		Vect_Col_SIMD(this->v0.z, this->v1.z, this->v2.z, this->v3.z),
		Vect_Col_SIMD(this->v0.w, this->v1.w, this->v2.w, this->v3.w)
	);
}

Matrix_Col_SIMD Matrix_Col_SIMD::operator * (const Matrix_Col_SIMD &mb)
{
	Matrix_Col_SIMD productM;

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
