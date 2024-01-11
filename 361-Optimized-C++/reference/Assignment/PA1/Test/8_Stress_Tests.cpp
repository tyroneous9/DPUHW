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

static Stand *pStand(nullptr);

TEST_WITH_TEARDOWN( ManyOperationsTogether, TestConfig::ALL)
{
#if ManyOperationsTogether

	// ----------------------------------------------------
	// Jamie order
	// ----------------------------------------------------

	HotDog  *pHotdog_A = new HotDog();
	CHECK(pHotdog_A != nullptr);
	pHotdog_A->Add(Condiments::Everything);

	HotDog  *pHotdog_B = new HotDog();
	CHECK(pHotdog_B != nullptr);
	pHotdog_B->Add(Condiments::Yellow_Mustard);
	pHotdog_B->Add(Condiments::Sport_Peppers);

	HotDog  *pHotdog_C = new HotDog();
	CHECK(pHotdog_C != nullptr);
	pHotdog_C->Add(Condiments::Celery_Salt);
	pHotdog_C->Add(Condiments::Tomato_Wedge);
	pHotdog_C->Add(Condiments::Green_Relish);

	Order *pOrder_Jamie = new Order(Name::Jaime);
	CHECK(pOrder_Jamie != nullptr);
	pOrder_Jamie->Add(pHotdog_A);
	pOrder_Jamie->Add(pHotdog_B);
	pOrder_Jamie->Add(pHotdog_C);

	// ----------------------------------------------------
	// Check Jamie order
	// ----------------------------------------------------

	const TestHotDog *pDog = ((TestOrder *)pOrder_Jamie)->poHead;
	CHECK(pDog != nullptr);
	CHECK(pDog != (void *)0xcdcdcdcd);

	CHECK(pDog->condiments == 0x4a);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x30);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x30);
	CHECK(pDog->pPrev->condiments == 0x4a);
	CHECK(pDog->pNext->condiments == 0xfe);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xfe);
	CHECK(pDog->pPrev->condiments == 0x30);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Cersei order
	// ----------------------------------------------------

	HotDog *pHotdog_D = new HotDog();
	CHECK(pHotdog_D != nullptr);
	pHotdog_D->Add(Condiments::Plain);
	pHotdog_D->Add(Condiments::Celery_Salt);
	pHotdog_D->Add(Condiments::Tomato_Wedge);

	HotDog *pHotdog_D1 = new HotDog(*pHotdog_D);
	CHECK(pHotdog_D1 != nullptr);

	HotDog *pHotdog_D2 = new HotDog();
	CHECK(pHotdog_D2 != nullptr);
	*pHotdog_D2 = *pHotdog_D;

	Order *pOrder_Cersei = new Order(Name::Cersei);
	CHECK(pOrder_Cersei != nullptr);
	pOrder_Cersei->Add(pHotdog_D);
	pOrder_Cersei->Add(pHotdog_D1);
	pOrder_Cersei->Add(pHotdog_D2);

	// ----------------------------------------------------
	// Check Cersei order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Cersei)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x48);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x48);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x48);
	CHECK(pDog->pPrev->condiments == 0x48);
	CHECK(pDog->pNext->condiments == 0x48);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x48);
	CHECK(pDog->pPrev->condiments == 0x48);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Arya order
	// ----------------------------------------------------

	HotDog *pHotdog_E = new HotDog();
	CHECK(pHotdog_E != nullptr);
	pHotdog_E->Add(Condiments::Everything);
	pHotdog_E->Minus(Condiments::Sport_Peppers);

	Order *pOrder_Arya = new Order(Name::Arya);
	CHECK(pOrder_Arya != nullptr);
	pOrder_Arya->Add(pHotdog_E);
	
	// ----------------------------------------------------
	// Check Arya order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Arya)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xde);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Sansa order
	// ----------------------------------------------------

	HotDog *pHotdog_F = new HotDog();
	CHECK(pHotdog_F != nullptr);
	pHotdog_F->Add(Condiments::Chopped_Onions);
	pHotdog_F->Add(Condiments::Yellow_Mustard);
	pHotdog_F->Add(Condiments::Green_Relish);

	HotDog *pHotdog_G = new HotDog();
	CHECK(pHotdog_G != nullptr);
	pHotdog_G->Add(Condiments::Everything);
	pHotdog_G->Add(Condiments::Ketchup);
	pHotdog_G->Minus(Condiments::Yellow_Mustard);

	Order *pOrder_Sansa = new Order(Name::Sansa);
	CHECK(pOrder_Sansa != nullptr);
	pOrder_Sansa->Add(pHotdog_F);
	pOrder_Sansa->Add(pHotdog_G);

	// ----------------------------------------------------
	// Check Sansa order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Sansa)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xef);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x92);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x92);
	CHECK(pDog->pPrev->condiments == 0xef);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Samwell order: assignment operator
	// ----------------------------------------------------

	Order *pOrder_Samwell = new Order();
	CHECK(pOrder_Samwell != nullptr);
	*pOrder_Samwell = *pOrder_Arya;
	pOrder_Samwell->SetName(Name::Samwell);

	// ----------------------------------------------------
	// Check Samwell order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Samwell)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xde);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Jon Order: copy constructor
	// ----------------------------------------------------

	Order *pOrder_Jon = new Order(*pOrder_Sansa);
	assert(pOrder_Jon);
	pOrder_Jon->SetName(Name::Jon);

	// ----------------------------------------------------
	// Check Jon order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Jon)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0xef);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0x92);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0x92);
	CHECK(pDog->pPrev->condiments == 0xef);
	CHECK(pDog->pNext == nullptr);

	// ----------------------------------------------------
	// Delete Arya order
	// ----------------------------------------------------

	delete pOrder_Arya;

	// ----------------------------------------------------
	// Delete HotDog B from Jamie's order
	// ----------------------------------------------------

	pOrder_Jamie->Remove(pHotdog_B);

	// ----------------------------------------------------
	// Check Jamie order
	// ----------------------------------------------------

	pDog = ((TestOrder *)pOrder_Jamie)->poHead;
	CHECK(pDog != nullptr);

	CHECK(pDog->condiments == 0x4a);
	CHECK(pDog->pPrev == nullptr);
	CHECK(pDog->pNext->condiments == 0xfe);

	pDog = pDog->pNext;
	CHECK(pDog->condiments == 0xfe);
	CHECK(pDog->pPrev->condiments == 0x4a);
	CHECK(pDog->pNext == nullptr);

