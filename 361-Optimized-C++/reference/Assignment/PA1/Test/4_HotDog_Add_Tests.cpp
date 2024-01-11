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

TEST(Add_HotDog, TestConfig::ALL)
{
#if Add_HotDog

	// -----------------------------------------------
	// Create an order
	// -----------------------------------------------
	Order JamieOrder(Name::Jaime);

	CHECK(((TestOrder &)JamieOrder).poHead == nullptr);
	CHECK(((TestOrder &)JamieOrder).name == Name::Jaime);
	CHECK(((TestOrder &)JamieOrder).pNext == nullptr);
	CHECK(((TestOrder &)JamieOrder).pPrev == nullptr);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog *pA4 = new HotDog();
	CHECK(pA4 != nullptr);

	pA4->Add(Condiments::Yellow_Mustard);
	pA4->Add(Condiments::Chopped_Onions);
	pA4->Add(Condiments::Pickle_Spear);
	pA4->Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog *)pA4)->condiments == 0xd4);

	JamieOrder.Add(pA4);

	const TestHotDog *pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog *pB4 = new HotDog();
	CHECK(pB4 != nullptr);

	pB4->Add(Condiments::Yellow_Mustard);
	pB4->Add(Condiments::Chopped_Onions);
	pB4->Add(Condiments::Pickle_Spear);
	pB4->Add(Condiments::Celery_Salt);
	pB4->Add(Condiments::Ketchup);
	pB4->Add(Condiments::Tomato_Wedge);
	CHECK( ((TestHotDog *)pB4)->condiments == 0xdd);

	JamieOrder.Add(pB4);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xdd);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xd4);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xd4);
	CHECK(pDog->pPrev->condiments == 0xdd);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog *pC4 = new HotDog();
	CHECK(pC4 != nullptr);

	pC4->Add(Condiments::Green_Relish);
	pC4->Add(Condiments::Chopped_Onions);
	pC4->Add(Condiments::Sport_Peppers);
	pC4->Add(Condiments::Celery_Salt);
	CHECK( ((TestHotDog *)pC4)->condiments == 0xe2);

	JamieOrder.Add(pC4);

	pDog = ((TestOrder &)JamieOrder).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xe2);
	CHECK(pDog->pPrev == nullptr);
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
	// Add a HotDog to an Order
	// -----------------------------------------------
	HotDog *pD4 = new HotDog();
	CHECK(pD4 != nullptr);

	pD4->Add(Condiments::Ketchup);
	pD4->Add(Condiments::Green_Relish);
	pD4->Add(Condiments::Chopped_Onions);
	pD4->Add(Condiments::Sport_Peppers);
	pD4->Add(Condiments::Celery_Salt);
	pD4->Add(Condiments::Ketchup);
	pD4->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)pD4)->condiments == 0xeb);

	JamieOrder.Add(pD4);

	pDog = ((TestOrder &)JamieOrder).poHead;
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

#endif
} TEST_END

//---  End of File ---
