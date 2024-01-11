//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "PerformanceTest.h"

#ifdef _DEBUG
#define FACTOR 1
#else
#define FACTOR 10
#endif

extern int Col_unit_result;
extern int Row_unit_result;
extern int Collide_unit_result;

void PerformanceTest()
{
	// Performance tests
	Trace::out2("\nPerformance tests: \n    Begin()\n");

	int sum_unit_tests = Col_unit_result + Row_unit_result + Collide_unit_result;

	if ( sum_unit_tests < 1 )
	{
		Trace::out2("\n  ERROR---> didn't pass unit tests\n");
		Trace::out2("\n    Cannot run performance tests\n\n\n");
	}
	else
	{
		float tB_time = 999999.0f;

		//Trace::out2("\n");
		PerformanceTimer tA;
		PerformanceTimer tB;



		// --------------- Collide ----------------------------------------------

		Trace::out2("\n---------- Collide ----------------\n");
		printf("           : Collide\n");

		tA.Tic();
		int result = 0;
		result = collide_test();

		tA.Toc();

		// --------------- Collide SIMD ----------------------------------------------

		printf("           : Collide SIMD\n");

		tB.Tic();
		int result_simd = 0;
		result_simd = collide_SIMD_test();

		tB.Toc();

		Trace::out2("        collide Orig: %f s   :%d\n", tA.TimeInSeconds(), result);
		Trace::out2("                SIMD: %f s   :%d\n", tB.TimeInSeconds(), result_simd);

#if Collide_Tests
		if(Collide_unit_result && (result == result_simd) )
		{
			Trace::out2("        collide SIMD: %f s ---> Unit Test Passed \n", tB.TimeInSeconds());
			tB_time = (float)tB.TimeInSeconds();
		}
		else
		{
			tB_time = 999999.0f;
			Trace::out2("       collide SIMD: %2.1f s ---> Unit Test Failed\n", tB_time);
		}

#else
		tB_time = 999999.0f;
		Trace::out2("       colide SIMD: %2.1f s ---> NOT ENABLED\n", tB_time);
#endif
		if(tB.TimeInSeconds() < 0.10f)
		{
			Trace::out2("\n");
			Trace::out2("----> ERROR make sure there is no implementation in header \n");
		}
		else
		{
			Trace::out2("               Ratio: %f\n", tA.TimeInSeconds() / tB_time);
		}


		// --------------- RowMajor ----------------------------------------------

		Trace::out2("\n---------- rowMajor ----------------\n");
		printf("           : rowMajor\n");
		Vect4D Row_C;
		tA.Tic();

			Row_C = rowMajor_test();
		
		tA.Toc();

		// --------------- RowMajor SIMD ----------------------------------------------

		printf("           : rowMajor SIMD\n");
		Vect_Row_SIMD Row_SIMD_C;
		tB.Tic();

			Row_SIMD_C = rowMajor_SIMD_test();
	
		tB.Toc();

		Trace::out2("       rowMajor Orig: %f s   :%f %f %f %f\n", tA.TimeInSeconds(), Row_C.x, Row_C.y, Row_C.z, Row_C.w);
		Trace::out2("                SIMD: %f s   :%f %f %f %f\n", tB.TimeInSeconds(), Row_SIMD_C.x, Row_SIMD_C.y, Row_SIMD_C.z, Row_SIMD_C.w);

#if Row_Tests
		if (Row_unit_result)
		{
			Trace::out2("       rowMajor SIMD: %f s ---> Unit Test Passed \n", tB.TimeInSeconds());
			tB_time = (float)tB.TimeInSeconds();
		}
		else
		{
			tB_time = 999999.0f;
			Trace::out2("       rowMajor SIMD: %2.1f s ---> Unit Test Failed\n", tB_time);
		}

#else
		tB_time = 999999.0f;
		Trace::out2("       rowMajor SIMD: %2.1f s ---> NOT ENABLED\n", tB_time);
#endif
		if( tB.TimeInSeconds() < 0.3f)
		{
			Trace::out2("\n");
			Trace::out2("----> ERROR make sure there is no implementation in header \n");
		}
		else
		{
			Trace::out2("               Ratio: %f\n", tA.TimeInSeconds() / tB_time);
		}

		// --------------- ColMajor ----------------------------------------------

		Trace::out2("\n---------- colMajor ----------------\n");
		printf("           : colMajor\n");
		Vect4D Col_C;
		tA.Tic();

			Col_C = colMajor_test();
		
		tA.Toc();

		// --------------- colMajor SIMD ----------------------------------------------

		printf("           : colMajor SIMD\n");
		Vect_Col_SIMD Col_SIMD_C;
		tB.Tic();

			Col_SIMD_C = colMajor_SIMD_test();
		
		tB.Toc();

		Trace::out2("       colMajor Orig: %f s    :%f %f %f %f\n", tA.TimeInSeconds(), Col_C.x, Col_C.y, Col_C.z, Col_C.w);
		Trace::out2("                SIMD: %f s    :%f %f %f %f\n", tB.TimeInSeconds(), Col_SIMD_C.x, Col_SIMD_C.y, Col_SIMD_C.z, Col_SIMD_C.w);

#if Col_Tests
		if (Col_unit_result)
		{
			Trace::out2("       colMajor SIMD: %f s ---> Unit Test Passed\n", tB.TimeInSeconds());
			tB_time = (float)tB.TimeInSeconds();
		}
		else
		{
			tB_time = 999999.0f;
			Trace::out2("       colMajor SIMD: %2.1f s ---> Unit Test Failed\n", tB_time);
		}
#else
		tB_time = 999999.0f;
		Trace::out2("       colMajor SIMD: %2.1f s ---> NOT ENABLED\n", tB_time);
#endif
		if (tB.TimeInSeconds() < 0.3f)
		{
			Trace::out2("\n");
			Trace::out2("----> ERROR make sure there is no implementation in header \n");
		}
		else
		{
			Trace::out2("               Ratio: %f\n", tA.TimeInSeconds() / tB_time);
		}

		// Tests done
		Trace::out2("\nPerformance tests: done() \n\n");
		printf("\n    done() \n\n");

	}
}

// ---  End of File ---------------
