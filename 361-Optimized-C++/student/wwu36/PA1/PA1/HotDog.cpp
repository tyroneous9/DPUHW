//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "HotDog.h"

// Methods

HotDog::HotDog()
{
	condiments = (int)Condiments::Plain;
	setNext(nullptr);
	setPrev(nullptr);
} 

HotDog::HotDog(const HotDog &r)
{
	this->condiments = r.condiments;
	setNext(nullptr);
	setPrev(nullptr);

}


HotDog &HotDog::operator = (const HotDog &r)
{
	this->condiments = r.condiments;
	setNext(nullptr);
	setPrev(nullptr);
	return *this;
} 

HotDog::~HotDog()
{
	
} 

void HotDog::Minus(const Condiments condiment)
{
	// Only use bit-wise operations
	unsigned int mask = (unsigned int) condiment;
	mask = ~(mask);
	condiments = condiments & mask;
}

void HotDog::Add(const Condiments condiment)
{
	// Only use bit-wise operations
	condiments = condiments | (unsigned int) condiment;
}

HotDog* HotDog::getNext() {
	return pNext;
}

void HotDog::setNext(HotDog* p) {
	pNext = p;
}

HotDog* HotDog::getPrev() {
	return pPrev;
}

void HotDog::setPrev(HotDog* p) {
	pPrev = p;
}

unsigned int HotDog::getCondiments() {
	return condiments;
}

// ---  End of File ---------------

