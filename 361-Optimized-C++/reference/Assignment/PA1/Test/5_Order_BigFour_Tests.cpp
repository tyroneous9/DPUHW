//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"

#include "HotDog.h"
#include "Order.h"
#include "Stand.h"

#include "TestStruct.h"

// ----------------------------------
// ---     DO NOT MODIFY FILE     ---
// ----------------------------------

static Order *pJamieOrder(nullptr);

TEST_WITH_TEARDOWN(BigFour_Orders, TestConfig::ALL)
{
#if BigFour_Orders
	
	// -----------------------------------------------
	// Default constructor
	// -----------------------------------------------
	Order R;
	CHECK(((TestOrder &)R).name == Name::Unknown)
	CHECK(((TestOrder &)R).poHead == nullptr);

	// -----------------------------------------------
	// Specialize constructor
	// -----------------------------------------------
	Order S(Name::Arya);
	CHECK(((TestOrder &)S).name == Name::Arya);
	CHECK(((TestOrder &)S).poHead == nullptr);

	// -----------------------------------------------
	// Create a complicated order
	// -----------------------------------------------
	pJamieOrder = new Order(Name::Jaime);

	CHECK(pJamieOrder != nullptr);
	CHECK(((TestOrder *)pJamieOrder)->name == Name::Jaime);
	CHECK(((TestOrder *)pJamieOrder)->pNext == nullptr);
	CHECK(((TestOrder *)pJamieOrder)->pPrev == nullptr);

	HotDog *A = new HotDog();
	CHECK(A != nullptr);

	A->Add(Condiments::Yellow_Mustard);
	A->Add(Condiments::Chopped_Onions);
	A->Add(Condiments::Pickle_Spear);
	A->Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog *)A)->condiments == 0xd4);

	pJamieOrder->Add(A);

	HotDog *B = new HotDog();
	CHECK(B != nullptr);

	B->Add(Condiments::Yellow_Mustard);
	B->Add(Condiments::Chopped_Onions);
	B->Add(Condiments::Pickle_Spear);
	B->Add(Condiments::Celery_Salt);
	B->Add(Condiments::Ketchup);
	B->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)B)->condiments == 0xdd);

	pJamieOrder->Add(B);

	HotDog *C = new HotDog();
	CHECK(C != nullptr);

	C->Add(Condiments::Green_Relish);
	C->Add(Condiments::Chopped_Onions);
	C->Add(Condiments::Sport_Peppers);
	C->Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog *)C)->condiments == 0xe2);

	pJamieOrder->Add(C);

	HotDog *D = new HotDog();
	CHECK(D != nullptr);

	D->Add(Condiments::Green_Relish);
	D->Add(Condiments::Chopped_Onions);
	D->Add(Condiments::Sport_Peppers);
	D->Add(Condiments::Celery_Salt);
	D->Add(Condiments::Ketchup);
	D->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)D)->condiments == 0xeb);

	pJamieOrder->Add(D);

	TestHotDog *pDog = ((TestOrder *)pJamieOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xe2);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xdd);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xe2);
	CHECK(pDog->pNext->condiments == 0xd4);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Copy constructor - with deep copy
	// -----------------------------------------------
	Order T(*pJamieOrder);

	// Make verify deep copy
	CHECK(((TestOrder &)T).name == ((TestOrder *)pJamieOrder)->name);
	CHECK(((TestOrder &)T).pNext == nullptr);
	CHECK(((TestOrder &)T).pPrev == nullptr);

	pDog = ((TestOrder &)T).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xe2);

	HotDog *T0 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xdd);

	HotDog *T1 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xe2);
	CHECK(pDog->pNext->condiments == 0xd4);

	HotDog *T2 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	HotDog *T3 = (HotDog *)pDog;

	// Make sure Jamie isn't corrupted
	pDog = ((TestOrder *)pJamieOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xe2);

	HotDog *S0 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xdd);

	HotDog *S1 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xe2);
	CHECK(pDog->pNext->condiments == 0xd4);

	HotDog *S2 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	HotDog *S3 = (HotDog *)pDog;

	// Make sure they are not equal
	CHECK(T0 != S0);
	CHECK(T1 != S1);
	CHECK(T2 != S2);
	CHECK(T3 != S3);

	// -----------------------------------------------
	// Assignment operator
	// -----------------------------------------------
	Order M;
	CHECK(((TestOrder &)M).name == Name::Unknown);
	CHECK(((TestOrder &)M).poHead == nullptr);

	M = *pJamieOrder;

	// Make verify deep copy
	CHECK(((TestOrder &)M).name == ((TestOrder *)pJamieOrder)->name);
	CHECK(((TestOrder &)M).pNext == nullptr);
	CHECK(((TestOrder &)M).pPrev == nullptr);

	pDog = ((TestOrder &)M).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xe2);

	HotDog *M0 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xdd);

	HotDog *M1 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xe2);
	CHECK(pDog->pNext->condiments == 0xd4);

	HotDog *M2 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	HotDog *M3 = (HotDog *)pDog;

	// Make sure Jamie isn't corrupted
	pDog = ((TestOrder *)pJamieOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xe2);

	S0 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xdd);

	S1 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xe2);
	CHECK(pDog->pNext->condiments == 0xd4);

	S2 = (HotDog *)pDog;

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	S3 = (HotDog *)pDog;

	// Make sure they are not equal
	CHECK(M0 != S0);
	CHECK(M1 != S1);
	CHECK(M2 != S2);
	CHECK(M3 != S3);

	// -----------------------------------------------
	// destructor - is called freeing up all HotDogs
	// -----------------------------------------------
	delete pJamieOrder;
	pJamieOrder = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(BigFour_Orders)
{
	delete pJamieOrder;
}

//---  End of File ---