// -----------------------------------------------
// Stand - add 5 orders
// -----------------------------------------------

	pStand = new Stand();
	CHECK(pStand != nullptr);

	CHECK(pStand->GetCurrOrders() == 0);
	CHECK(pStand->GetPeakOrders() == 0);
	CHECK(((TestStand *)pStand)->poHead == nullptr);

	pStand->Add(pOrder_Jamie);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 1);
		CHECK(pStand->GetPeakOrders() == 1);
	
		const TestOrder *pOrder = ((TestStand *)pStand)->poHead;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jaime);
		CHECK(pOrder->pPrev == nullptr);
		CHECK(pOrder->pNext == nullptr);

	pStand->Add(pOrder_Cersei);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 2);
		CHECK(pStand->GetPeakOrders() == 2);

		pOrder = ((TestStand *)pStand)->poHead;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jaime);
		CHECK(pOrder->pPrev == nullptr);
		CHECK(pOrder->pNext->name == Name::Cersei);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Cersei);
		CHECK(pOrder->pPrev->name == Name::Jaime);
		CHECK(pOrder->pNext == nullptr);

	pStand->Add(pOrder_Samwell);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 3);
		CHECK(pStand->GetPeakOrders() == 3);

		pOrder = ((TestStand *)pStand)->poHead;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jaime);
		CHECK(pOrder->pPrev == nullptr);
		CHECK(pOrder->pNext->name == Name::Cersei);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Cersei);
		CHECK(pOrder->pPrev->name == Name::Jaime);
		CHECK(pOrder->pNext->name == Name::Samwell);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Samwell);
		CHECK(pOrder->pPrev->name == Name::Cersei);
		CHECK(pOrder->pNext == nullptr);

	pStand->Add(pOrder_Sansa);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 4);
		CHECK(pStand->GetPeakOrders() == 4);

		pOrder = ((TestStand *)pStand)->poHead;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jaime);
		CHECK(pOrder->pPrev == nullptr);
		CHECK(pOrder->pNext->name == Name::Cersei);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Cersei);
		CHECK(pOrder->pPrev->name == Name::Jaime);
		CHECK(pOrder->pNext->name == Name::Samwell);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Samwell);
		CHECK(pOrder->pPrev->name == Name::Cersei);
		CHECK(pOrder->pNext->name == Name::Sansa);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Sansa);
		CHECK(pOrder->pPrev->name == Name::Samwell);
		CHECK(pOrder->pNext == nullptr);

	pStand->Add(pOrder_Jon);

		// -------------------------------------------------------
		// Check stand
		// -------------------------------------------------------

		CHECK(pStand->GetCurrOrders() == 5);
		CHECK(pStand->GetPeakOrders() == 5);

		pOrder = ((TestStand *)pStand)->poHead;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jaime);
		CHECK(pOrder->pPrev == nullptr);
		CHECK(pOrder->pNext->name == Name::Cersei);

		// ----------------------------------------------------
		// Check Jamie order
		// ----------------------------------------------------

		pDog = pOrder->poHead;
		CHECK(pDog != nullptr);

		CHECK(pDog->condiments == 0x4a);
		CHECK(pDog->pPrev == nullptr);
		CHECK(pDog->pNext->condiments == 0xfe);

		pDog = pDog->pNext;
		CHECK(pDog->condiments == 0xfe);
		CHECK(pDog->pPrev->condiments == 0x4a);
		CHECK(pDog->pNext == nullptr);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Cersei);
		CHECK(pOrder->pPrev->name == Name::Jaime);
		CHECK(pOrder->pNext->name == Name::Samwell);

		// ----------------------------------------------------
		// Check Cersei order
		// ----------------------------------------------------

		pDog = pOrder->poHead;
		CHECK(pDog != nullptr);

		CHECK(pDog->condiments == 0x48);
		CHECK(pDog->pPrev == nullptr);
		CHECK(pDog->pNext->condiments == 0x48);

		pDog = pDog->pNext;
		CHECK(pDog->condiments == 0x48);
		CHECK(pDog->pPrev->condiments == 0x48);
		CHECK(pDog->pNext->condiments == 0x48);

		pDog = pDog->pNext;
		CHECK(pDog->condiments == 0x48);
		CHECK(pDog->pPrev->condiments == 0x48);
		CHECK(pDog->pNext == nullptr);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Samwell);
		CHECK(pOrder->pPrev->name == Name::Cersei);
		CHECK(pOrder->pNext->name == Name::Sansa);

		// ----------------------------------------------------
		// Check Samwell order
		// ----------------------------------------------------

		pDog = pOrder->poHead;
		CHECK(pDog != nullptr);

		CHECK(pDog->condiments == 0xdE);
		CHECK(pDog->pPrev == nullptr);
		CHECK(pDog->pNext == nullptr);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Sansa);
		CHECK(pOrder->pPrev->name == Name::Samwell);
		CHECK(pOrder->pNext->name == Name::Jon);

		// ----------------------------------------------------
		// Check Sansa order
		// ----------------------------------------------------

		pDog = pOrder->poHead;
		CHECK(pDog != nullptr);

		CHECK(pDog->condiments == 0xef);
		CHECK(pDog->pPrev == nullptr);
		CHECK(pDog->pNext->condiments == 0x92);

		pDog = pDog->pNext;
		CHECK(pDog->condiments == 0x92);
		CHECK(pDog->pPrev->condiments == 0xef);
		CHECK(pDog->pNext == nullptr);

		pOrder = pOrder->pNext;
		CHECK(pOrder != nullptr);

		CHECK(pOrder->name == Name::Jon);
		CHECK(pOrder->pPrev->name == Name::Sansa);
		CHECK(pOrder->pNext == nullptr);

		// ----------------------------------------------------
		// Check Jon order
		// ----------------------------------------------------

		pDog = pOrder->poHead;
		CHECK(pDog != nullptr);

		CHECK(pDog->condiments == 0xef);
		CHECK(pDog->pPrev == nullptr);
		CHECK(pDog->pNext->condiments == 0x92);

		pDog = pDog->pNext;
		CHECK(pDog->condiments == 0x92);
		CHECK(pDog->pPrev->condiments == 0xef);
		CHECK(pDog->pNext == nullptr);

