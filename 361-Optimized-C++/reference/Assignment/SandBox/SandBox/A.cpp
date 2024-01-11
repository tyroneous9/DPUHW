//----------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------
//----------------------------------------------------------------
// class A  sample
//----------------------------------------------------------------

#include "A.h"

A::A()
	: a0(5)
{
	Trace::out("\tA(default constructor): 1111 \n");
}

A::A(const A& tmp)
	: a0(tmp.a0)
{
	Trace::out("\tA(copy constructor): 1122 \n");
}

A::A(int v0)
	: a0(v0)
{
	Trace::out("\tA(specialized constructor): 1133 \n");
}

A& A::operator = (const A& tmp)
{
	this->a0 = tmp.a0;
	Trace::out("\tA(assignment operator): 1144  \n");
	return *this;
}

A::~A()
{
	Trace::out("\tA(destructor): 1155 \n");
}

A A::operator + (const A& tmp)
{
	A result;
	result.a0 = this->a0 + tmp.a0;
	Trace::out("\tA(addition): 1166 \n");
	return result;
}

// ---- End of File ----
