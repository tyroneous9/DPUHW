///----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PERFORMANCE_TEST_H
#define PERFORMANCE_TEST_H

#include "Vect4D.h"
#include "Matrix.h"

// --------------------------------------------
// COLLIDE
// --------------------------------------------

	#ifdef _DEBUG
	#define COLLIDE_COUNT 20000000
	#else
	#define COLLIDE_COUNT 150000000
	#endif

	#include "Box.h"
	#include "Sphere.h"
	#include "Box_SIMD.h"
	#include "Sphere_SIMD.h"

	int collide_test();
	int collide_SIMD_test();

// --------------------------------------------
// ROW MAJOR 
// --------------------------------------------

	#ifdef _DEBUG
	#define ROW_MAJOR_COUNT 20000000
	#else
	#define ROW_MAJOR_COUNT 150000000
	#endif

	#include "Vect_Row_SIMD.h"
	#include "Matrix_Row_SIMD.h"

	Vect4D rowMajor_test();
	Vect_Row_SIMD rowMajor_SIMD_test();

// --------------------------------------------
// COL MAJOR 
// --------------------------------------------

	#ifdef _DEBUG
	#define COL_MAJOR_COUNT 15000000
	#else
	#define COL_MAJOR_COUNT 150000000
	#endif

	#include "Vect_Col_SIMD.h"
	#include "Matrix_Col_SIMD.h"

	Vect4D colMajor_test();
	Vect_Col_SIMD colMajor_SIMD_test();

// --------------------------------------------

void PerformanceTest();

#endif

// ---  End of File ---------------
