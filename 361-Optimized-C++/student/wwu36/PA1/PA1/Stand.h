//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef STAND_H
#define STAND_H

// Add files include as needed
#include "Names.h"
#include "Order.h"

class Stand
{
public:
	// Public Methods (Required)
	Stand();
	Stand(const Stand &);
	Stand &operator = (const Stand &);
	virtual ~Stand();

	// Public Methods (Required)
	void Remove(const Name name);
	void Add(Order * const pOrder);
	int GetCurrOrders() const;
	int GetPeakOrders() const;
	
	// Add more methods if desired


	// ---------------------------------
	// Data:
	// ---------------------------------
private:
	Order *poHead;
	int numCurrentOrders;
	int numPeakOrders;
};

#endif

//---  End of File ---
