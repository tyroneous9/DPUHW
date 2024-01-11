//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"

#include "TestStruct.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------
static HotDog *pE2(nullptr);

TEST_WITH_TEARDOWN(Big_Four, TestConfig::ALL)
{
#if Big_Four

	// -----------------------------------------------
	// Default constructor
	// -----------------------------------------------
	HotDog  A;
	CHECK(((TestHotDog &)A).pNext == nullptr);
	CHECK(((TestHotDog &)A).pPrev == nullptr);
	CHECK(((TestHotDog &)A).condiments == 0);

	HotDog  AA;
	CHECK(((TestHotDog &)AA).pNext == nullptr);
	CHECK(((TestHotDog &)AA).pPrev == nullptr);
	CHECK(((TestHotDog &)AA).condiments == 0);

	// -----------------------------------------------
	// B - complicated node used in copy constructor
	// -----------------------------------------------
	HotDog B;

	B.Add(Condiments::Everything);
	B.Minus(Condiments::Chopped_Onions);
	B.Minus(Condiments::Green_Relish);
	B.Add(Condiments::Ketchup);
	
	// Force some unique data to insure no cross wiring
	((TestHotDog &)B).pNext = (TestHotDog *)&AA;
	((TestHotDog &)B).pPrev = (TestHotDog *)&A;

	CHECK(((TestHotDog &)B).pNext == (TestHotDog *)&AA);
	CHECK(((TestHotDog &)B).pPrev == (TestHotDog *)&A);
	CHECK(((TestHotDog &)B).condiments == 0x7d);

	// -----------------------------------------------
	// Copy constructor
	// -----------------------------------------------
	HotDog C(B);

	// Copy B into C
	CHECK(((TestHotDog &)C).pNext == nullptr);
	CHECK(((TestHotDog &)C).pPrev == nullptr);
	CHECK(((TestHotDog &)C).condiments == 0x7d);

	// Make sure B isn't corrupted
	CHECK(((TestHotDog &)B).pNext == (TestHotDog *)&AA);
	CHECK(((TestHotDog &)B).pPrev == (TestHotDog *)&A);
	CHECK(((TestHotDog &)B).condiments == 0x7d);

	// ----------------------------------------------
	// Assignment operator
	// -----------------------------------------------
	HotDog D;
	CHECK(((TestHotDog &)D).pNext == nullptr);
	CHECK(((TestHotDog &)D).pPrev == nullptr);
	CHECK(((TestHotDog &)D).condiments == 0);

	D = B;

	// Copy B into C
	CHECK(((TestHotDog &)D).pNext == nullptr);
	CHECK(((TestHotDog &)D).pPrev == nullptr);
	CHECK(((TestHotDog &)D).condiments == 0x7d);

	// Make sure B isn't corrupted
	CHECK(((TestHotDog &)B).pNext == (TestHotDog *)&AA);
	CHECK(((TestHotDog &)B).pPrev == (TestHotDog *)&A);
	CHECK(((TestHotDog &)B).condiments == 0x7d);

	// -----------------------------------------------
	// Destructor
	// -----------------------------------------------
	pE2 = new HotDog();
	CHECK(pE2 != nullptr);

	pE2->Add(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog *)pE2)->condiments == 0x10);
	CHECK(((TestHotDog *)pE2)->pNext == nullptr);
	CHECK(((TestHotDog *)pE2)->pPrev == nullptr);

	delete pE2;
	pE2 = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(Big_Four)
{
	delete pE2;
}

//---  End of File ---
