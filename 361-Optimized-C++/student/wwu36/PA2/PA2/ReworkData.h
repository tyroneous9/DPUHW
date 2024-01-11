//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef REWORK_DATA_H
#define REWORK_DATA_H

struct DataA
{
	double r;
	int pad0;
	char a;
	char b;
	char pad1;
	char pad2;
	//8+4+1*4=16
};

struct DataB
{
	DataA da;
	int i;
	char a;
	char b;
	char pad0;
	char pad1;
	//16(8)+4+1*4=24
};

struct DataC
{
	int j;
	int i;
	bool f;
	char a;
	char pad0;
	char pad1;
	//4+4+1*4=12
};

struct DataD
{
	double r;
	int i;
	char a;
	char b;
	char pad0;
	char pad1;
	//8+4+1*4
};

struct DataE
{
	double r; 
	int* p;
	int x;
	char name[12];
	char a;
	char c;
	char pad0;
	char pad1;
	//8+4+4+12+1*4
};

struct Vect
{
	float vx;
	float vy;
	float vz;
	float vw;
	char a;
	char b;
	char pad0;
	char pad1;
	//4*4+1*4=20
};

struct DataF
{
	Vect v; 
	int i;
	int j;
	char c;
	char b;
	char pad0;
	char pad1;
	//20(4)+4+4+1*4
};

struct DataG
{
	DataA a0;
	double d1;
	double d0;
	Vect  v;
	char  b0;
	char  c0;
	char pad0;
	char pad1;
	//16(8)+8+8+20(4)+1*4=56
};


#endif

// ---  End of File ---

