//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Sphere.h"

void Sphere::Print()
{
	Trace::out("Sphere: %f %f %f  rad: %f \n", Center.x, Center.y, Center.z, Radius);
}

// --- End of File ---
