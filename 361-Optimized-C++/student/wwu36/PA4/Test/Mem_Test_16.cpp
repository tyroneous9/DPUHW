//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "_UnitTestConfiguration.h"
#include "Mem.h"

//--------------------------------
//    DO NOT MODIFY this File
//--------------------------------

#define PTR_FIX(x)  (unsigned int)(x == 0) ? 0: ((unsigned int)x - (unsigned int)h)  

TEST(Mem16_Secret_pointers, TestConfig::Flag::ALL)
{
#if Mem16_Secret_pointers

	{
		FileIO::Open("Student_", "Test_16");

		fprintf(FileIO::GetHandle(), "Test16: \n\n");

		// Part A:
		fprintf(FileIO::GetHandle(), "      Mem mem;\n");
		fprintf(FileIO::GetHandle(), "      mem.initialize();\n");
		fprintf(FileIO::GetHandle(), "      mem.Print(1);\n\n");

		fprintf(FileIO::GetHandle(), "      void *a1 = mem.malloc(0x100);\n");
		fprintf(FileIO::GetHandle(), "      void *a2 = mem.malloc(0x20);\n");
		fprintf(FileIO::GetHandle(), "      void *a3 = mem.malloc(0x20);\n");
		fprintf(FileIO::GetHandle(), "      void *a4 = mem.malloc(0x20);\n");
		fprintf(FileIO::GetHandle(), "      void *a5 = mem.malloc(0x20);\n");
		fprintf(FileIO::GetHandle(), "      void *b1 = mem.malloc(0x200);\n");
		fprintf(FileIO::GetHandle(), "      void *c1 = mem.malloc(0x300);\n");
		fprintf(FileIO::GetHandle(), "      void *c2 = mem.malloc(0x30);\n");
		fprintf(FileIO::GetHandle(), "      void *c3 = mem.malloc(0x30);\n");

		fprintf(FileIO::GetHandle(), "      void *c4 = mem.malloc(0x30);\n");
		fprintf(FileIO::GetHandle(), "      void *c5 = mem.malloc(0x30);\n");
		fprintf(FileIO::GetHandle(), "      void *c6 = mem.malloc(0x30);\n");
		fprintf(FileIO::GetHandle(), "      void *c7 = mem.malloc(0x30);\n");
		fprintf(FileIO::GetHandle(), "      void *d1 = mem.malloc(0x200);\n");

		fprintf(FileIO::GetHandle(), "      void *d2 = mem.malloc(0x40);\n");
		fprintf(FileIO::GetHandle(), "      void *d3 = mem.malloc(0x60);\n");
		fprintf(FileIO::GetHandle(), "      void *e1 = mem.malloc(0x100);\n");
		fprintf(FileIO::GetHandle(), "      void *f1 = mem.malloc(0x500);\n");
		fprintf(FileIO::GetHandle(), "      void *g1 = mem.malloc(0x100);\n\n");

		fprintf(FileIO::GetHandle(), "      mem.Print(2);\n\n");

		fprintf(FileIO::GetHandle(), "      mem.free(d1);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(b1);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(f1);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(a1);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(a4);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(c7);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(c5);\n");
		fprintf(FileIO::GetHandle(), "      mem.free(c2);\n\n");

		fprintf(FileIO::GetHandle(), "      mem.Print(3);\n\n");

		fprintf(FileIO::GetHandle(), "      mem1.free(d2);\n");
		fprintf(FileIO::GetHandle(), "      mem1.free(c4);\n");
		fprintf(FileIO::GetHandle(), "      mem1.free(g1);\n\n");

		fprintf(FileIO::GetHandle(), "      mem1.Print(4);\n\n");

		//---------------------------------------------------------
		// Part A:
		//---------------------------------------------------------
		Mem mem1(Mem::Guard::Type_A);
		mem1.initialize();
		mem1.Print(1);

		void *a1 = mem1.malloc(0x100);
		void *a2 = mem1.malloc(0x20);
		void *a3 = mem1.malloc(0x20);
		void *a4 = mem1.malloc(0x20);
		void *a5 = mem1.malloc(0x20);
		void *b1 = mem1.malloc(0x200);
		void *c1 = mem1.malloc(0x300);
		void *c2 = mem1.malloc(0x30);
		void *c3 = mem1.malloc(0x30);

		void *c4 = mem1.malloc(0x30);
		void *c5 = mem1.malloc(0x30);
		void *c6 = mem1.malloc(0x30);
		void *c7 = mem1.malloc(0x30);
		void *d1 = mem1.malloc(0x200);

		void *d2 = mem1.malloc(0x40);
		void *d3 = mem1.malloc(0x60);
		void *e1 = mem1.malloc(0x100);
		void *f1 = mem1.malloc(0x500);
		void *g1 = mem1.malloc(0x100);

		AZUL_UNUSED_VAR(c1);
		AZUL_UNUSED_VAR(e1);
		AZUL_UNUSED_VAR(g1);
		AZUL_UNUSED_VAR(a1);
		AZUL_UNUSED_VAR(a2);
		AZUL_UNUSED_VAR(a3);
		AZUL_UNUSED_VAR(a5);
		AZUL_UNUSED_VAR(c3);
		AZUL_UNUSED_VAR(c6);
		AZUL_UNUSED_VAR(c4);
		AZUL_UNUSED_VAR(d2);
		AZUL_UNUSED_VAR(d3);

		// ---- Verify A: -----------------------------------------------------------

		Heap *h = mem1.GetHeap();

		CHECK_EQUAL(PTR_FIX(a1), 0x2c);
		CHECK_EQUAL(PTR_FIX(a2), 0x138);
		CHECK_EQUAL(PTR_FIX(a3), 0x164);
		CHECK_EQUAL(PTR_FIX(a4), 0x190);
		CHECK_EQUAL(PTR_FIX(a5), 0x1bc);
		CHECK_EQUAL(PTR_FIX(b1), 0x1e8);
		CHECK_EQUAL(PTR_FIX(c1), 0x3f4);
		CHECK_EQUAL(PTR_FIX(c2), 0x700);
		CHECK_EQUAL(PTR_FIX(c3), 0x73c);
		CHECK_EQUAL(PTR_FIX(c4), 0x778);
		CHECK_EQUAL(PTR_FIX(c5), 0x7b4);
		CHECK_EQUAL(PTR_FIX(c6), 0x7f0);
		CHECK_EQUAL(PTR_FIX(c7), 0x82c);
		CHECK_EQUAL(PTR_FIX(d1), 0x868);
		CHECK_EQUAL(PTR_FIX(d2), 0xa74);
		CHECK_EQUAL(PTR_FIX(d3), 0xac0);
		CHECK_EQUAL(PTR_FIX(e1), 0xb2c);
		CHECK_EQUAL(PTR_FIX(f1), 0xc38);
		CHECK_EQUAL(PTR_FIX(g1), 0x1144);

		mem1.Print(2);

		//---------------------------------------------------------
		// Part B:
		//---------------------------------------------------------

		mem1.free(d1);
		mem1.free(b1);
		mem1.free(f1);
		mem1.free(a1);
		mem1.free(a4);
		mem1.free(c7);
		mem1.free(c5);
		mem1.free(c2);

		Used *used;
		uint32_t *secret;
		Free *free;

		// Check Secret Pointers, given pointer
		used = (Used *)a2 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x12c);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x20);

		// Check Secret Pointers, given pointer
		used = (Used *)a5 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x1b0);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x184);

		// Check Secret Pointers, given pointer
		used = (Used *)c1 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x3e8);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x1dc);

		// Check Secret Pointers, given pointer
		used = (Used *)c3 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x730);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x6f4);

		// Check Secret Pointers, given pointer
		used = (Used *)c6 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x7e4);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x7a8);

		// Check Secret Pointers, given pointer
		used = (Used *)d2 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0xa68);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x820);

		// Check Secret Pointers, given pointer
		used = (Used *)g1 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x1138);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0xc2c);

		mem1.Print(3);

		//---------------------------------------------------------
		// Part C:
		//---------------------------------------------------------
		//
		//  READ the next 3 Frees... here is the real test
		//  If it doesn't pass inspection - you lose points 
		//
		//---------------------------------------------------------

		// This should not use Do,For,While loop on the free list
		// I will walk into you function and verify - Keenan
		mem1.free(d2);

		// This should not use Do,For,While loop on the free list
		// I will walk into you function and verify - Keenan
		mem1.free(c4);

		// This should not use Do,For,While loop on the free list
		// I will walk into you function and verify - Keenan
		mem1.free(g1);

		// Check Secret Pointers, given pointer
		used = (Used *)a2 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x12c);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x20);

		// Check Secret Pointers, given pointer
		used = (Used *)a5 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x1b0);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x184);

		// Check Secret Pointers, given pointer
		used = (Used *)c1 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x3e8);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x1dc);

		// Check Secret Pointers, given pointer
		used = (Used *)c3 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x730);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x6f4);

		// Check Secret Pointers, given pointer
		used = (Used *)c6 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0x7e4);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x76c);

		// Check for Secret Pointers, given pointer
		used = (Used *)d3 - 1;
		CHECK_EQUAL((PTR_FIX(used)), 0xab4);
		CHECK_EQUAL(used->bAboveFree, true);
		secret = (uint32_t *)((uint32_t)used - 4);
		free = (Free *)*secret;
		CHECK_EQUAL((PTR_FIX(free)), 0x820);

		mem1.Print(4);
		FileIO::Close();
	}

	{

		// ----  Checking Guards ----

		Mem mem1(Mem::Guard::Type_5);
		CHECK(true);
		mem1.initialize();
		CHECK(true);
		void *a1 = mem1.malloc(0x100);
		CHECK(true);
		void *a2 = mem1.malloc(0x20);
		CHECK(true);
		void *a3 = mem1.malloc(0x20);
		CHECK(true);
		void *a4 = mem1.malloc(0x20);
		CHECK(true);
		void *a5 = mem1.malloc(0x20);
		CHECK(true);
		void *b1 = mem1.malloc(0x200);
		CHECK(true);
		void *c1 = mem1.malloc(0x300);
		CHECK(true);
		void *c2 = mem1.malloc(0x30);
		CHECK(true);
		void *c3 = mem1.malloc(0x30);
		CHECK(true);

		void *c4 = mem1.malloc(0x30);
		CHECK(true);
		void *c5 = mem1.malloc(0x30);
		CHECK(true);
		void *c6 = mem1.malloc(0x30);
		CHECK(true);
		void *c7 = mem1.malloc(0x30);
		CHECK(true);
		void *d1 = mem1.malloc(0x200);
		CHECK(true);
		void *d2 = mem1.malloc(0x40);
		CHECK(true);
		void *d3 = mem1.malloc(0x60);
		CHECK(true);
		void *e1 = mem1.malloc(0x100);
		CHECK(true);
		void *f1 = mem1.malloc(0x500);
		CHECK(true);
		void *g1 = mem1.malloc(0x100);
		CHECK(true);

		AZUL_UNUSED_VAR(c1);
		AZUL_UNUSED_VAR(e1);
		AZUL_UNUSED_VAR(g1);
		AZUL_UNUSED_VAR(a1);
		AZUL_UNUSED_VAR(a2);
		AZUL_UNUSED_VAR(a3);
		AZUL_UNUSED_VAR(a5);
		AZUL_UNUSED_VAR(c3);
		AZUL_UNUSED_VAR(c6);
		AZUL_UNUSED_VAR(c4);
		AZUL_UNUSED_VAR(d2);
		AZUL_UNUSED_VAR(d3);
		CHECK(true);
		mem1.free(d1);
		CHECK(true);
		mem1.free(b1);
		CHECK(true);
		mem1.free(f1);
		CHECK(true);
		mem1.free(a1);
		CHECK(true);
		mem1.free(a4);
		CHECK(true);
		mem1.free(c7);
		CHECK(true);
		mem1.free(c5);
		CHECK(true);
		mem1.free(c2);
		CHECK(true);

		mem1.free(d2);
		CHECK(true);
		mem1.free(c4);
		CHECK(true);
		mem1.free(g1);
		CHECK(true);

	}

#endif
}  TEST_END

// ---  End of File ---
