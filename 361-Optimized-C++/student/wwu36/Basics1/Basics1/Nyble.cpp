//----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Nyble.h"
#include <string.h>

Nyble::Nyble() {
	data = NULL;
}

Nyble::Nyble(int data) {
	this->data = (unsigned char)(data & 0x0F);
}

Nyble::Nyble(unsigned int data) {
	this->data = (unsigned char) (data & 0x0F);
}

Nyble::Nyble(Nyble const& r) {
	this->data = r.data;
}

Nyble& Nyble::operator = (Nyble const& r) {
	this->data = r.data;
	return *this;
}

Nyble::~Nyble() {
	
}

Nyble Nyble::operator + (const int r) {
	int sum = ((int) this->data + r) & 0x0F;
	return Nyble(sum);
}

Nyble Nyble::operator + (const Nyble &r) {
	int sum = ((int)this->data + (int)r.data) & 0x0F;
	return Nyble(sum);
}

Nyble operator+ (const int l, Nyble &r) {
	int sum = ((int) r.getData() + l) & 0x0F;
	return Nyble(sum);
}

Nyble Nyble::operator += (const Nyble &r) {
	this->data = (unsigned char) (((int) this->data + r.data) & 0x0F);
	return *this;
}

Nyble Nyble::operator ++ () {
	this->data = (unsigned char) (((int)this->data + 1) & 0x0F);
	return *this;
}

Nyble Nyble::operator ++ (int) {
	Nyble old(*this);
	this->data = (unsigned char) (((int)this->data + 1) & 0x0F);
	return old;
}

Nyble Nyble::operator << (const int r) {
	int result = ((this->data << r) % 0x0F);
	return Nyble(result);
}

Nyble Nyble::operator ~ () {
	int result = (int) ~this->data;
	return Nyble(result);
}

Nyble Nyble::operator + () {
	int result = (int)this->data + 3;
	return Nyble(result);
}

Nyble::operator unsigned int() {
	return (unsigned int)this->data - 3;
}

unsigned char Nyble::getData()
{
	return this->data;
}


//---  End of File ---
