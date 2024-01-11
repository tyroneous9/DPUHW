//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "PerformanceTest.h"

int collide_test()
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
	Box::ColResult result;

	Vect4D d1 = Vect4D(0.000001f, 0, 0, 0);
	s1.Center = Vect4D(-20, 0, 5, 0);
	s1.Radius = 5.0f;

	Vect4D d2 = Vect4D(0, 0.000001f, 0, 0);
	s2.Center = Vect4D(0, -20, 5, 0);
	s2.Radius = 5.0f;

	Vect4D d3 = Vect4D(0, 0, 0.000001f, 0);
    s3.Center = Vect4D(0, 0, -10, 0);
	s3.Radius = 5.0f;

	int kResult = 0;
	for(int i = 0; i <= 50000000; i++)
	{

		result = b1.Collide(s1);
		kResult += (int)result;
		result = b1.Collide(s2);
		kResult += (int)result;
		result = b1.Collide(s3);
		kResult += (int)result;

		s1.Center = s1.Center + d1;
		s2.Center = s2.Center + d2;
		s3.Center = s3.Center + d3;
	}

	


	return kResult;
}

// ---  End of File ---------------
