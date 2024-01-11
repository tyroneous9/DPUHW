//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef ORDER_H
#define ORDER_H

// Add files include as needed
#include "HotDog.h"
#include "Names.h"

class Order 
{
public:
	// Public Methods (Required)
	Order();
	Order(const Order &);
	Order &operator = (const Order &);
	virtual ~Order();

	Order(const Name name);

	void Add(HotDog * const pDog);
	void Remove(HotDog * const pDog);
	void SetName(const Name name);

	// Add more methods if desired


	// ---------------------------------
	// Data:
	// ---------------------------------
private:
	Order *pNext;
	Order *pPrev;

	Name    name;
	HotDog *poHead;
};

#endif

//---  End of File ---
