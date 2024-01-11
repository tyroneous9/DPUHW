//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef MEM_H
#define MEM_H

#include "Heap.h"

class Mem
{
public:
	static const uint32_t TotalSize = (50 * 1024);
	static const uint32_t HeapAlign = 16;
	static const uint32_t HeapAlignMask = HeapAlign - 1;
	static const uint32_t HeaderGuards = 128;

	enum class Guard
	{
		Type_A,
		Type_5,
		Type_None
	};

public:

	Mem( Guard type );	

	Mem() = default;
	Mem(const Mem &) = delete;
	Mem & operator = (const Mem &) = delete;
	~Mem();

	// implement these functions
	void free( void * const data );
	void *malloc( const uint32_t size );
	void initialize( );

	// helper functions
	Heap *GetHeap();
	void Print(int count);

private:
	// Useful in malloc and free
	Heap *poHeap;

	// Below: 
	//    Not used in malloc, free, or initialize
	Guard type;	
	void *poRawMem;
};

#endif 

// --- End of File ---

