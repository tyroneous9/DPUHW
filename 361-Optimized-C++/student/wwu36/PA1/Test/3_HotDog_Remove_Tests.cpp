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

TEST(Remove_HotDog, TestConfig::ALL)
{
#if Remove_HotDog

	// -----------------------------------------------
	// Create an order
	// -----------------------------------------------
	Order JamieOrder(Name::Jaime);

	CHECK( ((TestOrder &)JamieOrder).poHead == nullptr);
	CHECK(((TestOrder &)JamieOrder).name == Name::Jaime);
	CHECK(((TestOrder &)JamieOrder).pNext == nullptr);
	CHECK(((TestOrder &)JamieOrder).pPrev == nullptr);

	// -----------------------------------------------
	// Create 4 HotDogs to add to Order
	// -----------------------------------------------
	HotDog *pA3 = new HotDog();
	CHECK(pA3 != nullptr);

	pA3->Add(Condiments::Yellow_Mustard);
	pA3->Add(Condiments::Chopped_Onions);
	pA3->Add(Condiments::Pickle_Spear);
	pA3->Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog *)pA3)->condiments == 0xd4);

	JamieOrder.Add(pA3);

	HotDog *pB3 = new HotDog();
	CHECK(pB3 != nullptr);

	pB3->Add(Condiments::Yellow_Mustard);
	pB3->Add(Condiments::Chopped_Onions);
	pB3->Add(Condiments::Pickle_Spear);
	pB3->Add(Condiments::Celery_Salt);
	pB3->Add(Condiments::Ketchup);
	pB3->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)pB3)->condiments == 0xdd);

	JamieOrder.Add(pB3);

	HotDog *pC3 = new HotDog();
	CHECK(pC3 != nullptr);

	pC3->Add(Condiments::Green_Relish);
	pC3->Add(Condiments::Chopped_Onions);
	pC3->Add(Condiments::Sport_Peppers);
	pC3->Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog *)pC3)->condiments == 0xe2);

	JamieOrder.Add(pC3);

	HotDog *pD3 = new HotDog();
	CHECK(pD3 != nullptr);

	pD3->Add(Condiments::Green_Relish);
	pD3->Add(Condiments::Chopped_Onions);
	pD3->Add(Condiments::Sport_Peppers);
	pD3->Add(Condiments::Celery_Salt);
	pD3->Add(Condiments::Ketchup);
	pD3->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)pD3)->condiments == 0xeb);

	JamieOrder.Add(pD3);

	// Verify HotDogs in order
	CHECK(((TestOrder &)JamieOrder).name == Name::Jaime);
	CHECK(((TestOrder &)JamieOrder).pNext == nullptr);
	CHECK(((TestOrder &)JamieOrder).pPrev == nullptr);

	const TestHotDog *pDog = ((TestOrder &)JamieOrder).poHead;
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
	// Remove HotDogs one at a Time
	// 
	//     Setup is done:  AA->BB->CC->DD
	// -----------------------------------------------

	// -----------------------------------------------
	// Delete CC
	//     AA->BB->DD
	// -----------------------------------------------
	JamieOrder.Remove(pC3);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xdd);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext->condiments == 0xd4);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Delete AA
	//     BB->DD
	// -----------------------------------------------
	JamieOrder.Remove(pA3);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xeb);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xdd);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev->condiments == 0xeb);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Delete DD
	//     BB
	// -----------------------------------------------
	JamieOrder.Remove(pD3);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Delete BB
	//     empty
	// -----------------------------------------------
	JamieOrder.Remove(pB3);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog == nullptr);

#endif
} TEST_END

//---  End of File ---
