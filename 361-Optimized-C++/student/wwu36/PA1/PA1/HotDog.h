//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef HOTDOG_H
#define HOTDOG_H

// Add files include as needed
#include "Condiments.h"

class HotDog
{
public:
	// These methods are just stubbed out... may need to change
	HotDog();
	HotDog(const HotDog &);
	HotDog &operator = (const HotDog &);
	virtual ~HotDog();

	// Public Methods (Required)
	void Minus(const Condiments condiment);
	void Add(const Condiments condiment);

	// add code here (add more methods if desired)
	HotDog* getNext();
	void setNext(HotDog*);
	HotDog* getPrev();
	void setPrev(HotDog*);
	unsigned int getCondiments();
	// ---------------------------------------------------
	// Data:
	// --------------------------------------------------
	// use the condiments unsigned integer provided
	// no additional data for condiments
	// --------------------------------------------------
private:
	
	HotDog *pNext;
	HotDog *pPrev;
	unsigned int condiments;
};

#endif

//---  End of File ---
