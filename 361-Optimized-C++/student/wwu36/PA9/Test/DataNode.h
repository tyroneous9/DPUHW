//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef DATANODE_H
#define DATANODE_H

#include "Node.h"

struct DataNode : public Node
{
public:

	int row;
	int col;

	DataNode(int _row, int _col);
	DataNode(const DataNode &) = delete;
	DataNode &operator = (const DataNode &) = delete;
	~DataNode();


private:


};

#endif

// ---  End of File ---
