/*-------------------------------------------------------------------------*
 *---									---*
 *---		Node.h							---*
 *---									---*
 *---	    This file declares a class that implements a node in a	---*
 *---	tree.								---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1A				Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

class		Node
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the name of '*this' Node.
  std::string			name_;

  //  PURPOSE:  To hold the addresses of the children of '*this' Node.
  std::vector<Node*>		childrenDs_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Node				()
				= delete;

  //  No copy constructor:
  Node				(const Node&)
				= delete;

  //  No copy assignment op:
  Node&		operator=	(const Node&)
				= delete;

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to have name 'newName' and the children
  //  	named in 'childrenNameDsPtr'.  delete()s 'childrenNameDsPtr'.
  //	No return value.
  Node				(const std::string&		newName,
				 std::vector<std::string>*	newChildrenDsPtr
				);

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~Node				();

  //  V.  Accessors:
  //  PURPOSE:  To return the name of '*this' Node.  No parameters.
  const std::string&
		getName		()
				const
				{ return(name_); }

  //  PURPOSE:  To return the name of '*this' Node as a C-string.
  //	No parameters.
  const char*	getNameCPtr	()
				const
  				{ return(name_.c_str()); }

  //  PURPOSE:  To return the number of children.  No parameters.
  size_t	getNumChildren	()
				const
				{ return(childrenDs_.size()); }

  //  PURPOSE:  To return the address of 'n'th child.
  Node*		getChild	(size_t		n
				)
				const
				{
				  return( (n >= getNumChildren())
				  	  ? NULL
					  : childrenDs_[n]
					);
				}

  //  VI.  Mutators:

  //  VII.  Methods that do the main and misc. work of this class:
  //  PURPOSE:  To print '*this' out to 'filePtr'.  'depth' tells the depth
  //	of '*this' from the root of the tree.  No return value.
  void		print		(FILE*		filePtr,
  				 size_t		depth	= 0
				)
				const;

};