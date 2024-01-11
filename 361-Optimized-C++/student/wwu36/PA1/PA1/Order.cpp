//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Order.h"

// Methods

Order::Order()
{
	SetName(Name::Unknown);
	poHead = nullptr;
	setNext(nullptr);
	setPrev(nullptr);
}

Order::Order(const Order &r)
{
	this->SetName(r.name);
	this->poHead = nullptr;
	if(r.poHead==nullptr)
		return;
	// loop from tail to head
	HotDog* rCurr = r.poHead;
	while(rCurr->getNext() != nullptr)
		rCurr = rCurr->getNext();
	while(rCurr != nullptr) {
		this->Add(new HotDog(*rCurr));
		rCurr = rCurr->getPrev();
	}
	setNext(nullptr);
	setPrev(nullptr);
}


Order &Order::operator = (const Order &r)
{
	this->SetName(r.name);
	this->poHead = nullptr;
	if (r.poHead == nullptr)
		return *this;
	// loop from tail to head
	HotDog* rCurr = r.poHead;
	while (rCurr->getNext() != nullptr)
		rCurr = rCurr->getNext();
	while (rCurr != nullptr) {
		this->Add(new HotDog(*rCurr));
		rCurr = rCurr->getPrev();
	}
	setNext(nullptr);
	setPrev(nullptr);
	return *this;
}

Order::~Order()
{
	HotDog* curr = this->poHead;
	while(curr != nullptr) {
		HotDog* deleteMe = curr;
		curr = curr->getNext();
		delete deleteMe;
	}
}

Order::Order(Name name)
{
	SetName(name);
	poHead = nullptr;
	setNext(nullptr);
	setPrev(nullptr);
}

void Order::Add(HotDog *p)
{
	if(poHead==nullptr)
		poHead = p;
	else {
		p->setNext(poHead);
		poHead->setPrev(p);
		poHead = p;
	}
}

void Order::Remove(HotDog *p)
{
	if (p == poHead)
		poHead = poHead->getNext();
	if(p->getPrev() != nullptr)
		p->getPrev()->setNext(p->getNext());
	if(p->getNext() != nullptr)
		p->getNext()->setPrev(p->getPrev());
	delete p;
}

void Order::SetName(Name _name)
{
	name = _name;
}

Order* Order::getNext() {
	return pNext;
}

void Order::setNext(Order* p) {
	pNext = p;
}

Order* Order::getPrev() {
	return pPrev;
}

void Order::setPrev(Order* p) {
	pPrev = p;
}

Name Order::getName() {
	return name;
}

//---  End of File ---
