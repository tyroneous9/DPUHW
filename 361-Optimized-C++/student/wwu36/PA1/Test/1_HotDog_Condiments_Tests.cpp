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

TEST(Condiments_HotDog, TestConfig::ALL)
{
#if Condiments_HotDog	

	// ----  Data layout ------------------------------------------
	{
		HotDog tmp;
		CHECK(sizeof(tmp) == 16);
	}

	{
		Order tmp;
		CHECK(sizeof(tmp) == 20);
	}

	{
		Stand tmp;
		CHECK(sizeof(tmp) == 16);
	}

	// -----------------------------------------------
	// Jaime order:
	// -----------------------------------------------
	HotDog  hotdog_A;

	hotdog_A.Add(Condiments::Everything);
	CHECK(((TestHotDog &)hotdog_A).condiments == 0xFE);

	HotDog  hotdog_B;
	hotdog_B.Add(Condiments::Yellow_Mustard);
	hotdog_B.Add(Condiments::Sport_Peppers);
	CHECK(((TestHotDog &)hotdog_B).condiments == 0x30);

	HotDog  hotdog_C;
	hotdog_C.Add(Condiments::Celery_Salt);
	hotdog_C.Add(Condiments::Tomato_Wedge);
	hotdog_C.Add(Condiments::Green_Relish);
	hotdog_C.Add(Condiments::Celery_Salt);
	CHECK(((TestHotDog &)hotdog_C).condiments == 0x4a);

	// -----------------------------------------------
	// Cersei order:
	// -----------------------------------------------
	HotDog hotdog_D;
	hotdog_D.Add(Condiments::Plain);
	CHECK(((TestHotDog &)hotdog_D).condiments == 0x0);

	// -----------------------------------------------
	// Sansa order:
	// -----------------------------------------------
	HotDog hotdog_F;
	hotdog_F.Add(Condiments::Chopped_Onions);
	hotdog_F.Minus(Condiments::Green_Relish);
	hotdog_F.Add(Condiments::Yellow_Mustard);
	hotdog_F.Minus(Condiments::Green_Relish);
	hotdog_F.Add(Condiments::Ketchup);
	hotdog_F.Minus(Condiments::Green_Relish);
	hotdog_F.Minus(Condiments::Green_Relish);
	CHECK(((TestHotDog &)hotdog_F).condiments == 0x91);

	HotDog hotdog_G;
	hotdog_G.Add(Condiments::Ketchup);
	hotdog_G.Add(Condiments::Everything);
	hotdog_G.Add(Condiments::Ketchup);
	hotdog_G.Minus(Condiments::Yellow_Mustard);
	CHECK(((TestHotDog &)hotdog_G).condiments == 0xef);

	// -----------------------------------------------
	// Arya order:
	// -----------------------------------------------
	HotDog hotdog_E;
	hotdog_E.Add(Condiments::Everything);
	hotdog_E.Minus(Condiments::Green_Relish);
	hotdog_E.Minus(Condiments::Sport_Peppers);
	hotdog_E.Add(Condiments::Everything);
	hotdog_E.Add(Condiments::Ketchup);
	hotdog_E.Minus(Condiments::Sport_Peppers);
	CHECK(((TestHotDog &)hotdog_E).condiments == 0xdf);

	// -----------------------------------------------
	// Samwell order:
	// -----------------------------------------------
	HotDog hotdog_H;
	hotdog_H.Add(Condiments::Chopped_Onions);
	hotdog_H.Add(Condiments::Yellow_Mustard);
	hotdog_H.Add(Condiments::Celery_Salt);
	hotdog_H.Minus(Condiments::Celery_Salt);
	hotdog_H.Add(Condiments::Ketchup);
	hotdog_H.Minus(Condiments::Celery_Salt);
	CHECK(((TestHotDog &)hotdog_H).condiments == 0x91);

	HotDog hotdog_I;
	hotdog_I.Add(Condiments::Pickle_Spear);
	hotdog_I.Add(Condiments::Yellow_Mustard);
	hotdog_I.Add(Condiments::Pickle_Spear);
	CHECK(((TestHotDog &)hotdog_I).condiments == 0x14);

	// -----------------------------------------------
	// Tyrion order:
	// -----------------------------------------------
	HotDog hotdog_J;
	hotdog_J.Add(Condiments::Yellow_Mustard);
	hotdog_J.Add(Condiments::Green_Relish);
	hotdog_J.Add(Condiments::Yellow_Mustard);
	hotdog_J.Add(Condiments::Sport_Peppers);
	hotdog_J.Add(Condiments::Yellow_Mustard);
	hotdog_J.Add(Condiments::Chopped_Onions);
	CHECK(((TestHotDog &)hotdog_J).condiments == 0xB2);

#endif
} TEST_END

//---  End of File ---
