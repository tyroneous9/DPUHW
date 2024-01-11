//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef M_H
#define M_H

class M
{
public:
	M()
	: a(11)
	{
		// Label:  0xF001
	}

	int weight()
	{
		// Label:  0xF002
		return this->a;
	}

	virtual int maximum()
	{
		// Label:  0xF003
		return this->a;
	}

	void foo()
	{
		// Label:  0xF004
		this->a += 10;
	}

	virtual ~M()
	{
		// Label:  0xF005
	}

protected:
	int a;
};


class N : public M
{
public:
	N()
	: b(22)
	{
		// Label:  0xF006
	}

	void foo()
	{
		// Label:  0xF007
		a += 3;
	}

	virtual int weight()
	{
		// Label:  0xF008
		return this->a + this->b;
	}

	virtual int maximum()
	{
		// Label:  0xF009
		int max = this->a;

		if ( this->a > this->b)
		{
			max = this->a;
		}
		else
		{
			max = this->b;
		}
		return max;
	}


	~N()
	{
		// Label:  0xF00A
	}

protected:
	int b;


};

class O : public N
{
public:
	O()
	: c(33)
	{
		// Label:  0xF00B
	}

	void foo()
	{
		// Label:  0xF00C
		a += 3;
	}

	int weight()
	{
		// Label:  0xF00D
		return this->a + this->b + this->c;
	}


	~O()
	{
		// Label:  0xF00E
	}

private:
	int c;

};

#endif

// ---  End of File ---------------
