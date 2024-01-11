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

TEST(Remove_Orders, TestConfig::ALL)
{
#if Remove_Orders

	// -----------------------------------------------
	// Create a Jamie order
	// -----------------------------------------------
	Order *pJamieOrder = new Order(Name::Jaime);
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

	const TestHotDog *pDog = ((TestOrder *)pJamieOrder)->poHead;
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
	// Create a Cersei order
	// -----------------------------------------------
	Order *pCerseiOrder = new Order(Name::Cersei);
	CHECK(pCerseiOrder != nullptr);
	CHECK(((TestOrder *)pCerseiOrder)->name == Name::Cersei);
	CHECK(((TestOrder *)pCerseiOrder)->pNext == nullptr);
	CHECK(((TestOrder *)pCerseiOrder)->pPrev == nullptr);

	HotDog *E = new HotDog();
	CHECK(E != nullptr);

	E->Add(Condiments::Everything);
	E->Minus(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)E)->condiments == 0xf6);

	pCerseiOrder->Add(E);

	HotDog *F = new HotDog();
	CHECK(F != nullptr);

	F->Add(Condiments::Everything);
	F->Add(Condiments::Ketchup);
	CHECK(((TestHotDog *)F)->condiments == 0xFF);

	pCerseiOrder->Add(F);

	pDog = ((TestOrder *)pCerseiOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xff);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xF6);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xF6);
	CHECK(pDog->pPrev->condiments == 0xff);
	CHECK(pDog->pNext == nullptr);


	// -----------------------------------------------
	// Create a Arya order
	// -----------------------------------------------
	Order *pAryaOrder = new Order(Name::Arya);
	CHECK(pAryaOrder != nullptr);
	CHECK(((TestOrder *)pAryaOrder)->name == Name::Arya);
	CHECK(((TestOrder *)pAryaOrder)->pNext == nullptr);
	CHECK(((TestOrder *)pAryaOrder)->pPrev == nullptr);

	HotDog *M11 = new HotDog();
	CHECK(M11 != nullptr);

	M11->Add(Condiments::Ketchup);
	M11->Add(Condiments::Tomato_Wedge);
	CHECK(((TestHotDog *)M11)->condiments == 0x09);

	pAryaOrder->Add(M11);

	HotDog *M22 = new HotDog();
	CHECK(M22 != nullptr);

	M22->Add(Condiments::Yellow_Mustard);
	M22->Add(Condiments::Pickle_Spear);
	CHECK(((TestHotDog *)M22)->condiments == 0x14);

	pAryaOrder->Add(M22);

	HotDog *M22_1 = new HotDog(*M22);
	CHECK(M22_1 != nullptr)

	pAryaOrder->Add(M22_1);

	HotDog *M22_2 = new HotDog(*M22);
	CHECK(M22_2 != nullptr);

	pAryaOrder->Add(M22_2);

	HotDog *M22_3 = new HotDog(*M22);
	CHECK(M22_3 != nullptr);

	pAryaOrder->Add(M22_3);

	pDog = ((TestOrder *)pAryaOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x09);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x09);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Create a Sansa order
	// -----------------------------------------------
	Order *pSansaOrder = new Order(Name::Sansa);
	CHECK(pSansaOrder != nullptr);
	CHECK(((TestOrder *)pSansaOrder)->name == Name::Sansa);
	CHECK(((TestOrder *)pSansaOrder)->pNext == nullptr);
	CHECK(((TestOrder *)pSansaOrder)->pPrev == nullptr);

	HotDog *M33 = new HotDog();
	CHECK(M33 != nullptr);

	M33->Add(Condiments::Ketchup);
	M33->Add(Condiments::Yellow_Mustard);
	M33->Add(Condiments::Tomato_Wedge);
	M33->Add(Condiments::Pickle_Spear);
	CHECK(((TestHotDog *)M33)->condiments == 0x1d);

	pSansaOrder->Add(M33);

	HotDog *M00 = new HotDog();
	CHECK(M00 != nullptr);
	CHECK(((TestHotDog *)M00)->condiments == 0x00);

	pSansaOrder->Add(M00);

	HotDog *M00_1 = new HotDog();
	CHECK(M00_1 != nullptr);
	CHECK(((TestHotDog *)M00_1)->condiments == 0x00);

	pSansaOrder->Add(M00_1);

	HotDog *M44 = new HotDog();
	CHECK(M44 != nullptr);

	M44->Add(Condiments::Green_Relish);
	M44->Add(Condiments::Sport_Peppers);
	CHECK(((TestHotDog *)M44)->condiments == 0x22);

	pSansaOrder->Add(M44);

	pDog = ((TestOrder *)pSansaOrder)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x22);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x0);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x0);
	CHECK(pDog->pPrev->condiments == 0x22);
	CHECK(pDog->pNext->condiments == 0x0);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x0);
	CHECK(pDog->pPrev->condiments == 0x0);
	CHECK(pDog->pNext->condiments == 0x1d);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x1d);
	CHECK(pDog->pPrev->condiments == 0x0);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Stand - add 4 orders
	// -----------------------------------------------

	Stand stand;
	CHECK(stand.GetCurrOrders() == 0);
	CHECK(stand.GetPeakOrders() == 0);
	CHECK(((TestStand &)stand).poHead == nullptr);

	stand.Add(pJamieOrder);
	CHECK(stand.GetCurrOrders() == 1);
	CHECK(stand.GetPeakOrders() == 1);

	const TestOrder *pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Jaime);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext == nullptr);

	stand.Add(pCerseiOrder);
	CHECK(stand.GetCurrOrders() == 2);
	CHECK(stand.GetPeakOrders() == 2);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Jaime);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext->name == Name::Cersei);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev->name == Name::Jaime);
	CHECK(pOrder->pNext == nullptr);

	stand.Add(pAryaOrder);

	CHECK(stand.GetCurrOrders() == 3);
	CHECK(stand.GetPeakOrders() == 3);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Jaime);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext->name == Name::Cersei);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev->name == Name::Jaime);
	CHECK(pOrder->pNext->name == Name::Arya);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Arya);
	CHECK(pOrder->pPrev->name == Name::Cersei);
	CHECK(pOrder->pNext == nullptr);

	stand.Add(pSansaOrder);

	// ---------------------------------------------------
	//  Verify the 4 orders with hotdogs
	// ---------------------------------------------------

	CHECK(stand.GetCurrOrders() == 4);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Jaime);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext->name == Name::Cersei);

	pDog = pOrder->poHead;
	CHECK(pDog != nullptr);

	// Verify Jaime's order
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
	CHECK(pDog->pNext == nullptr)

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	// Verify Cersei's order
	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev->name == Name::Jaime);
	CHECK(pOrder->pNext->name == Name::Arya);

	pDog = pOrder->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xff);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xF6);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xF6);
	CHECK(pDog->pPrev->condiments == 0xff);
	CHECK(pDog->pNext == nullptr);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	// Verify Arya's order
	CHECK(pOrder->name == Name::Arya);
	CHECK(pOrder->pPrev->name == Name::Cersei);
	CHECK(pOrder->pNext->name == Name::Sansa);

	pDog = pOrder->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x14);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x14);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext->condiments == 0x09);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x09);
	CHECK(pDog->pPrev->condiments == 0x14);
	CHECK(pDog->pNext == nullptr);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	// Verify Sansa's order
	CHECK(pOrder->name == Name::Sansa);
	CHECK(pOrder->pPrev->name == Name::Arya);
	CHECK(pOrder->pNext == nullptr);

	pDog = pOrder->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x22);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x0);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x0);
	CHECK(pDog->pPrev->condiments == 0x22);
	CHECK(pDog->pNext->condiments == 0x0);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x0);
	CHECK(pDog->pPrev->condiments == 0x0);
	CHECK(pDog->pNext->condiments == 0x1d);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x1d);
	CHECK(pDog->pPrev->condiments == 0x0);
	CHECK(pDog->pNext == nullptr);

	// -----------------------------------------------
	// Remove Orders one at a Time
	// 
	//     Setup is done:  Jamie->Cersei->Arya->Sansa
	// -----------------------------------------------

	// -----------------------------------------------
	// Delete Arya
	//     Jamie->Cersei->Sansa
	// -----------------------------------------------
	stand.Remove(Name::Arya);

	CHECK(stand.GetCurrOrders() == 3);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Jaime);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext->name == Name::Cersei);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev->name == Name::Jaime);
	CHECK(pOrder->pNext->name == Name::Sansa);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Sansa);
	CHECK(pOrder->pPrev->name == Name::Cersei);
	CHECK(pOrder->pNext == nullptr);

	// -----------------------------------------------
	// Delete Jamie
	//     Cersei->Sansa
	// -----------------------------------------------
	stand.Remove(Name::Jaime);

	CHECK(stand.GetCurrOrders() == 2);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext->name == Name::Sansa);

	pOrder = pOrder->pNext;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Sansa);
	CHECK(pOrder->pPrev->name == Name::Cersei);
	CHECK(pOrder->pNext == nullptr);

	// -----------------------------------------------
	// Delete Sansa
	//     Cersei
	// -----------------------------------------------
	stand.Remove(Name::Sansa);

	CHECK(stand.GetCurrOrders() == 1);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder != nullptr);

	CHECK(pOrder->name == Name::Cersei);
	CHECK(pOrder->pPrev == nullptr);
	CHECK(pOrder->pNext == nullptr);

	// -----------------------------------------------
	// Delete Cersei
	//     empty
	// -----------------------------------------------
	stand.Remove(Name::Cersei);

	CHECK(stand.GetCurrOrders() == 0);
	CHECK(stand.GetPeakOrders() == 4);

	pOrder = ((TestStand &)stand).poHead;
	CHECK(pOrder == nullptr);


	// -----------------------------------------------
	// Loop hole
	// -----------------------------------------------

	HotDog *L1 = new HotDog();
	CHECK(L1 != nullptr);

	L1->Add(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog *)L1)->condiments == 0x10);

	HotDog *L2 = new HotDog();
	CHECK(L2 != nullptr);

	L2->Add(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog *)L2)->condiments == 0x10);

	HotDog *L3 = new HotDog();
	CHECK(L3 != nullptr);

	L3->Add(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog *)L3)->condiments == 0x10);

	HotDog *L4 = new HotDog();
	CHECK(L4 != nullptr);

	L4->Add(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog *)L4)->condiments == 0x10);

	Order O(Name::Samwell);

	O.Add(L1);
	O.Add(L2);
	O.Add(L3);
	O.Add(L4);

	pDog = ((TestOrder &)O).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog == (TestHotDog *)L4);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == (TestHotDog *)L3);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L3);
	CHECK(pDog->pPrev == (TestHotDog *)L4);
	CHECK(pDog->pNext == (TestHotDog *)L2);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L2);
	CHECK(pDog->pPrev == (TestHotDog *)L3);
	CHECK(pDog->pNext == (TestHotDog *)L1);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L1);
	CHECK(pDog->pPrev == (TestHotDog *)L2);
	CHECK(pDog->pNext == nullptr);

	O.Remove(L2);

	pDog = ((TestOrder &)O).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog == (TestHotDog *)L4);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == (TestHotDog *)L3);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L3);
	CHECK(pDog->pPrev == (TestHotDog *)L4);
	CHECK(pDog->pNext == (TestHotDog *)L1);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L1);
	CHECK(pDog->pPrev == (TestHotDog *)L3);
	CHECK(pDog->pNext == nullptr);

	O.Remove(L1);

	pDog = ((TestOrder &)O).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog == (TestHotDog *)L4);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == (TestHotDog *)L3);

	pDog = pDog->pNext;
	CHECK(pDog == (TestHotDog *)L3);
	CHECK(pDog->pPrev == (TestHotDog *)L4);
	CHECK(pDog->pNext == nullptr);

	O.Remove(L4);

	pDog = ((TestOrder &)O).poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog == (TestHotDog *)L3);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == nullptr);

	O.Remove(L3);

	pDog = ((TestOrder &)O).poHead;
	CHECK(pDog == nullptr);


#endif
} TEST_END

//---  End of File ---
