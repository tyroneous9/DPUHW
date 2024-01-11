//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef Vect_SIMD_H
#define Vect_SIMD_H

#include <xmmintrin.h>
#include <smmintrin.h>  


// -----------------------------------------------------------------------
// Rules: 
//    No implementation in Header
//    No inline keyword
// -----------------------------------------------------------------------

class Vect4D_SIMD
{
public:
	Vect4D_SIMD() = default;
	Vect4D_SIMD(const Vect4D_SIMD &tmp) = default;
	Vect4D_SIMD &operator = (const Vect4D_SIMD &tmp) = default;
	~Vect4D_SIMD() = default;

	Vect4D_SIMD(const float tx, const float ty, const float tz, const float tw);

	float Dot(const Vect4D_SIMD &B) const;
	Vect4D_SIMD operator - (const Vect4D_SIMD &t) const;
	Vect4D_SIMD operator + (const Vect4D_SIMD &t) const;

public:

	union
	{
		__m128	_m;

		struct
		{
			float x;
			float y;
			float z;
			float w;
		};
	};

};

#endif

// ---  End of File ---------------
