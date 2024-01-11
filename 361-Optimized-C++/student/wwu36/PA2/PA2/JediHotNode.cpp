//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#include "JediHotNode.h"
#include "JediRedirect.h"
class JediRedirect;
JediHotNode::JediHotNode() {
	pRedirect = new JediRedirect();
}

JediHotNode::~JediHotNode() {
	delete pRedirect;
}
// ---  End of File ---

