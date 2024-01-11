//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#include "_UnitTestConfiguration.h"
#include "Boustrophedonic.h"
#include "Tree.h"

static Tree *pTree = nullptr;

TEST_WITH_TEARDOWN(Delete01_Test_Enable, TestConfig::ALL)
{
#if Delete01_Test_Enable

	pTree = new Tree();

	DataNode *pN00, *pN01;
	DataNode *pN10, *pN11;


	pTree->GetPointers(pTree->pHead,
					   pN00, pN01,
					   pN10, pN11);
	
	pTree->SkipThisOne = Tree::SkipDelete::N01;

	// Make sure we have a good initial tree

	//-----------------------------------
	CHECK_EQUAL(pN00->pNorth, nullptr);
	CHECK_EQUAL(pN00->pSouth, nullptr);
	CHECK_EQUAL(pN00->pEast, pN01);
	CHECK_EQUAL(pN00->pWest, nullptr);

	CHECK_EQUAL(pN01->pNorth, nullptr);
	CHECK_EQUAL(pN01->pSouth, pN11);
	CHECK_EQUAL(pN01->pEast, nullptr);
	CHECK_EQUAL(pN01->pWest, nullptr);

	//---------------------------------

	CHECK_EQUAL(pN11->pNorth, nullptr);
	CHECK_EQUAL(pN11->pSouth, nullptr);
	CHECK_EQUAL(pN11->pEast, nullptr);
	CHECK_EQUAL(pN11->pWest, pN10);

	CHECK_EQUAL(pN10->pNorth, pN00);
	CHECK_EQUAL(pN10->pSouth, nullptr);
	CHECK_EQUAL(pN10->pEast, nullptr);
	CHECK_EQUAL(pN10->pWest, nullptr);


	//---- TEST below here --------------------

	//Trace::out("remove:---> (0,1) \n");
	Node *p = pTree->pHead;
	Boustropehedic::Remove(p, 0, 1);

	// ------- CHECK HEAD ---------------------

	DataNode *pData = (DataNode *)p;
	CHECK_EQUAL(pData, pTree->pHead);

	//-----------------------------------
	CHECK_EQUAL(pN00->pNorth, nullptr);
	CHECK_EQUAL(pN00->pSouth, nullptr);
	CHECK_EQUAL(pN00->pEast, nullptr);
	CHECK_EQUAL(pN00->pWest, nullptr);

	//---------------------------------

	CHECK_EQUAL(pN11->pNorth, nullptr);
	CHECK_EQUAL(pN11->pSouth, nullptr);
	CHECK_EQUAL(pN11->pEast, nullptr);
	CHECK_EQUAL(pN11->pWest, pN10);

	CHECK_EQUAL(pN10->pNorth, pN00);
	CHECK_EQUAL(pN10->pSouth, nullptr);
	CHECK_EQUAL(pN10->pEast, nullptr);
	CHECK_EQUAL(pN10->pWest, nullptr);

	delete pTree;
	pTree = nullptr;

#endif
}  TEST_END

TEST_TEARDOWN(Delete01_Test_Enable)
{
	delete pTree;
}

// ---  End of File ---------------
