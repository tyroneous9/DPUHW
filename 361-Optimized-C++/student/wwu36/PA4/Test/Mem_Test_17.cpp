//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Mem.h"

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

unsigned int s(0);
#define PTR_FIX( x )  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 

TEST(Mem17_Exact_Alloc_Sets_Below_Flag, TestConfig::Flag::ALL)
{
#if Mem17_Exact_Alloc_Sets_Below_Flag

	{
		// ------------
		// File Print
		// ------------
		FileIO::Open("Student_", "Test_17");

		Mem memToFile(Mem::Guard::Type_A);
		memToFile.initialize();
		memToFile.Print(1);

		void *pA1 = memToFile.malloc(0x4290);
		void *pB1 = memToFile.malloc(0x429c);
		void *pC1 = memToFile.malloc(0x4290);

		memToFile.Print(2);  // --- A ---

		memToFile.free(pB1);
		memToFile.Print(3);  // --- B ---

		void *pD1 = memToFile.malloc(0x429c);
		memToFile.Print(4);  // --- C ---

		memToFile.free(pD1);
		memToFile.Print(4);

		memToFile.free(pA1);
		memToFile.Print(5);

		memToFile.free(pC1);
		memToFile.Print(6);

		FileIO::Close();
	}
	// ----  GENERAL CHECK ------------------------------------------------------

	{
		// ---- Part A: -------------------------------------------------------------

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();

		void *pA = mem.malloc(0x4290);
		void *pB = mem.malloc(0x429c);
		void *pC = mem.malloc(0x4290);

		// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(h->pFreeHead, nullptr);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x8564);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 3);
		CHECK_EQUAL(h->currUsedMem, 0x4290 + 0x429c + 0x4290);

		CHECK_EQUAL(h->currNumFreeBlocks, 0);
		CHECK_EQUAL(h->currFreeMem, 0x0);


		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;
		//uint32_t secret;

		s = PTR_FIX(h->pUsedHead);
		AZUL_UNUSED_VAR(pA);
		AZUL_UNUSED_VAR(pB);
		AZUL_UNUSED_VAR(pC);

		// ---- USED HDR 1 -------------------------------------------

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
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x42bc);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pA), PTR_FIX(hdrEnd));

		CHECK_EQUAL(PTR_FIX(blkEnd), 0x42bc);
		CHECK_EQUAL(used->mAllocSize, 0x4290);

		// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x42bc);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x42c8);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x8564);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x20);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pB), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x8564);
		CHECK_EQUAL(used->mAllocSize, 0x429C);

		// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x8564);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x8570);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x42bc);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pC), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(used->mAllocSize, 0x4290);

		// ---- Part B: -------------------------------------------------------------

		mem.free(pB);

		// ---- Verify B: -----------------------------------------------------------

		// Used / free
		s = PTR_FIX(h->pFreeHead);
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x42bc);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x8564);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 2);
		CHECK_EQUAL(h->currUsedMem, 0x4290 + 0x4290);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0x429c);


		// ----  Type walk ------------------------------------------------------


		s = PTR_FIX(h->pUsedHead);
		AZUL_UNUSED_VAR(pA);
		AZUL_UNUSED_VAR(pB);
		AZUL_UNUSED_VAR(pC);

		// ---- USED HDR 1 -------------------------------------------

		// Check type
		used = (Used *)(h + 1);

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
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x8564);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pA), PTR_FIX(hdrEnd));

		CHECK_EQUAL(PTR_FIX(blkEnd), 0x42bc);
		CHECK_EQUAL(used->mAllocSize, 0x4290);

		// ---- free HDR 2 -------------------------------------------

		used = (Used *)0x1;
		// Check type
		Free *free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x42bc);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x42c8);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pB), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x8564);
		CHECK_EQUAL(free->mAllocSize, 0x429c);

		// ---- Used HDR 3 -------------------------------------------

		free = (Free *)0x1;
		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		s = PTR_FIX(hdrStart);
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x8564);
		// Hdr End
		s = PTR_FIX(hdrEnd);
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x8570);
		// Prev
		s = PTR_FIX(used->pPrev);
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		s = PTR_FIX(used->pNext);
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x20);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pC), PTR_FIX(hdrEnd));
		s = PTR_FIX(blkEnd);
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(used->mAllocSize, 0x4290);






		// ---- Part C: -------------------------------------------------------------

		void *pD = mem.malloc(0x429c);


		// ---- Verify C: -----------------------------------------------------------

		// Used / free
		CHECK_EQUAL(h->pFreeHead, nullptr);

		s = PTR_FIX(h->pUsedHead);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x42bc);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 3);
		CHECK_EQUAL(h->currUsedMem, 0x4290 + 0x429c + 0x4290);

		CHECK_EQUAL(h->currNumFreeBlocks, 0);
		CHECK_EQUAL(h->currFreeMem, 0x0);


		// ----  Type walk ------------------------------------------------------

		// ---- USED HDR 1 -------------------------------------------

		free = (Free *)0x1;
		// Check type
		used = (Used *)(h + 1);

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
		s = PTR_FIX(used->pPrev);
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x8564);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pA), PTR_FIX(hdrEnd));

		CHECK_EQUAL(PTR_FIX(blkEnd), 0x42bc);
		CHECK_EQUAL(used->mAllocSize, 0x4290);

		// ---- Used HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x42bc);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x42c8);
		// Prev
		s = PTR_FIX(used->pPrev);
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		s = PTR_FIX(used->pNext);
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x8564);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pD), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x8564);
		CHECK_EQUAL(used->mAllocSize, 0x429c);

		// ---- Used HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x8564);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x8570);
		// Prev
		s = PTR_FIX(used->pPrev);
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x42bc);
		// Next
		s = PTR_FIX(used->pNext);
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x20);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(pC), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(used->mAllocSize, 0x4290);
	}

	{

	// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
		void *pA = mem.malloc(0x4290);
		CHECK(true);
		void *pB = mem.malloc(0x429c);
		CHECK(true);
		void *pC = mem.malloc(0x4290);
		CHECK(true);
		mem.free(pB);
		CHECK(true);
		void *pD = mem.malloc(0x429c);
		CHECK(true);
		mem.free(pD);
		CHECK(true);
		mem.free(pA);
		CHECK(true);
		mem.free(pC);
		CHECK(true);
	}

#endif
} TEST_END

// ---  End of File ---
