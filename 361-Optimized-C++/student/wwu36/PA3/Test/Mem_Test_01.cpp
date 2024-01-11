//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "Mem.h"
#include "TestMem.h"

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0 : ((unsigned int)x - (unsigned int)h) 


TEST(Mem1_Initialize, TestConfig::Flag::ALL)
{
#if Mem1_Initialize

	{
		FileIO::Open("Student_", "Test_01");

		fprintf(FileIO::GetHandle(), "Test 1: \n\n");
		fprintf(FileIO::GetHandle(), "     Mem mem(Mem::Guard::Type_A);  \n");
		fprintf(FileIO::GetHandle(), "     mem.initialize();                      \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(1);                          \n");

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();
		mem.Print(1);

		FileIO::Close();
	}

	{

		// ----  Data layout ------------------------------------------
		{
			Free tmp;
			CHECK(sizeof(tmp) == 12);
			CHECK(((unsigned int)&tmp.pNext - (unsigned int)&tmp) == 0);
			CHECK(((unsigned int)&tmp.pPrev - (unsigned int)&tmp) == 4);
			CHECK(((unsigned int)&tmp.mAllocSize - (unsigned int)&tmp) == 8);
			CHECK(((unsigned int)&tmp.mType - (unsigned int)&tmp) == 10);
			CHECK(((unsigned int)&tmp.bAboveFree - (unsigned int)&tmp) == 11);
		}
		{
			Used tmp;
			CHECK(sizeof(tmp) == 12);
			CHECK(((unsigned int)&tmp.pNext - (unsigned int)&tmp) == 0);
			CHECK(((unsigned int)&tmp.pPrev - (unsigned int)&tmp) == 4);
			CHECK(((unsigned int)&tmp.mAllocSize - (unsigned int)&tmp) == 8);
			CHECK(((unsigned int)&tmp.mType - (unsigned int)&tmp) == 10);
			CHECK(((unsigned int)&tmp.bAboveFree - (unsigned int)&tmp) == 11);
		}
		{
			Heap tmp;
			CHECK(sizeof(tmp) == 32);
			CHECK(((unsigned int)&tmp.pUsedHead - (unsigned int)&tmp) == 0);
			CHECK(((unsigned int)&tmp.pFreeHead - (unsigned int)&tmp) == 4);
			CHECK(((unsigned int)&tmp.pNextFit - (unsigned int)&tmp) == 8);
			CHECK(((unsigned int)&tmp.currNumUsedBlocks - (unsigned int)&tmp) == 12);
			CHECK(((unsigned int)&tmp.currUsedMem - (unsigned int)&tmp) == 16);
			CHECK(((unsigned int)&tmp.currNumFreeBlocks - (unsigned int)&tmp) == 20);
			CHECK(((unsigned int)&tmp.currFreeMem - (unsigned int)&tmp) == 24);
			CHECK(((unsigned int)&tmp.pad - (unsigned int)&tmp) == 28);
		}
		{
			Mem tmp;
			TestMem *p = (TestMem *)&tmp;
			p->type = Mem::Guard::Type_None;
			p->poRawMem = nullptr;
			CHECK(sizeof(tmp) == 12);
			CHECK(((unsigned int)&p->poHeap - (unsigned int)p) == 0);
			CHECK(((unsigned int)&p->type - (unsigned int)p) == 4);
			CHECK(((unsigned int)&p->poRawMem - (unsigned int)p) == 8);
		}

		// ----  GENERAL CHECK ------------------------------------------------------
		Mem mem(Mem::Guard::Type_A);
		mem.initialize();
		Heap *h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(h->pUsedHead, nullptr);
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pNextFit), 0x20);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 0);
		CHECK_EQUAL(h->currUsedMem, 0);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0xc7d4);

		// ---- Heap Walk ------------------------------------------------------

		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;

		// ---- HDR -------------------------------------------

		// Check type
		Free *free = (Free *)(h + 1);
		// Should be FREE
		CHECK_EQUAL(free->mType, Type::FREE_Type);
		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2C);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		// ---- Type ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc7d4);
	}

	{
		// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
	}

#endif
} TEST_END


// ---  End of File ---
