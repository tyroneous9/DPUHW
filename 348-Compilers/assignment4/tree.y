%{

/*-------------------------------------------------------------------------*
 *---									---*
 *---		tree.y							---*
 *---									---*
 *---	    This file defines a parser for grammar that defines a tree,	---*
 *---	and the high-level functions that run the program.		---*
 *---									---*
 *---	    The grammar is:						---*
 *---		S  -> N S						---*
 *---		S  -> 							---*
 *---		N  -> root ( <str> )					---*
 *---		N  -> node ( <str> , L )				---*
 *---		L  -> [ ]						---*
 *---		L  -> [ LL ]						---*
 *---		LL -> <str>						---*
 *---		LL -> LL , <str>					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1A				Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include			"headers.h"

//  PURPOSE:  To store the Node instances until they are incorporated into
//	parts of the tree.
extern
NodeStore	nodeStore;


//  PURPOSE:  To hold the root of the tree.
extern
Node*		rootPtr;


//  PURPOSE:  To create and return the address of a heap-allocated
//	data-structure that can hold names of Nodes.  No parameters.
std::vector<std::string>*
		createNewStringDsPtr
				();

%}

%union
{
  std::string*			strPtr_;
  std::vector<std::string>*	stringDsPtr_;
}

%start S

%token root node "(" ")" "[" "]" ","

%token <strPtr_> STRING

%type <stringDsPtr_> L LL

%%

S:
    N S
    |
    ;

N: root "(" STRING ")"
    {
        rootPtr = nodeStore.get(*$3);
        delete $3;
    }
;

N: node "(" STRING "," L ")"
    {
        Node* newNode = new Node(*$3, $5);
        nodeStore.put(newNode);
        delete $3;
    }
;



%%

//	----	----	----	Global variables:	----	----	//

//  PURPOSE:  To hold an array of space chars.
char		spaceCharArray[MAX_LINE+1];


//  PURPOSE:  To hold the root of the tree.
Node*		rootPtr		= NULL;


//  PURPOSE:  To store the Node instances until they are incorporated into
//	parts of the tree.
NodeStore	nodeStore;



//	----	----	----	Node methods:	----	----	----	//

//  PURPOSE:  To initialize '*this' to have name 'newName' and the children
//  	named in 'childrenNameDsPtr'.  delete()s 'childrenNameDsPtr'.
//	No return value.
Node::Node			(const std::string&	newName,
				 std::vector<std::string>*	
				 			newChildrenDsPtr
				) :
				name_(newName),
				childrenDs_()
{
  //  I.  Application validity check:
  if  (newChildrenDsPtr == NULL)
  {
    fprintf(stderr,"NULL ptr to Node constructor\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Initialize '*this':
  //  II.A.  Initialize 'childrenDs_':
  for  (size_t ind = 0;  ind < newChildrenDsPtr->size();  ind++)
  {
    childrenDs_.push_back(nodeStore.get((*newChildrenDsPtr)[ind]));
  }

  //  III.  Finished:
  delete(newChildrenDsPtr);
}


//  PURPOSE:  To release the resources of '*this'.  No parameters.
//	No return value.
Node::~Node			()
{
  //  I.  Application validity check:

  //  II.  Release resources:
  for  (size_t in = 0;  in < getNumChildren();  in++)
  {
    delete(childrenDs_[in]);
  }

  //  III.   Finished:
}


//  PURPOSE:  To print '*this' out to 'filePtr'.  'depth' tells the depth
//	of '*this' from the root of the tree.  No return value.
void		Node::print	(FILE*		filePtr,
				 size_t		depth	// = 0
				)
				const
{
  //  I.  Application validity check:
  if  (filePtr == NULL)
  {
    fprintf(stderr,"NULL ptr to Node::print()\n");
    exit(EXIT_FAILURE);
  }

  //  II.  Print '*this':
  size_t	spacing	= depth * 2;

  fprintf
	(filePtr,"%s%s\n",
	 (spaceCharArray+sizeof(spaceCharArray)-1) - spacing,
	 getNameCPtr()
	);

  for  (size_t ind = 0;  ind < getNumChildren();  ind++)
  {
    getChild(ind)->print(filePtr,depth+1);
  }

  //  III.  Finished:    
}


//	----	----	----	NodeStore methods:	----	----	//

//  PURPOSE:  To release the resources of '*this'.  No parameters.
//	No return value.
NodeStore::~NodeStore		()
{
  //  I.  Application validity check:

  //  II.  Release resources:
  if  ( !nameToNodePtrMap_.empty() )
  {
    bool	isFirst	= true;

    fprintf
	(stderr,
	 "WARNING: These Node instance(s) were not included in the tree.\n"
	);

    do
    {
      auto	iter	= nameToNodePtrMap_.begin();
      Node*	nodePtr	= iter->second;

      fprintf
	    (stderr,"%s%s",
	     (isFirst ? "" : ", "), nodePtr->getNameCPtr()
	    );
      nameToNodePtrMap_.erase(iter);
    }
    while  ( !nameToNodePtrMap_.empty() );

    fprintf(stderr,"\n");
  }

  //  III.  Finished:
}


//  PURPOSE:  To attempt to find the Node named 'name', remove it from
//	'*this', and return its address.  Prints an error message and quits
//	if no such Node instance is found.
Node*		NodeStore::get	(const std::string&	name
				)
{
  //  I.  Application validity check:
  Node*	returnMe= NULL;
  auto	found	= nameToNodePtrMap_.find(name);

  if  (found == nameToNodePtrMap_.end())
  {
    fprintf(stderr,"No node \"%s\" defined.\n",name.c_str());
    exit(EXIT_FAILURE);
  }

  //  II.  Attempt to get named node:
  returnMe	= found->second;
  nameToNodePtrMap_.erase(found);

  //  III.  Finished:
  return(returnMe);
}


//  PURPOSE:  To place a new node with address 'nodePtr' in '*this' Store.
//	Prints an error message and quits if there already is a Node instance
//	in '*this' with the same name.
void		NodeStore::put	(Node*		nodePtr
				)
{
  //  I.  Application validity check:
  std::string	name	= nodePtr->getName();
  auto		found	= nameToNodePtrMap_.find(name);

  if  (found != nameToNodePtrMap_.end())
  {
    fprintf
	(stderr,"Attempt to define two or more nodes named \"%s\".\n",
	 name.c_str()
	);
    exit(EXIT_FAILURE);
  }

  //  II.  Attempt to put '*nodePtr' in '*this':
  nameToNodePtrMap_[name]	= nodePtr;

  //  III.  Finished:
}


//	----	----	----	Global functions:	----	----	//

//  PURPOSE:  To create and return the address of a heap-allocated
//	data-structure that can hold names of Nodes.  No parameters.
std::vector<std::string>*
		createNewStringDsPtr
				()
{
  return(new std::vector<std::string>);
}


//  PURPOSE:  To tell the user that a syntax error described by 'errMsgCPtr'
//	was found.  Quits program an return 'EXIT_FAILURE' to OS.
int	    	yyerror		(const char*	errMsgCPtr
				)
{
  fprintf
	(stderr,"Problem found at or before line %ld: %s.\n",
  	 lineNum,errMsgCPtr
	);
  exit(EXIT_FAILURE);
}


//  PURPOSE:  To return a C-string telling a filepath, either from the command
//	line or the keyboard.  'argc' tells how many arguments were on the
//	command line and 'argv[]' points to those arguments.
char*		getFilepath	(int		argc,
				 char*		argv[]
				)
{
  static
  char	line[MAX_LINE];
  char*	cPtr;

  //  I.  Application validity check:

  //  II.  Get input:
  //  II.A.  Handle command line input:
  if  (argc > 1)
  {
    strncpy(line,argv[1],MAX_LINE);
    return(line);
  }

  //  II.B.  Handle keyboard input:
  printf("Filepath: ");
  fgets(line,MAX_LINE,stdin);

  cPtr	= strchr(line,'\n');
  if  (cPtr != NULL)
  {
    *cPtr	= '\0';
  }

  //  III.  Finished:
  return(line);
}


//  PURPOSE:  To attempt to read and print a tree whose definition may be
//	given on the command line with 'argc' arguments listed in 'argv[]'.
//	Returns 'EXIT_SUCCESS' to OS on success or 'EXIT_FAILURE' otherwise.
int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validty check:

  //  II.  Do work:
  int		returnMe	= EXIT_SUCCESS;
  const char*	filePathCPtr	= getFilepath(argc,argv);

  yyin				= fopen(filePathCPtr,"r");

  memset(spaceCharArray,' ',sizeof(spaceCharArray)-1);
  spaceCharArray[sizeof(spaceCharArray)-1]	= '\0';

  if  (yyin == NULL)
  {
    fprintf(stderr,"Cannot open %s.\n",filePathCPtr);
    exit(EXIT_FAILURE);
  }

  if  (yyparse() == 0)
  {
    if  (rootPtr != NULL)
    {
      rootPtr->print(stdout);
      delete(rootPtr);
    }
    else
    {
      fprintf(stderr,"Parse valid but no root defined.\n");
    }
  }
  else
  {
    returnMe	= EXIT_FAILURE;
  }

  //  III.  Finished:
  return(returnMe);
}
