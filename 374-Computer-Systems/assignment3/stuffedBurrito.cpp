//simplify code to swap between customer threads
//put gets stuck for 

/*-------------------------------------------------------------------------*
 *---									---*
 *---		stuffedBurrito.cpp					---*
 *---									---*
 *---	    This file defines a multi-threaded program that simulates	---*
 *---	the two customers (2 threads) placing ingredients into a	---*
 *---	linked-list representing a burrito.  Both customers get their	---*
 *---	ingredients from a thread serving thread.			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//	Compile with:
//	$ g++ stuffedBurrito.cpp -o stuffedBurrito -lpthread

#include	<stdlib.h>
#include	<stdio.h>
#include	<pthread.h>
#include	<unistd.h>


//----		Constants:						----//
const char*	INGREDIENT_NAME_ARRAY[]		= {"rice",
						   "beans",
						   "chicken",
						   "beef",
						   "sofritas",
						   "veggies",
						   "guacamole",
						   "salsa",
						   "cheese",
						   "coal slurry"
						  };

const int	INGREDIENT_NAME_ARRAY_LEN	= sizeof(INGREDIENT_NAME_ARRAY)
						  / sizeof(const char*);

const int	NUM_CUSTOMER_THREADS		= 2;

const int	NUM_INGREDIENTS_PER_CUSTOMER_THREAD
						= INGREDIENT_NAME_ARRAY_LEN /
						  NUM_CUSTOMER_THREADS;


//----		Classes:						----//
//  PURPOSE:  To hold the index of one burrito ingredient in a list of them.
class		Ingredient
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the index into INGREDIENT_NAME_ARRAY[].
  int				index_;

  //  PURPOSE:  To hold the address of the next Ingredient instance,
  //	or NULL if there is none.
  Ingredient*			nextPtr_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  Ingredient			();

  //  No copy constructor:
  Ingredient			(const Ingredient&);

  //  No copy-assignment op:
  Ingredient&	operator=	(const Ingredient&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to hold value 'newIndex' at the end of
  //	a list.  No return value.
  Ingredient			(int	newIndex
				) :
  				index_(newIndex),
				nextPtr_(NULL)
				{ }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~Ingredient			()
				{ }

  //  V.  Accessors:
  //  PURPOSE:  To return the index into INGREDIENT_NAME_ARRAY[].
  //	No parameters.
  int		getIndex	()
				const
				{ return(index_); }

  //  PURPOSE:  To return the address of the next Ingredient instance,
  //	or NULL if there is none.
  Ingredient*	getNextPtr	()
				const
				{ return(nextPtr_); }

  //  VI.  Mutators:
  //  PURPOSE:  To set the index into INGREDIENT_NAME_ARRAY[] to 'newIndex'.
  //  	No parameters.
  void		setIndex	(int	newIndex
				)
				{ index_	= newIndex; }

  //  PURPOSE:  To set the address of the next Ingredient instance to
  //	'newNextPtr'.  No parameters.
  void		setNextPtr	(Ingredient*		newNextPtr
				)
				{ nextPtr_	= newNextPtr; }

  //  VII.  Methods that do main and misc work of class.
};


//  PURPOSE: To implement a linked list of ingredients.
class		Burrito
{
  //  I.  Member vars:
  //  YOUR VARIABLES DECLARED HERE
  Ingredient* front;
  Ingredient* back;
  int size;
  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  Burrito			(const Burrito&);

  //  No copy-assignment nop:
  Burrito&	operator=	(const Burrito&);

protected :
  //  III.  Protected methods:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to an empty list.  No parameters.
  //	No return value.
  Burrito			()
  {
    //  YOUR CODE HERE
    front = NULL;
    back = NULL;
    size = 0;
  }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~Burrito			()
  {
    //  YOUR CODE HERE
    const Ingredient*	run;
    const Ingredient* deleteMe;
    for(run=front; run!=NULL; ) {
      deleteMe = run;
      run=run->getNextPtr();
      delete(deleteMe);
    }
    size = 0;
  }

  //  V.  Accessors:
  //  PURPOSE:  To return the number of ingredients in '*this'.  No parameters.
  int		getCount	()
				const
				{ return(size); /* CHANGE THAT 0 */ }

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To add 'newIndex' to the end of '*this'.  No return value.
  void		append		(int	newIndex
				)
  {
    Ingredient*	nodePtr	= new Ingredient(newIndex);
    //  YOUR CODE HERE
    if(getCount() == 0) {
      front = nodePtr;
      back = nodePtr;
      size++;
      return;
    } 
    back->setNextPtr(nodePtr);
    back = back->getNextPtr();
    size++;
  }

  //  PURPOSE:  To print the ingredients in '*this' list.  No parameters.
  //	No return value.
  void		print		()
				const
  {
    const Ingredient*	run;
    //  YOUR CODE HERE
    for(run=front; run!=NULL; run=run->getNextPtr()) {
      printf("    %s\n", INGREDIENT_NAME_ARRAY[run->getIndex()]);
    }
  }

};


