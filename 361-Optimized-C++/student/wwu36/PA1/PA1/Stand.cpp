//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Stand.h"

// Methods

Stand::Stand()
{
	numCurrentOrders = 0;
	numPeakOrders = 0;
	poHead = nullptr;
}

Stand::Stand(const Stand &r)
{
	this->numCurrentOrders = r.numCurrentOrders;
	this->numPeakOrders = r.numPeakOrders;
	this->poHead = nullptr;
	if (r.poHead == nullptr)
		return;
	// loop from tail to head
	Order* rCurr = r.poHead;
	while (rCurr->getNext() != nullptr)
		rCurr = rCurr->getNext();
	while (rCurr != nullptr) {
		this->Add(new Order(*rCurr));
		rCurr = rCurr->getPrev();
	}
}


Stand &Stand::operator = (const Stand &r)
{
	this->numCurrentOrders = r.numCurrentOrders;
	this->numPeakOrders = r.numPeakOrders;
	this->poHead = nullptr;
	if (r.poHead == nullptr)
		return *this;
	Order* rCurr = r.poHead;
	while (rCurr->getNext() != nullptr)
		rCurr = rCurr->getNext();
	while (rCurr != nullptr) {
		this->Add(new Order(*rCurr));
		rCurr = rCurr->getPrev();
	}
	return *this;
}

Stand::~Stand()
{
	Order* curr=poHead;
	while(curr != nullptr) {
		Order* deleteMe = curr;
		curr = curr->getNext();
		delete deleteMe;
	}
}

int Stand::GetCurrOrders() const
{
	return numCurrentOrders;
}

int Stand::GetPeakOrders() const
{
	return numPeakOrders;
}

void Stand::Add(Order * const pOrder)
{
	if(poHead==nullptr)
		poHead = pOrder;
	else {
		Order* curr = poHead;
		while (curr->getNext() != nullptr)
			curr = curr->getNext();
		curr->setNext(pOrder);
		pOrder->setPrev(curr);
	}
	numCurrentOrders += 1;
	if(numCurrentOrders > numPeakOrders)
		numPeakOrders = numCurrentOrders;
}

void Stand::Remove(const Name name)
{	
	Order* curr = poHead;
	while (curr != nullptr) {
		if (curr->getName() == name)
			break;
		curr = curr->getNext();
	}
	if (curr == poHead) {
		poHead = poHead->getNext();
	}
	if(curr->getPrev() != nullptr)
		curr->getPrev()->setNext(curr->getNext());
	if(curr->getNext() != nullptr)
		curr->getNext()->setPrev(curr->getPrev());
	delete curr;
	numCurrentOrders -= 1;
	
}

//---  End of File ---
