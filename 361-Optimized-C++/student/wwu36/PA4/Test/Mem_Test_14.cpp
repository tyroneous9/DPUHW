//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Mem.h"

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h) 

TEST(Mem14_combo_1, TestConfig::Flag::ALL)
{
#if Mem14_combo_1

	{
		FileIO::Open("Student_", "Test_14");

		fprintf(FileIO::GetHandle(), "Test14: \n\n");

		fprintf(FileIO::GetHandle(), "      Mem mem1(Mem::Guard::Type_A);                           \n");
		fprintf(FileIO::GetHandle(), "      mem1.initialize();                  \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(1);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      void *a1 = mem1.malloc( 0x200 );    \n");
		fprintf(FileIO::GetHandle(), "      void *b1 = mem1.malloc( 0x200 );    \n");
		fprintf(FileIO::GetHandle(), "      void *c1 = mem1.malloc( 0x300 );    \n");
		fprintf(FileIO::GetHandle(), "      void *d1 = mem1.malloc( 0x300 );    \n");
		fprintf(FileIO::GetHandle(), "      void *e1 = mem1.malloc( 0x300 );    \n");
		fprintf(FileIO::GetHandle(), "      void *f1 = mem1.malloc( 0x400 );    \n");
		fprintf(FileIO::GetHandle(), "      void *g1 = mem1.malloc( 0x300 );    \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(2);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      // Part B:                          \n");
		fprintf(FileIO::GetHandle(), "      mem1.free( a1 );                    \n");
		fprintf(FileIO::GetHandle(), "      mem1.free( c1 );                    \n");
		fprintf(FileIO::GetHandle(), "      mem1.free( f1 );                    \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(3);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      // Part C:                          \n");
		fprintf(FileIO::GetHandle(), "      void *r1 = mem1.malloc( 0x180 );    \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(4);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      void *s1 = mem1.malloc(0xb100);     \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(5);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      void *t1 = mem1.malloc(0x220);      \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(6);                        \n");
		fprintf(FileIO::GetHandle(), "                                          \n");
		fprintf(FileIO::GetHandle(), "      mem1.free(s1);                      \n");
		fprintf(FileIO::GetHandle(), "      mem1.Print(7);                        \n");

		// Part A:
		Mem mem1(Mem::Guard::Type_A);
		mem1.initialize();
		mem1.Print(1);

		void *a1 = mem1.malloc(0x200);
		void *b1 = mem1.malloc(0x200);
		void *c1 = mem1.malloc(0x300);
		void *d1 = mem1.malloc(0x300);
		void *e1 = mem1.malloc(0x300);
		void *f1 = mem1.malloc(0x400);
		void *g1 = mem1.malloc(0x300);

		mem1.Print(2);

		// Part B:
		mem1.free(a1);
		mem1.free(c1);
		mem1.free(f1);
		mem1.Print(3);

		// Part C:
		void *r1 = mem1.malloc(0x180);
		mem1.Print(4);

		// Part D:
		void *s1 = mem1.malloc(0xb100);
		mem1.Print(5);

		// Part E:
		void *t1 = mem1.malloc(0x220);
		mem1.Print(6);

		// Part F:
		mem1.free(s1);
		mem1.Print(7);

		// to shut up warnings
		r1 = 0;
		t1 = 0;
		g1 = 0;
		e1 = 0;
		d1 = 0;
		b1 = 0;

		FileIO::Close();
	}

	// ----  GENERAL CHECK ------------------------------------------------------
	{
		// ---- Part A: -------------------------------------------------------------

		Mem mem(Mem::Guard::Type_A);
		mem.initialize();

		void *a = mem.malloc(0x200);
		void *b = mem.malloc(0x200);
		void *c = mem.malloc(0x300);
		void *d = mem.malloc(0x300);
		void *e = mem.malloc(0x300);
		void *f = mem.malloc(0x400);
		void *g = mem.malloc(0x300);

		// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem.GetHeap();

		CHECK_EQUAL(PTR_FIX(a), 0x2c);
		CHECK_EQUAL(PTR_FIX(b), 0x238);
		CHECK_EQUAL(PTR_FIX(c), 0x444);
		CHECK_EQUAL(PTR_FIX(d), 0x750);
		CHECK_EQUAL(PTR_FIX(e), 0xa5c);
		CHECK_EQUAL(PTR_FIX(f), 0xd68);
		CHECK_EQUAL(PTR_FIX(g), 0x1174);


		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x1474);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x1168);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 7);
		CHECK_EQUAL(h->currUsedMem, 0x1400);

		CHECK_EQUAL(h->currNumFreeBlocks, 1);
		CHECK_EQUAL(h->currFreeMem, 0xb380);

		// ----  Type walk ------------------------------------------------------

		uint32_t hdrStart;
		uint32_t hdrEnd;
		uint32_t blkStart;
		uint32_t blkEnd;
		uint32_t secret;

		// ---- USED HDR 1 -------------------------------------------

			// Check type
		Used *used = (Used *)(h + 1);
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x22c);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x20);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- HDR 3 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 4 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x438);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 5 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 6 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(used->mAllocSize, 0x400);

		// ---- HDR 7 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 8 -------------------------------------------

			// Check type
		Free *free = (Free *)blkEnd;
		// Should be USED
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xb380);

		secret = *((uint32_t *)(blkEnd - 4));

		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

		// ---- Part B: -------------------------------------------------------------

		mem.free(a);
		mem.free(c);
		mem.free(f);

		// ---- Verify B: -----------------------------------------------------------

		h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x1168);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 4);
		CHECK_EQUAL(h->currUsedMem, 0xb00);

		CHECK_EQUAL(h->currNumFreeBlocks, 4);
		CHECK_EQUAL(h->currFreeMem, 0xbc80);

		// ---- HDR 1 -------------------------------------------

			// Check type
		free = (Free *)(h + 1);
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x438);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Hdr 3 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(free->mAllocSize, 0x300);

		// ---- HDR 4 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 5 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 6 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x1474);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(free->mAllocSize, 0x400);

		// ---- HDR 7 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 8 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xb380);

		secret = *((uint32_t *)(blkEnd - 4));
		CHECK_EQUAL(PTR_FIX(secret), PTR_FIX(hdrStart));

		CHECK_EQUAL(PTR_FIX(h->pNextFit), PTR_FIX(hdrStart));

		// ---- Part C: -------------------------------------------------------------

		void *r = mem.malloc(0x180);

		// ---- Verify C: -----------------------------------------------------------

		h = mem.GetHeap();

		CHECK_EQUAL(PTR_FIX(r), 0x1480);

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x1474);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 5);
		CHECK_EQUAL(h->currUsedMem, 0xc80);

		CHECK_EQUAL(h->currNumFreeBlocks, 4);
		CHECK_EQUAL(h->currFreeMem, 0xbaf4);

		// ---- HDR 1 -------------------------------------------

			// Check type
		free = (Free *)(h + 1);
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x438);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Hdr 3 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(free->mAllocSize, 0x300);

		// ---- HDR 4 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 5 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 6 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x1600);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(free->mAllocSize, 0x400);

		// ---- HDR 7 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1474);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 8 -------------------------------------------

			// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1168);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1600);
		CHECK_EQUAL(used->mAllocSize, 0x180);

		// ---- Hdr 9 -------------------------------------------

			// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1600);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x160c);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xb1f4);

		// ---- Part D: -------------------------------------------------------------

		void *s = mem.malloc(0xb100);

		// ---- Verify D: -----------------------------------------------------------

		h = mem.GetHeap();

		CHECK_EQUAL(PTR_FIX(s), 0x160c);

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x1600);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 6);
		CHECK_EQUAL(h->currUsedMem, 0xbd80);

		CHECK_EQUAL(h->currNumFreeBlocks, 4);
		CHECK_EQUAL(h->currFreeMem, 0x9e8);

		// ---- HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x438);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- Hdr 3 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(free->mAllocSize, 0x300);

		// ---- HDR 4 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 5 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 6 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xc70c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(free->mAllocSize, 0x400);

		// ---- HDR 7 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1474);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 8 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1600);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1168);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1600);
		CHECK_EQUAL(used->mAllocSize, 0x180);

		// ---- HDR 9 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1600);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x160c);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1474);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc70c);
		CHECK_EQUAL(used->mAllocSize, 0xb100);

		// ---- Hdr 10 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xc70c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xc718);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xe8);

		// ---- Part E: -------------------------------------------------------------

		void *t = mem.malloc(0x220);

		// ---- Verify E: -----------------------------------------------------------

		h = mem.GetHeap();

		CHECK_EQUAL(PTR_FIX(t), 0x444);

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x438);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 7);
		CHECK_EQUAL(h->currUsedMem, 0xbfa0);

		CHECK_EQUAL(h->currNumFreeBlocks, 4);
		CHECK_EQUAL(h->currFreeMem, 0x7bc);

		// ---- HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x664);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1600);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x664);
		CHECK_EQUAL(used->mAllocSize, 0x220);

		// ---- Hdr 4 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x664);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x670);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(free->mAllocSize, 0xd4);

		// ---- HDR 5 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 6 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;
		
		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 7 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x664);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xc70c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(free->mAllocSize, 0x400);

		// ---- HDR 8 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1474);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 9 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1600);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1168);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1600);
		CHECK_EQUAL(used->mAllocSize, 0x180);

		// ---- HDR 10 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1600);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x160c);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1474);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc70c);
		CHECK_EQUAL(used->mAllocSize, 0xb100);

		// ---- Hdr 11 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xc70c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xc718);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xe8);

		// ---- Part F: -------------------------------------------------------------

		mem.free(s);

		// ---- Verify F: -----------------------------------------------------------

		h = mem.GetHeap();

		// Sanit check, make sure everything is heap relative for testing
		CHECK_EQUAL(PTR_FIX(h), 0);

		// Used / free
		CHECK_EQUAL(PTR_FIX(h->pFreeHead), 0x20);
		CHECK_EQUAL(PTR_FIX(h->pUsedHead), 0x438);

		// ---- Heap Stats ------------------------------------------------------

		CHECK_EQUAL(h->currNumUsedBlocks, 6);
		CHECK_EQUAL(h->currUsedMem, 0xea0);

		CHECK_EQUAL(h->currNumFreeBlocks, 4);
		CHECK_EQUAL(h->currFreeMem, 0xb8c8);

		// ---- HDR 1 -------------------------------------------

		// Check type
		free = (Free *)(h + 1);
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x20);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x2c);
		// Prev
		CHECK_EQUAL(free->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x664);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Free));

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x22c);
		CHECK_EQUAL(free->mAllocSize, 0x200);

		// ---- HDR 2 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x22c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x238);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x744);
		// Next
		CHECK_EQUAL(used->pNext, nullptr);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x438);
		CHECK_EQUAL(used->mAllocSize, 0x200);

		// ---- HDR 3 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x438);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x444);
		// Prev
		CHECK_EQUAL(used->pPrev, nullptr);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1474);
		// Hdr Size
		CHECK_EQUAL(hdrEnd - hdrStart, sizeof(Used));

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x664);
		CHECK_EQUAL(used->mAllocSize, 0x220);

		// ---- Hdr 4 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x664);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x670);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x20);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0xd5c);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x744);
		CHECK_EQUAL(free->mAllocSize, 0xd4);

		// ---- HDR 5 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x744);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x750);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0xa50);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x22c);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xa50);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 6 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xa50);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xa5C);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1168);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x744);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xd5c);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- Hdr 7 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0xd5c);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0xd68);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0x664);
		// Next
		CHECK_EQUAL(PTR_FIX(free->pNext), 0x1600);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1168);
		CHECK_EQUAL(free->mAllocSize, 0x400);

		// ---- HDR 8 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, true);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1168);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1174);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x1474);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0xa50);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1474);
		CHECK_EQUAL(used->mAllocSize, 0x300);

		// ---- HDR 9 -------------------------------------------

		// Check type
		used = (Used *)blkEnd;
		// Should be USED
		CHECK_EQUAL(used->mType, Type::USED_Type);

		// Above free
		CHECK_EQUAL(used->bAboveFree, false);

		hdrStart = (uint32_t)used;
		hdrEnd = (uint32_t)used + sizeof(Used);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1474);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x1480);
		// Prev
		CHECK_EQUAL(PTR_FIX(used->pPrev), 0x438);
		// Next
		CHECK_EQUAL(PTR_FIX(used->pNext), 0x1168);

		blkStart = hdrEnd;
		blkEnd = blkStart + used->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0x1600);
		CHECK_EQUAL(used->mAllocSize, 0x180);

		// ---- Hdr 10 -------------------------------------------

		// Check type
		free = (Free *)blkEnd;
		// Should be free
		CHECK_EQUAL(free->mType, Type::FREE_Type);

		// Above free
		CHECK_EQUAL(free->bAboveFree, false);

		hdrStart = (uint32_t)free;
		hdrEnd = (uint32_t)free + sizeof(Free);

		// Hdr Start
		CHECK_EQUAL(PTR_FIX(hdrStart), 0x1600);
		// Hdr End
		CHECK_EQUAL(PTR_FIX(hdrEnd), 0x160c);
		// Prev
		CHECK_EQUAL(PTR_FIX(free->pPrev), 0xd5c);
		// Next
		CHECK_EQUAL(free->pNext, nullptr);

		blkStart = hdrEnd;
		blkEnd = blkStart + free->mAllocSize;

		CHECK_EQUAL(PTR_FIX(blkStart), PTR_FIX(hdrEnd));
		CHECK_EQUAL(PTR_FIX(blkEnd), 0xc800);
		CHECK_EQUAL(free->mAllocSize, 0xb1f4);
	}

	{
	// ----  Checking Guards ----

		Mem mem(Mem::Guard::Type_5);
		CHECK(true);
		mem.initialize();
		CHECK(true);
		void *a;
		a = mem.malloc(0x200);
		CHECK(true);
		void *b;
		b = mem.malloc(0x200);
		CHECK(true);
		void *c;
		c = mem.malloc(0x300);
		CHECK(true);
		void *d;
		d = mem.malloc(0x300);
		CHECK(true);
		void *e;
		e = mem.malloc(0x300);
		CHECK(true);
		void *f;
		f = mem.malloc(0x400);
		CHECK(true);
		void *g;
		g= mem.malloc(0x300);
		CHECK(true);
		mem.free(a);
		CHECK(true);
		mem.free(c);
		CHECK(true);
		mem.free(f);
		CHECK(true);
		void *r;
		r = mem.malloc(0x180);
		CHECK(true);
		void *s;
		s = mem.malloc(0xb100);
		CHECK(true);
		void *t;
		t= mem.malloc(0x220);
		CHECK(true);
		mem.free(s);
		CHECK(true);

	}

#endif
}  TEST_END

// ---  End of File ---
