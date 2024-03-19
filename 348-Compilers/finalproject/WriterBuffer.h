/*-------------------------------------------------------------------------*
 *---									---*
 *---		WriterBuffer.h						---*
 *---									---*
 *---	    This file declares a class that represents byte buffer that	---*
 *---	can either point to fixed data elsewhere with a const pointer,	---*
 *---	or a heap-allocated buffer for variable-sized content.		---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 9a		2021 September 28	Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

  class	WriterBuffer
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold the address of the data to return.
    const char*			dataPtr_;

    //  PURPOSE:  To hold the length of the data to return.
    size_t			numBytes_;

    //  PURPOSE:  To hold the address of the heap-allocated space.
    char*			beginHeapPtr_;

    //  PURPOSE:  To hold the length of the heap-allocated space.
    size_t			numHeapBytes_;

    //  PURPOSE:  To hold the address of where in the heap array to write the
    //		next data.
    char*			heapRunPtr_;

    //  II.  Disallowed auto-generated methods:
    //  No copy constructor:
    WriterBuffer		(const WriterBuffer&);

    //  No copy assignment op:
    WriterBuffer&
		operator=	(const WriterBuffer&);

  protected :
    //  III.  Protected methods:
    //  PURPOSE:  To return the address of just after the heap array.
    const char*	getHeapEndCPtr	()
				const
				{ return(beginHeapPtr_+numHeapBytes_); }

    //  PURPOSE:  To return the remaining bytes left in the heap before it
    //		needs to be resized.
    size_t	getRemainingHeapSize
				()
				const
				{ return(getHeapEndCPtr() - heapRunPtr_); }

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this' to an empty buffer.
    WriterBuffer		() :
				dataPtr_(NULL),
				numBytes_(0),
				beginHeapPtr_(NULL),
				numHeapBytes_(0),
				heapRunPtr_(NULL)
				{ }

    //  PURPOSE:  To release the resources of '*this'.  No parameters.
    //		No return value.
    ~WriterBuffer		()
				{
				  free(beginHeapPtr_);
				}

    //  V.  Accessors:
    //  PURPOSE:  To return a pointer to the beginning of the data.
    //		No parameters.
    const char*	getDataPtr	()
				const
				{ return(dataPtr_); }

    //  PURPOSE:  To return the number of bytes of data
    size_t	getNumBytes	()
				const
				{ return(numBytes_); }

    //  PURPOSE:  To return 'true' if '*this' is empty, or 'false' otherwise.
    //		No parameters.
    bool	isEmpty		()
				const
				{ return(getNumBytes() == 0); }

    //  PURPOSE:  To return the string in this stored at offset 'offset'.
    const char*	getCPtr		(size_t		offset
				)
				const
				{ return(getDataPtr() + offset); }

    //  VI.  Mutators:
    //  PURPOSE:  To set '*this' to an empty state.  No parameters.
    //		No return value.
    void	clear		()
				{
				  dataPtr_	= NULL;
				  numBytes_	= 0;
				  heapRunPtr_	= beginHeapPtr_;
				}

    //  PURPOSE:  To initialize '*this' to point to the const data pointed to
    //		by 'sourceCPtr' of length 'sourceLen'.  No return value.
    void	initialize	(const char*	sourceCPtr,
				 size_t		sourceLen
				)
				{
				  dataPtr_	= sourceCPtr;
				  numBytes_	= sourceLen;
				}

    //  PURPOSE:  To initialize '*this' to point to the const data pointed to
    //		by 'sourceCPtr'.  Length of C-string computed by 'strlen()'.
    //		No return value.
    void	initialize	(const char*	sourceCPtr
				)
				{
				  initialize
					(sourceCPtr,
					 strlen(sourceCPtr)
					);
				}

    //  PURPOSE:  To append the C-string pointed to by 'toAppendCPtr' of
    //		length 'length' to the end of '*this'.    Returns offset from
    //		'beginHeapPtr_' where 'toAppendCPtr' will be stored.
    size_t	append		(const char*	toAppendCPtr,
				 size_t		length
				);

    //  PURPOSE:  To append the C-string pointed to by 'toAppendCPtr' to the
    //		end of '*this'.    Returns offset from 'beginHeapPtr_' where
    //		'toAppendCPtr' will be stored.
    size_t	append		(const char*	toAppendCPtr
				)
				{
				  return(append
					    (toAppendCPtr,
					     strlen(toAppendCPtr)
					    )
					);
				}

    //  PURPOSE:  To append the single char 'c' to the end of '*this'.  Returns
    //		offset from 'beginHeapPtr_' where 'toAppendCPtr' will be stored.
    size_t	append		(char	c
				)
				{
				  return(append(&c,1));
				}

    //  PURPOSE:  To insert the data pointed to by 'dataPtr' of length 'length'
    //		to the position indicated by 'reserved'.  'reserved' is
    //		updated so that calling insert() on '*this' again with
    //		'reserved' will add more data just after the insertion caused
    //		by this call.  No return value.
    void	insert		(const void*	toAppendCPtr,
				 size_t		length,
				 ReservedVarSizedBufferSpace&
						reserved
				)
				{
				  memcpy(beginHeapPtr_	+
				  	  reserved.giveAway(length),
					 toAppendCPtr,
					 length
					);
				}

    //  PURPOSE:  To append 'rhs' to the end of '*this'.  Returns reference to
    //		'*this'.
    WriterBuffer&
		operator+=	(const WriterBuffer&	rhs
				);

    //  PURPOSE:  To append 'rhs' to the end of '*this'.  Returns reference to
    //		'*this'.
    WriterBuffer&
		operator+=	(char	rhs
				)
      				{
				  append(rhs);
				  return(*this);
				}

    //  PURPOSE:  To append the C-string pointed to by 'rhsCPtr' to the end of
    //		'*this'.  Returns reference to '*this'.
    WriterBuffer&
		operator+=	(const char*	rhsCPtr
				)
      				{
				  append(rhsCPtr);
				  return(*this);
				}

    //  VII.  Methods that do main and misc. work class:
    //  PURPOSE:  To advance the mem copying pointer to the next multiple of
    //		'multiple'.  No return value.
    void	advanceToMultipleOf
				(uint32_t	multiple
				);

    //  PURPOSE:  To write() the data in '*this' concerning to file descriptor
    //		'fd' with file path 'filePathCPtr'.  No return value.
    void	write		(int		fd,
				 const char*	filePathCPtr
				);

    //  PURPOSE:  To return a reservation of 'numBytes' bytes to be written to
    //		later.
    ReservedVarSizedBufferSpace
		reserve		(size_t		numBytes
				);

    //  PURPOSE:  To return 'true' if '*this' contains a string equivalent to
    //		the one pointed to by 'rhsCPtr', or 'false' otherwise.
    bool	operator==	(const char*	rhsCPtr
				)
				const
				{
				  return(strncmp(getDataPtr(),
						 rhsCPtr,
						 getNumBytes()
						)
					 == 0
					);
				}

    //  PURPOSE:  To return 'false' if '*this' contains a string equivalent to
    //		the one pointed to by 'rhsCPtr', or 'true' otherwise.
    bool	operator!=	(const char*	rhsCPtr
				)
				const
				{
				  return( !(*this == rhsCPtr) );
				}

  };