//  PURPOSE:  To implement the object on which the server thread places
//	ingredients and the customer threads take ingredients.
class		IngredientTable
{
  //  I.  Member vars:
  //  YOUR VARIABLES DECLARED HERE
  int currentIndex;
  bool isCustomerTurn;
  pthread_mutex_t lock;
  pthread_cond_t serverTurn;
  pthread_cond_t customerTurn;
  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  IngredientTable		(const IngredientTable&);

  //  No copy-assignment op:
  IngredientTable&
	operator=		(const IngredientTable&);

protected :
  //  III.  Protected methodss:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to a blank table, and that it is the
  //	turn of the serving-thread.  No parameters.  No return value.
  IngredientTable		()
  {
    //  YOUR CODE HERE
    currentIndex = 0;
    isCustomerTurn = false;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&serverTurn, NULL);
    pthread_cond_init(&customerTurn, NULL);
  }

  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No return
  //	value.
  ~IngredientTable		()
  {
    //  YOUR CODE HERE
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&serverTurn);
    pthread_cond_destroy(&customerTurn);
  }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class.
  //  PURPOSE:  To note that 'i' is to be given to a customer.  No return value.
  void		put		(int		i)
  {
    //  YOUR CODE HERE                               
    pthread_mutex_lock(&lock);                    
    while(isCustomerTurn == true) {                      
      pthread_cond_wait(&serverTurn, &lock);          
    }
    currentIndex = i;                                  
    isCustomerTurn = true;                             
    printf("Server \"Who wants %s?\"\n",INGREDIENT_NAME_ARRAY[i]);
    pthread_cond_signal(&customerTurn);               
    pthread_mutex_unlock(&lock);                       
  }

  //  PURPOSE:  To return the index of the ingredient on '*this' table.
  //	Customer 'customerIndex' takes this ingredient to place in their
  //	burrito.
  int		get		(int  	       customerIndex
				)
  {
    int	returnMe;

    //  YOUR CODE HERE
    pthread_mutex_lock(&lock);
    while(isCustomerTurn == false) {
      pthread_cond_wait(&customerTurn, &lock);
    }
    returnMe	= currentIndex;	// CHANGE 0 TO YOUR INGREDIENT INDEX
    isCustomerTurn = false;
    printf("Customer %d \"I will take %s.\"\n",
	   customerIndex,INGREDIENT_NAME_ARRAY[returnMe]
	  );
    pthread_cond_signal(&serverTurn);
    pthread_mutex_unlock(&lock);
    return(returnMe);
  }

};


//  PURPOSE:  To implement turn-taking between the 2 customer threads.
class		CustomerTurn
{
  //  I.  Member vars:
  //  YOUR VARIABLES DECLARED HERE
  int turnIndex;
  pthread_mutex_t lock;
  pthread_cond_t thread0Turn;
  pthread_cond_t thread1Turn;
  //  II.  Disallowed auto-generated methods:
  //  No copy constructor:
  CustomerTurn			(const CustomerTurn&);

  //  No copy-assignment ops:
  CustomerTurn&	operator=	(const CustomerTurn&);

protected :
  //  III.  Protected:

public :
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this'.  No parameters.  No return value.
  CustomerTurn			()
  {
    //  YOUR CODE HERE
    turnIndex = 0;
    pthread_mutex_init(&lock,NULL);
    pthread_cond_init(&thread0Turn, NULL);
    pthread_cond_init(&thread1Turn, NULL);
  }


  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~CustomerTurn			()
  {
    //  YOUR CODE HERE
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&thread0Turn);
    pthread_cond_destroy(&thread1Turn);
  }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class.
  //  PURPOSE:  To obtain from 'ingredientTable' the most recent ingredient
  //	and place it in 'burrito' for thread 'threadIndex'.  No return value.
  void		moveIngredientFromTableToBurrito
				(int			threadIndex,
				 IngredientTable&	ingredientTable,
				 Burrito&		burrito
				)
  {
    //  YOUR CODE HERE
    pthread_mutex_lock(&lock);

    while(threadIndex == 0 && turnIndex == 1) {
        pthread_cond_wait(&thread0Turn, &lock);
    }
    while(threadIndex == 1 && turnIndex == 0) {
        pthread_cond_wait(&thread1Turn, &lock);
    }

    burrito.append(ingredientTable.get(threadIndex));
    turnIndex = (threadIndex == 0) ? 1 : 0;
    (threadIndex == 0) ? pthread_cond_signal(&thread1Turn) : pthread_cond_signal(&thread0Turn);
    pthread_mutex_unlock(&lock);
  }
    

};


