//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "Node.h"
#include "ColdNode.h"

// Insert code
ColdNode& ColdNode::operator = (const Node& r) {
    this->key = r.key;
	this->aa = r.aa;
	this->bb = r.bb;
	this->cc = r.cc;
	this->dd = r.dd;
	this->x = r.x;
	this->y = r.y;
	this->z = r.z;
	this->w = r.w;
	this->A = r.A;
	this->B = r.B;
	this->C = r.C;
	this->D = r.D;
	this->MA = r.MA;
	this->MB = r.MB;
	this->MC = r.MC;
	this->MD = r.MD;
	this->ME = r.ME;
    memcpy(this->name, r.name, Node::NAME_SIZE);
	return *this;
}

// ---  End of File ---

