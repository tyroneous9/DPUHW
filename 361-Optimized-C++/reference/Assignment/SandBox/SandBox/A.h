//----------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------

//----------------------------------------------------------------
// class A  sample
//---------------------------------------------------------------- 

#ifndef A_H
#define A_H

class A
{
public:
	// Big four
	A();
	A(const A& tmp);
	A& operator = (const A& tmp);
	~A();

	// specialized constructor
	A(int v0);

	// binary operator
	A operator + (const A& tmp);

// -------------------------
//  Data
// -------------------------
	int a0;

};

#endif // A_H

// ---- End of File ----