//----		Global vars:						----//
//  PURPOSE:  To be the table on which the server thread places ingredients
//	and the customer threads take ingredients.
IngredientTable	ingredientTable;

//  PURPOSE:  To the the instance that regulates which customer's turn it is.
CustomerTurn	customerTurn;


//----		Functions:						----//
//  PURPOSE:  To be the function that the serving thread runs.  Ignores 'vPtr'.
//	Returns 'NULL'.
void*		server		(void*		vPtr
				)
{
  //  I.  Application validity check:
  srand(getpid());
  //  II.  Server the ingredients:
  //  II.A.  Create an array of ingredients in a pseudo-random order:
  int*	intArray	= (int*)calloc(INGREDIENT_NAME_ARRAY_LEN,sizeof(int));

  for  (int i = 0;  i < INGREDIENT_NAME_ARRAY_LEN;  i++)
  {
    intArray[i]	= i;
  }

  for  (int i = 0;  i < INGREDIENT_NAME_ARRAY_LEN;  i++)
  {
    int	first		= rand() % INGREDIENT_NAME_ARRAY_LEN;
    int	second		= rand() % INGREDIENT_NAME_ARRAY_LEN;
    int	temp		= intArray[first];

    intArray[first]	= intArray[second];
    intArray[second]	= temp;
  }
  //  II.B.  Serve the ingredients:
  for  (int i = 0;  i < INGREDIENT_NAME_ARRAY_LEN;  i++)
  {
    int	ingredientIndex	= intArray[i];
    ingredientTable.put(ingredientIndex);
  }
  //  II.C.  Clean up:
  free(intArray);

  //  III.  Finished:
  return(NULL);
}


//  PURPOSE:  To be the function that the customer threads run.  'vPtr'
//  	points to the integer that tells which thread is being implement.
//	Returns address of a 'new Burrito' instance.
void*		customer	(void*		vPtr
				)
{
  int		threadIndex	= *(int*)vPtr;
  Burrito*	burritoPtr	= new Burrito;

  for  (int i = 0;  i < NUM_INGREDIENTS_PER_CUSTOMER_THREAD;  i++)
  {
    customerTurn.moveIngredientFromTableToBurrito
			(threadIndex,
			 ingredientTable,
			 *burritoPtr
			);
  }

  return((void*)burritoPtr);
}


//  PURPOSE:  To simulate two customers (2 threads) placing ingredients into a
//	linked-list representing a burrito.  Both customers get their
//	ingredients from a thread serving thread.  Ignores command line
//	arguments.  Returns 'EXIT_SUCCESS'.
int		main		()
{
  //  I.  Application validity check:

  //  II.  Simulate creating burritos:
  //  II.A.  Init random number generator:
  srand(getpid());
  printf("PID=%d\n",getpid());

  //  II.B.  Start threads:
  Burrito*	burritoPtr;
  pthread_t	serverThread;
  pthread_t	customerThreadArray[NUM_CUSTOMER_THREADS];
  int		threadIndexArray[NUM_CUSTOMER_THREADS]	= {0,1};

  //  YOUR CODE HERE
  pthread_create(&serverThread, NULL, server, NULL);
  int i;
  for(i=0; i<NUM_CUSTOMER_THREADS; i++) {
    pthread_create(&customerThreadArray[i], NULL, customer, (void*)&threadIndexArray[i]);
  }
  //  II.C.  Wait for threads to finish:  
  //  YOUR CODE HERE
  pthread_join(serverThread, NULL);
  for(i=0; i<NUM_CUSTOMER_THREADS; i++) {
    pthread_join(customerThreadArray[i], (void**)&burritoPtr);
    printf("Customer %d has %d ingredients.\n", i, burritoPtr->getCount());
    burritoPtr->print();
  }
  delete(burritoPtr);
  //  III.  Finished:
  return(EXIT_SUCCESS);
}