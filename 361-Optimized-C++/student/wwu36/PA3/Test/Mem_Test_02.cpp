//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "_UnitTestConfiguration.h"
#include "Mem.h"
#include "TestMem.h"

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 

TEST(Mem2_Allocate_Everything, TestConfig::Flag::ALL)
{
#if Mem2_Allocate_Everything

	{
		FileIO::Open("Student_", "Test_02");

		fprintf(FileIO::GetHandle(), "Test2: \n\n");
		fprintf(FileIO::GetHandle(), "1) allocate the biggest Type                \n");
		fprintf(FileIO::GetHandle(), "     Mem mem(Mem::Guard::Type_A);   \n");
		fprintf(FileIO::GetHandle(), "     mem.initialize();                       \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(1);                           \n");
		fprintf(FileIO::GetHandle(), "     void *p = mem.malloc( 0xc7d4 );         \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(2);                           \n");

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();
		mem.Print(1);

		void *p;
		p = mem.malloc(0xc7d4);
		mem.Print(2);

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
		void *p = mem.malloc(0xc7d4);

		Heap *h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(h->pFreeHead, nullptr);
		CHECK_EQUAL(h->pNextFit, nullptr);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x20);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 1);
		CHECK_EQUAL(h->currUsedMem, 0xc7d4);

		CHECK_EQUAL(h->currNumFreeBlocks, 0);
		CHECK_EQUAL(h->currFreeMem, 0x0);

		// ---- Heap Walk ------------------------------------------------------

		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;

		// ---- HDR -------------------------------------------

		// Check type
		Used *used = (Used *)(h + 1);
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);
		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		// ---- Type ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(p), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(used->mAllocSize, 0xc7d4);
	}
	{
		// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
		void *p;
		p = mem.malloc(0xc7d4);
		CHECK(true);
	}

#endif
}  TEST_END

// ---  End of File ---
