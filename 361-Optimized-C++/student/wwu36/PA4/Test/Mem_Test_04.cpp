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

TEST(Mem4_Partial_allocate, TestConfig::Flag::ALL)
{
#if Mem4_Partial_allocate

	{
		FileIO::Open("Student_", "Test_04");

		fprintf(FileIO::GetHandle(), "Test4: \n\n");

		fprintf(FileIO::GetHandle(), " 1) allocate regular size Type            \n");
		fprintf(FileIO::GetHandle(), "     Mem mem(Mem::Guard::Type_A); \n");
		fprintf(FileIO::GetHandle(), "     mem.initialize();                     \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(1);                         \n");
		fprintf(FileIO::GetHandle(), "     void *p = mem.malloc( 200 );          \n");
		fprintf(FileIO::GetHandle(), "     mem.Print(2);                         \n");

		Mem mem1(Mem::Guard::Type_A);
		mem1.initialize();
		mem1.Print(1);

		void *p1 = mem1.malloc(0x200);
		mem1.Print(2);

		// Shut up warnings
		AZUL_UNUSED_VAR(p1);

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

		// ---- Part A: -------------------------------------------------------------

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();
		void *p = mem.malloc(0x200);

		// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x22c);
		CHECK_EQUAL(PTR_FIX(h->pNextFit), 0x22c);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x20);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 1);
		CHECK_EQUAL(h->currUsedMem, 0x200);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0xc5c8);

		// ---- Heap Walk ------------------------------------------------------

		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;

		// ---- USED HDR -------------------------------------------

		// Check type
		Used *used = (Used *)(h + 1);
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);
		// Above free?
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

		// ---- USED Type ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(PTR_FIX(p), PTR_FIX(hdrEnd));
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- FREE HDR -------------------------------------------

		// Check type
		Free *free = (Free *)blkEnd;
		// Should be USED
		CHECK_EQUAL(free->mType, Type::FREE_Type);
		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		// ---- FREE Type ----------------------------------------------------

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xc5c8);
	}
	{
		// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
		void *p;
		p = mem.malloc(0x200);
		CHECK(true);

	}

#endif
}  TEST_END


// ---  End of File ---
