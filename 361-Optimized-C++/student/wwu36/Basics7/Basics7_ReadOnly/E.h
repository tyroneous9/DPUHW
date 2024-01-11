//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef E_H
#define E_H

class E
{
public:
	E()
	: a(11)
	{
		// Label:  0xe001
	}

	virtual int weight()
	{
		// Label:  0xe002
		return this->a;
	}

	virtual int maximum()
	{
		// Label:  0xe003
		return this->a;
	}

	void foo()
	{
		// Label:  0xe004
		this->a += 10;
	}

	virtual ~E()
	{
		// Label:  0xe005
	}

protected:
	int a;
};


class F : public E
{
public:
	F()
	: b(22)
	{
		// Label:  0xe006
	}

	void foo()
	{
		// Label:  0xe007
		a += 3;
	}

	int weight()
	{
		// Label:  0xe008
		return this->a + this->b;
	}

	int maximum()
	{
		// Label:  0xe009
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


	~F()
	{
		// Label:  0xe00a
	}

private:
	int b;

};

class G : public E
{
public:
	G()
	: c(22)
	{
		// Label:  0xe00b
	}

	void foo()
	{
		// Label:  0xe00c
		a += 33;
	}

	int maximum()
	{
		// Label:  0xe00d
		int max = this->a;

		if ( this->a > this->c)
		{
			max = this->a;
		}
		else
		{
			max = this->c;
		}
		return max;
	}

	int weight()
	{
		// Label:  0xe00e
		return this->a + this->c;
	}

	~G()
	{
		// Label:  0xe00f
	}

private:
	int c;

};

#endif

// ---  End of File ---------------
