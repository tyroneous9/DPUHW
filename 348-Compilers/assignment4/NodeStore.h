/*-------------------------------------------------------------------------*
 *---									---*
 *---		NodeStore.h						---*
 *---									---*
 *---	    This file declares a class that keeps track of Node		---*
 *---	instances by their name.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1A				Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		NodeStore
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the map of Node names to their addresses.
  std::map<std::string,Node*>	nameToNodePtrMap_;

  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  NodeStore			(const NodeStore&)
				= delete;

  //  No copy assignment op:
  NodeStore&	operator=	(const NodeStore&)
				= delete;

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to an empty store.  No return value.
  NodeStore			() :
				nameToNodePtrMap_()
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~NodeStore			();

  //  V.  Accessors:
  //  PURPOSE:  To attempt to find the Node named 'name', remove it from
  //	'*this', and return its address.  Prints an error message and quits
  //	if no such Node instance is found.
  Node*		get		(const std::string&	name
				);

  //  VI.  Mutators:
  //  PURPOSE:  To place a new node with address 'nodePtr' in '*this' Store.
  //	Prints an error message and quits if there already is a Node instance
  //	in '*this' with the same name.
  void		put		(Node*		nodePtr
				);

  //  VII.  Methods that do the main and misc. work of this class:

};