// -----------------------------------------------
// Stand - remove 4 orders in a specific order
// -----------------------------------------------

		// Remove
		pStand->Remove(Name::Cersei);

			// -------------------------------------------------------
			// Check stand
			// -------------------------------------------------------

			CHECK(pStand->GetCurrOrders() == 4);
			CHECK(pStand->GetPeakOrders() == 5);

			pOrder = ((TestStand *)pStand)->poHead;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Jaime);
			CHECK(pOrder->pPrev == nullptr);
			CHECK(pOrder->pNext->name == Name::Samwell);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Samwell);
			CHECK(pOrder->pPrev->name == Name::Jaime);
			CHECK(pOrder->pNext->name == Name::Sansa);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Sansa);
			CHECK(pOrder->pPrev->name == Name::Samwell);
			CHECK(pOrder->pNext->name == Name::Jon);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Jon);
			CHECK(pOrder->pPrev->name == Name::Sansa);
			CHECK(pOrder->pNext == nullptr);


		// Remove
		pStand->Remove(Name::Samwell);

			// -------------------------------------------------------
			// Check stand
			// -------------------------------------------------------

			CHECK(pStand->GetCurrOrders() == 3);
			CHECK(pStand->GetPeakOrders() == 5);

			pOrder = ((TestStand *)pStand)->poHead;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Jaime);
			CHECK(pOrder->pPrev == nullptr);
			CHECK(pOrder->pNext->name == Name::Sansa);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Sansa);
			CHECK(pOrder->pPrev->name == Name::Jaime);
			CHECK(pOrder->pNext->name == Name::Jon);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Jon);
			CHECK(pOrder->pPrev->name == Name::Sansa);
			CHECK(pOrder->pNext == nullptr);
			
		// Remove
		pStand->Remove(Name::Jaime);

			// -------------------------------------------------------
			// Check stand
			// -------------------------------------------------------

			CHECK(pStand->GetCurrOrders() == 2);
			CHECK(pStand->GetPeakOrders() == 5);

			pOrder = ((TestStand *)pStand)->poHead;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Sansa);
			CHECK(pOrder->pPrev == nullptr);
			CHECK(pOrder->pNext->name == Name::Jon);

			pOrder = pOrder->pNext;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Jon);
			CHECK(pOrder->pPrev->name == Name::Sansa);
			CHECK(pOrder->pNext == nullptr);
			
		// Remove
		pStand->Remove(Name::Jon);
			
			// -------------------------------------------------------
			// Check stand
			// -------------------------------------------------------

			CHECK(pStand->GetCurrOrders() == 1);
			CHECK(pStand->GetPeakOrders() == 5);
		
			pOrder = ((TestStand *)pStand)->poHead;
			CHECK(pOrder != nullptr);

			CHECK(pOrder->name == Name::Sansa);
			CHECK(pOrder->pPrev == nullptr);
			CHECK(pOrder->pNext == nullptr);

		delete pStand;
		pStand = nullptr;

#endif
} TEST_END

TEST_TEARDOWN(ManyOperationsTogether)
{
	delete pStand;
}

//---  End of File ---
