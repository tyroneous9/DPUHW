//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef NYBLE_H
#define NYBLE_H

class Nyble
{
public:
	//big four
	Nyble();
	Nyble(int data);
	Nyble(unsigned int data);
	Nyble(const Nyble &r);
	Nyble& operator = (const Nyble &r);
	~Nyble();
	//operators
	Nyble operator + (const int r);
	Nyble operator + (const Nyble &r);
	Nyble operator += (const Nyble &r);
	Nyble operator ++ ();
	Nyble operator ++ (int);
	Nyble operator << (const int r);
	Nyble operator ~ ();
	Nyble operator + ();
	operator unsigned int();
	//getter
	unsigned char getData();

private:
        // Do not change this data
	unsigned char data;

};

#endif

//---  End of File ---
