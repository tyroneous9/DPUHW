//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"

#include "Box.h"
#include "Box_SIMD.h"

int Collide_unit_result = 0;


TEST(Collide_Tests, TestConfig::ALL)
{
#if Collide_Tests

	// ---------------------------------------------------
	// Cpp tests
	// ---------------------------------------------------
	{
		{
			Box b1;

			b1.NearBottomLeftPoint = Vect4D(-10, -10, 0, 0);
			b1.FarTopRightPoint = Vect4D(10, 10, 10, 0);

			b1.TopNorm = Vect4D(0, 1, 0, 0);
			b1.BottomNorm = Vect4D(0, -1, 0, 0);

			b1.FrontNorm = Vect4D(0, 0, -1, 0);
			b1.BackNorm = Vect4D(0, 0, 1, 0);

			b1.LeftNorm = Vect4D(-1, 0, 0, 0);
			b1.RightNorm = Vect4D(1, 0, 0, 0);

			Sphere s1;
			Sphere s2;
			Sphere s3;
	
			Vect4D d1 = Vect4D(1, 0, 0, 0);
			s1.Center = Vect4D(-20, 0, 5, 0);
			s1.Radius = 5.0f;

			Vect4D d2 = Vect4D(0, 1, 0, 0);
			s2.Center = Vect4D(0, -20, 5, 0);
			s2.Radius = 5.0f;

			Vect4D d3 = Vect4D(0, 0, 1, 0);
			s3.Center = Vect4D(0, 0, -10, 0);
			s3.Radius = 5.0f;

			Box::ColResult result[51*3];
			int j = 0;
			for(int i = 0; i <= 50; i++)
			{

				result[j++] = b1.Collide(s1);
				result[j++] = b1.Collide(s2);
				result[j++] = b1.Collide(s3);
		

				s1.Center = s1.Center + d1;
				s2.Center = s2.Center + d2;
				s3.Center = s3.Center + d3;
			}

			CHECK(result[0] == Box::ColResult::Outside);
			CHECK(result[1] == Box::ColResult::Outside);
			CHECK(result[2] == Box::ColResult::Outside);
			CHECK(result[3] == Box::ColResult::Outside);
			CHECK(result[4] == Box::ColResult::Outside);
			CHECK(result[5] == Box::ColResult::Outside);
			CHECK(result[6] == Box::ColResult::Outside);
			CHECK(result[7] == Box::ColResult::Outside);
			CHECK(result[8] == Box::ColResult::Outside);
			CHECK(result[9] == Box::ColResult::Outside);
			CHECK(result[10] == Box::ColResult::Outside);
			CHECK(result[11] == Box::ColResult::Outside);
			CHECK(result[12] == Box::ColResult::Outside);
			CHECK(result[13] == Box::ColResult::Outside);
			CHECK(result[14] == Box::ColResult::Outside);
			CHECK(result[15] == Box::ColResult::Inside);
			CHECK(result[16] == Box::ColResult::Inside);
			CHECK(result[17] == Box::ColResult::Inside);
			CHECK(result[18] == Box::ColResult::Inside);
			CHECK(result[19] == Box::ColResult::Inside);
			CHECK(result[20] == Box::ColResult::Inside);
			CHECK(result[21] == Box::ColResult::Inside);
			CHECK(result[22] == Box::ColResult::Inside);
			CHECK(result[23] == Box::ColResult::Inside);
			CHECK(result[24] == Box::ColResult::Inside);
			CHECK(result[25] == Box::ColResult::Inside);
			CHECK(result[26] == Box::ColResult::Inside);
			CHECK(result[27] == Box::ColResult::Inside);
			CHECK(result[28] == Box::ColResult::Inside);
			CHECK(result[29] == Box::ColResult::Inside);
			CHECK(result[30] == Box::ColResult::Inside);
			CHECK(result[31] == Box::ColResult::Inside);
			CHECK(result[32] == Box::ColResult::Inside);
			CHECK(result[33] == Box::ColResult::Inside);
			CHECK(result[34] == Box::ColResult::Inside);
			CHECK(result[35] == Box::ColResult::Inside);
			CHECK(result[36] == Box::ColResult::Inside);
			CHECK(result[37] == Box::ColResult::Inside);
			CHECK(result[38] == Box::ColResult::Inside);
			CHECK(result[39] == Box::ColResult::Inside);
			CHECK(result[40] == Box::ColResult::Inside);
			CHECK(result[41] == Box::ColResult::Inside);
			CHECK(result[42] == Box::ColResult::Inside);
			CHECK(result[43] == Box::ColResult::Inside);
			CHECK(result[44] == Box::ColResult::Inside);
			CHECK(result[45] == Box::ColResult::Inside);
			CHECK(result[46] == Box::ColResult::Inside);
			CHECK(result[47] == Box::ColResult::Inside);
			CHECK(result[48] == Box::ColResult::Inside);
			CHECK(result[49] == Box::ColResult::Inside);
			CHECK(result[50] == Box::ColResult::Inside);
			CHECK(result[51] == Box::ColResult::Inside);
			CHECK(result[52] == Box::ColResult::Inside);
			CHECK(result[53] == Box::ColResult::Inside);
			CHECK(result[54] == Box::ColResult::Inside);
			CHECK(result[55] == Box::ColResult::Inside);
			CHECK(result[56] == Box::ColResult::Inside);
			CHECK(result[57] == Box::ColResult::Inside);
			CHECK(result[58] == Box::ColResult::Inside);
			CHECK(result[59] == Box::ColResult::Inside);
			CHECK(result[60] == Box::ColResult::Inside);
			CHECK(result[61] == Box::ColResult::Inside);
			CHECK(result[62] == Box::ColResult::Inside);
			CHECK(result[63] == Box::ColResult::Inside);
			CHECK(result[64] == Box::ColResult::Inside);
			CHECK(result[65] == Box::ColResult::Inside);
			CHECK(result[66] == Box::ColResult::Inside);
			CHECK(result[67] == Box::ColResult::Inside);
			CHECK(result[68] == Box::ColResult::Inside);
			CHECK(result[69] == Box::ColResult::Inside);
			CHECK(result[70] == Box::ColResult::Inside);
			CHECK(result[71] == Box::ColResult::Inside);
			CHECK(result[72] == Box::ColResult::Inside);
			CHECK(result[73] == Box::ColResult::Inside);
			CHECK(result[74] == Box::ColResult::Inside);
			CHECK(result[75] == Box::ColResult::Inside);
			CHECK(result[76] == Box::ColResult::Inside);
			CHECK(result[77] == Box::ColResult::Inside);
			CHECK(result[78] == Box::ColResult::Inside);
			CHECK(result[79] == Box::ColResult::Inside);
			CHECK(result[80] == Box::ColResult::Outside);
			CHECK(result[81] == Box::ColResult::Inside);
			CHECK(result[82] == Box::ColResult::Inside);
			CHECK(result[83] == Box::ColResult::Outside);
			CHECK(result[84] == Box::ColResult::Inside);
			CHECK(result[85] == Box::ColResult::Inside);
			CHECK(result[86] == Box::ColResult::Outside);
			CHECK(result[87] == Box::ColResult::Inside);
			CHECK(result[88] == Box::ColResult::Inside);
			CHECK(result[89] == Box::ColResult::Outside);
			CHECK(result[90] == Box::ColResult::Inside);
			CHECK(result[91] == Box::ColResult::Inside);
			CHECK(result[92] == Box::ColResult::Outside);
			CHECK(result[93] == Box::ColResult::Inside);
			CHECK(result[94] == Box::ColResult::Inside);
			CHECK(result[95] == Box::ColResult::Outside);
			CHECK(result[96] == Box::ColResult::Inside);
			CHECK(result[97] == Box::ColResult::Inside);
			CHECK(result[98] == Box::ColResult::Outside);
			CHECK(result[99] == Box::ColResult::Inside);
			CHECK(result[100] == Box::ColResult::Inside);
			CHECK(result[101] == Box::ColResult::Outside);
			CHECK(result[102] == Box::ColResult::Inside);
			CHECK(result[103] == Box::ColResult::Inside);
			CHECK(result[104] == Box::ColResult::Outside);
			CHECK(result[105] == Box::ColResult::Inside);
			CHECK(result[106] == Box::ColResult::Inside);
			CHECK(result[107] == Box::ColResult::Outside);
			CHECK(result[108] == Box::ColResult::Outside);
			CHECK(result[109] == Box::ColResult::Outside);
			CHECK(result[110] == Box::ColResult::Outside);
			CHECK(result[111] == Box::ColResult::Outside);
			CHECK(result[112] == Box::ColResult::Outside);
			CHECK(result[113] == Box::ColResult::Outside);
			CHECK(result[114] == Box::ColResult::Outside);
			CHECK(result[115] == Box::ColResult::Outside);
			CHECK(result[116] == Box::ColResult::Outside);
			CHECK(result[117] == Box::ColResult::Outside);
			CHECK(result[118] == Box::ColResult::Outside);
			CHECK(result[119] == Box::ColResult::Outside);
			CHECK(result[120] == Box::ColResult::Outside);
			CHECK(result[121] == Box::ColResult::Outside);
			CHECK(result[122] == Box::ColResult::Outside);
			CHECK(result[123] == Box::ColResult::Outside);
			CHECK(result[124] == Box::ColResult::Outside);
			CHECK(result[125] == Box::ColResult::Outside);
			CHECK(result[126] == Box::ColResult::Outside);
			CHECK(result[127] == Box::ColResult::Outside);
			CHECK(result[128] == Box::ColResult::Outside);
			CHECK(result[129] == Box::ColResult::Outside);
			CHECK(result[130] == Box::ColResult::Outside);
			CHECK(result[131] == Box::ColResult::Outside);
			CHECK(result[132] == Box::ColResult::Outside);
			CHECK(result[133] == Box::ColResult::Outside);
			CHECK(result[134] == Box::ColResult::Outside);
			CHECK(result[135] == Box::ColResult::Outside);
			CHECK(result[136] == Box::ColResult::Outside);
			CHECK(result[137] == Box::ColResult::Outside);
			CHECK(result[138] == Box::ColResult::Outside);
			CHECK(result[139] == Box::ColResult::Outside);
			CHECK(result[140] == Box::ColResult::Outside);
			CHECK(result[141] == Box::ColResult::Outside);
			CHECK(result[142] == Box::ColResult::Outside);
			CHECK(result[143] == Box::ColResult::Outside);
			CHECK(result[144] == Box::ColResult::Outside);
			CHECK(result[145] == Box::ColResult::Outside);
			CHECK(result[146] == Box::ColResult::Outside);
			CHECK(result[147] == Box::ColResult::Outside);
			CHECK(result[148] == Box::ColResult::Outside);
			CHECK(result[149] == Box::ColResult::Outside);
			CHECK(result[150] == Box::ColResult::Outside);
			CHECK(result[151] == Box::ColResult::Outside);
			CHECK(result[152] == Box::ColResult::Outside);

		}

		{
			Box_SIMD b1;

			b1.NearBottomLeftPoint = Vect4D_SIMD(-10, -10, 0, 0);
			b1.FarTopRightPoint = Vect4D_SIMD(10, 10, 10, 0);

			b1.TopNorm = Vect4D_SIMD(0, 1, 0, 0);
			b1.BottomNorm = Vect4D_SIMD(0, -1, 0, 0);

			b1.FrontNorm = Vect4D_SIMD(0, 0, -1, 0);
			b1.BackNorm = Vect4D_SIMD(0, 0, 1, 0);

			b1.LeftNorm = Vect4D_SIMD(-1, 0, 0, 0);
			b1.RightNorm = Vect4D_SIMD(1, 0, 0, 0);

			Sphere_SIMD s1;
			Sphere_SIMD s2;
			Sphere_SIMD s3;

			Vect4D_SIMD d1 = Vect4D_SIMD(1, 0, 0, 0);
			s1.Center = Vect4D_SIMD(-20, 0, 5, 0);
			s1.Radius = 5.0f;

			Vect4D_SIMD d2 = Vect4D_SIMD(0, 1, 0, 0);
			s2.Center = Vect4D_SIMD(0, -20, 5, 0);
			s2.Radius = 5.0f;

			Vect4D_SIMD d3 = Vect4D_SIMD(0, 0, 1, 0);
			s3.Center = Vect4D_SIMD(0, 0, -10, 0);
			s3.Radius = 5.0f;

			Box_SIMD::ColResult result[51 * 3];
			int j = 0;
			for(int i = 0; i <= 50; i++)
			{

				result[j++] = b1.Collide(s1);
				result[j++] = b1.Collide(s2);
				result[j++] = b1.Collide(s3);


				s1.Center = s1.Center + d1;
				s2.Center = s2.Center + d2;
				s3.Center = s3.Center + d3;
			}

			CHECK(result[0] == Box_SIMD::ColResult::Outside);
			CHECK(result[1] == Box_SIMD::ColResult::Outside);
			CHECK(result[2] == Box_SIMD::ColResult::Outside);
			CHECK(result[3] == Box_SIMD::ColResult::Outside);
			CHECK(result[4] == Box_SIMD::ColResult::Outside);
			CHECK(result[5] == Box_SIMD::ColResult::Outside);
			CHECK(result[6] == Box_SIMD::ColResult::Outside);
			CHECK(result[7] == Box_SIMD::ColResult::Outside);
			CHECK(result[8] == Box_SIMD::ColResult::Outside);
			CHECK(result[9] == Box_SIMD::ColResult::Outside);
			CHECK(result[10] == Box_SIMD::ColResult::Outside);
			CHECK(result[11] == Box_SIMD::ColResult::Outside);
			CHECK(result[12] == Box_SIMD::ColResult::Outside);
			CHECK(result[13] == Box_SIMD::ColResult::Outside);
			CHECK(result[14] == Box_SIMD::ColResult::Outside);
			CHECK(result[15] == Box_SIMD::ColResult::Inside);
			CHECK(result[16] == Box_SIMD::ColResult::Inside);
			CHECK(result[17] == Box_SIMD::ColResult::Inside);
			CHECK(result[18] == Box_SIMD::ColResult::Inside);
			CHECK(result[19] == Box_SIMD::ColResult::Inside);
			CHECK(result[20] == Box_SIMD::ColResult::Inside);
			CHECK(result[21] == Box_SIMD::ColResult::Inside);
			CHECK(result[22] == Box_SIMD::ColResult::Inside);
			CHECK(result[23] == Box_SIMD::ColResult::Inside);
			CHECK(result[24] == Box_SIMD::ColResult::Inside);
			CHECK(result[25] == Box_SIMD::ColResult::Inside);
			CHECK(result[26] == Box_SIMD::ColResult::Inside);
			CHECK(result[27] == Box_SIMD::ColResult::Inside);
			CHECK(result[28] == Box_SIMD::ColResult::Inside);
			CHECK(result[29] == Box_SIMD::ColResult::Inside);
			CHECK(result[30] == Box_SIMD::ColResult::Inside);
			CHECK(result[31] == Box_SIMD::ColResult::Inside);
			CHECK(result[32] == Box_SIMD::ColResult::Inside);
			CHECK(result[33] == Box_SIMD::ColResult::Inside);
			CHECK(result[34] == Box_SIMD::ColResult::Inside);
			CHECK(result[35] == Box_SIMD::ColResult::Inside);
			CHECK(result[36] == Box_SIMD::ColResult::Inside);
			CHECK(result[37] == Box_SIMD::ColResult::Inside);
			CHECK(result[38] == Box_SIMD::ColResult::Inside);
			CHECK(result[39] == Box_SIMD::ColResult::Inside);
			CHECK(result[40] == Box_SIMD::ColResult::Inside);
			CHECK(result[41] == Box_SIMD::ColResult::Inside);
			CHECK(result[42] == Box_SIMD::ColResult::Inside);
			CHECK(result[43] == Box_SIMD::ColResult::Inside);
			CHECK(result[44] == Box_SIMD::ColResult::Inside);
			CHECK(result[45] == Box_SIMD::ColResult::Inside);
			CHECK(result[46] == Box_SIMD::ColResult::Inside);
			CHECK(result[47] == Box_SIMD::ColResult::Inside);
			CHECK(result[48] == Box_SIMD::ColResult::Inside);
			CHECK(result[49] == Box_SIMD::ColResult::Inside);
			CHECK(result[50] == Box_SIMD::ColResult::Inside);
			CHECK(result[51] == Box_SIMD::ColResult::Inside);
			CHECK(result[52] == Box_SIMD::ColResult::Inside);
			CHECK(result[53] == Box_SIMD::ColResult::Inside);
			CHECK(result[54] == Box_SIMD::ColResult::Inside);
			CHECK(result[55] == Box_SIMD::ColResult::Inside);
			CHECK(result[56] == Box_SIMD::ColResult::Inside);
			CHECK(result[57] == Box_SIMD::ColResult::Inside);
			CHECK(result[58] == Box_SIMD::ColResult::Inside);
			CHECK(result[59] == Box_SIMD::ColResult::Inside);
			CHECK(result[60] == Box_SIMD::ColResult::Inside);
			CHECK(result[61] == Box_SIMD::ColResult::Inside);
			CHECK(result[62] == Box_SIMD::ColResult::Inside);
			CHECK(result[63] == Box_SIMD::ColResult::Inside);
			CHECK(result[64] == Box_SIMD::ColResult::Inside);
			CHECK(result[65] == Box_SIMD::ColResult::Inside);
			CHECK(result[66] == Box_SIMD::ColResult::Inside);
			CHECK(result[67] == Box_SIMD::ColResult::Inside);
			CHECK(result[68] == Box_SIMD::ColResult::Inside);
			CHECK(result[69] == Box_SIMD::ColResult::Inside);
			CHECK(result[70] == Box_SIMD::ColResult::Inside);
			CHECK(result[71] == Box_SIMD::ColResult::Inside);
			CHECK(result[72] == Box_SIMD::ColResult::Inside);
			CHECK(result[73] == Box_SIMD::ColResult::Inside);
			CHECK(result[74] == Box_SIMD::ColResult::Inside);
			CHECK(result[75] == Box_SIMD::ColResult::Inside);
			CHECK(result[76] == Box_SIMD::ColResult::Inside);
			CHECK(result[77] == Box_SIMD::ColResult::Inside);
			CHECK(result[78] == Box_SIMD::ColResult::Inside);
			CHECK(result[79] == Box_SIMD::ColResult::Inside);
			CHECK(result[80] == Box_SIMD::ColResult::Outside);
			CHECK(result[81] == Box_SIMD::ColResult::Inside);
			CHECK(result[82] == Box_SIMD::ColResult::Inside);
			CHECK(result[83] == Box_SIMD::ColResult::Outside);
			CHECK(result[84] == Box_SIMD::ColResult::Inside);
			CHECK(result[85] == Box_SIMD::ColResult::Inside);
			CHECK(result[86] == Box_SIMD::ColResult::Outside);
			CHECK(result[87] == Box_SIMD::ColResult::Inside);
			CHECK(result[88] == Box_SIMD::ColResult::Inside);
			CHECK(result[89] == Box_SIMD::ColResult::Outside);
			CHECK(result[90] == Box_SIMD::ColResult::Inside);
			CHECK(result[91] == Box_SIMD::ColResult::Inside);
			CHECK(result[92] == Box_SIMD::ColResult::Outside);
			CHECK(result[93] == Box_SIMD::ColResult::Inside);
			CHECK(result[94] == Box_SIMD::ColResult::Inside);
			CHECK(result[95] == Box_SIMD::ColResult::Outside);
			CHECK(result[96] == Box_SIMD::ColResult::Inside);
			CHECK(result[97] == Box_SIMD::ColResult::Inside);
			CHECK(result[98] == Box_SIMD::ColResult::Outside);
			CHECK(result[99] == Box_SIMD::ColResult::Inside);
			CHECK(result[100] == Box_SIMD::ColResult::Inside);
			CHECK(result[101] == Box_SIMD::ColResult::Outside);
			CHECK(result[102] == Box_SIMD::ColResult::Inside);
			CHECK(result[103] == Box_SIMD::ColResult::Inside);
			CHECK(result[104] == Box_SIMD::ColResult::Outside);
			CHECK(result[105] == Box_SIMD::ColResult::Inside);
			CHECK(result[106] == Box_SIMD::ColResult::Inside);
			CHECK(result[107] == Box_SIMD::ColResult::Outside);
			CHECK(result[108] == Box_SIMD::ColResult::Outside);
			CHECK(result[109] == Box_SIMD::ColResult::Outside);
			CHECK(result[110] == Box_SIMD::ColResult::Outside);
			CHECK(result[111] == Box_SIMD::ColResult::Outside);
			CHECK(result[112] == Box_SIMD::ColResult::Outside);
			CHECK(result[113] == Box_SIMD::ColResult::Outside);
			CHECK(result[114] == Box_SIMD::ColResult::Outside);
			CHECK(result[115] == Box_SIMD::ColResult::Outside);
			CHECK(result[116] == Box_SIMD::ColResult::Outside);
			CHECK(result[117] == Box_SIMD::ColResult::Outside);
			CHECK(result[118] == Box_SIMD::ColResult::Outside);
			CHECK(result[119] == Box_SIMD::ColResult::Outside);
			CHECK(result[120] == Box_SIMD::ColResult::Outside);
			CHECK(result[121] == Box_SIMD::ColResult::Outside);
			CHECK(result[122] == Box_SIMD::ColResult::Outside);
			CHECK(result[123] == Box_SIMD::ColResult::Outside);
			CHECK(result[124] == Box_SIMD::ColResult::Outside);
			CHECK(result[125] == Box_SIMD::ColResult::Outside);
			CHECK(result[126] == Box_SIMD::ColResult::Outside);
			CHECK(result[127] == Box_SIMD::ColResult::Outside);
			CHECK(result[128] == Box_SIMD::ColResult::Outside);
			CHECK(result[129] == Box_SIMD::ColResult::Outside);
			CHECK(result[130] == Box_SIMD::ColResult::Outside);
			CHECK(result[131] == Box_SIMD::ColResult::Outside);
			CHECK(result[132] == Box_SIMD::ColResult::Outside);
			CHECK(result[133] == Box_SIMD::ColResult::Outside);
			CHECK(result[134] == Box_SIMD::ColResult::Outside);
			CHECK(result[135] == Box_SIMD::ColResult::Outside);
			CHECK(result[136] == Box_SIMD::ColResult::Outside);
			CHECK(result[137] == Box_SIMD::ColResult::Outside);
			CHECK(result[138] == Box_SIMD::ColResult::Outside);
			CHECK(result[139] == Box_SIMD::ColResult::Outside);
			CHECK(result[140] == Box_SIMD::ColResult::Outside);
			CHECK(result[141] == Box_SIMD::ColResult::Outside);
			CHECK(result[142] == Box_SIMD::ColResult::Outside);
			CHECK(result[143] == Box_SIMD::ColResult::Outside);
			CHECK(result[144] == Box_SIMD::ColResult::Outside);
			CHECK(result[145] == Box_SIMD::ColResult::Outside);
			CHECK(result[146] == Box_SIMD::ColResult::Outside);
			CHECK(result[147] == Box_SIMD::ColResult::Outside);
			CHECK(result[148] == Box_SIMD::ColResult::Outside);
			CHECK(result[149] == Box_SIMD::ColResult::Outside);
			CHECK(result[150] == Box_SIMD::ColResult::Outside);
			CHECK(result[151] == Box_SIMD::ColResult::Outside);
			CHECK(result[152] == Box_SIMD::ColResult::Outside);
			
			Collide_unit_result = 1;
		}

	}

#endif
} TEST_END

// ---  End of File ---
