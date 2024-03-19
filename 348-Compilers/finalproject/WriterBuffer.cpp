/*-------------------------------------------------------------------------*
 *---									---*
 *---		WriterBuffer.cpp					---*
 *---									---*
 *---	    This file define members for a class that represents byte	---*
 *---	buffer that can either point to fixed data elsewhere with a	---*
 *---	const pointer, or a heap-allocated buffer for variable-sized	---*
 *---	content.							---*
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

#include	"header.h"


  //  PURPOSE:  To append to the end of '*this' the C-string pointed to
  //	by 'toAppendCPtr' of length 'length'.  Returns offset from
  //	'beginHeapPtr_' where 'toAppendCPtr' will be stored.
  size_t	WriterBuffer::append
				(const char*	toAppendCPtr,
				 size_t		length
				)
  {
    //  I.  Application validity check:

    //  II.  Append 'toAppendCPtr' to the end of '*this':
    size_t	toReturn;

    if  ( (getDataPtr() == NULL)  ||  (getDataPtr() == beginHeapPtr_) )
    {
      //  II.A.  Handle when there is no const data to copy to heap:
      //  II.A.1.  Allocate space if needed:
      if  ( (numHeapBytes_ == 0)			||
	    (getRemainingHeapSize() < (length + 1))
	  )
      {
	size_t	runOffset	= heapRunPtr_ - beginHeapPtr_;
	size_t	numNeededBytes	= runOffset + length + 1;
	size_t	toAllocate	= (numHeapBytes_ == 0)
	    			  ? 4096
				  : 2*numHeapBytes_;

	while  (toAllocate < numNeededBytes)
	{
	  toAllocate	*= 2;
	}

	beginHeapPtr_	= (char*)realloc(beginHeapPtr_,toAllocate);

	if  (beginHeapPtr_ == NULL)
	{
	  throw "Out of heap memory";
	}

	numHeapBytes_	= toAllocate;
	heapRunPtr_	= beginHeapPtr_ + runOffset;
      }

      //  II.A.2.  Copy 'toAppendCPtr':
      toReturn	 = heapRunPtr_ - beginHeapPtr_;
      memcpy(heapRunPtr_,toAppendCPtr,length);
      heapRunPtr_	+= length;
      *heapRunPtr_	 = '\0';
      numBytes_	 = heapRunPtr_ - beginHeapPtr_;
      dataPtr_	 = beginHeapPtr_;
    }
    else
    {
      //  II.B.  Handle when there *is* const data to copy to heap:
      //  II.B.1.  Remember const data:
      const char*	tempCPtr	= getDataPtr();
      size_t		tempLen		= getNumBytes();

      //  II.B.2.  Reset '*this' so it can hold const or heap data:
      clear();

      //  II.B.3.  Append const data to '*this' in its heap:
      append(tempCPtr,tempLen);

      //  II.B.4.  Concatenate with data originally given to append:
      toReturn	= append(toAppendCPtr,length);
    }

    //  III.  Finished:
    return(toReturn);
  }


  //  PURPOSE:  To append 'rhs' to the end of '*this'.  Returns reference to
  //	'*this'.
  WriterBuffer&
		WriterBuffer::operator+=
				(const WriterBuffer&	rhs
				)
  {
    //  I.  Application validity check:

    //  II.  Append 'rhs' to end of '*this':
    if  (this == &rhs)
    {
      //  II.A.  Handle special case of appending self to self:
      //  II.A.1.  Make copy:
      size_t	tempLen		= getNumBytes();
      char*	tempCPtr	= (char*)malloc(tempLen);

      if  (tempCPtr == NULL)
      {
	throw "Out of heap memory";
      }

      memcpy(tempCPtr,getDataPtr(),tempLen);

      //  II.A.2.  Append copy:
      append(tempCPtr,tempLen);

      //  II.A.3.  Release copy:
      free(tempCPtr);
    }
    else
    {
      //  II.B.  Handle appending something else to self:
      append(rhs.getDataPtr(),rhs.getNumBytes());
    }

    //  III.  Finished:
    return(*this);
  }


  //  PURPOSE:  To advance the mem copying pointer to the next multiple of
  //	'multiple'.  No return value.
  void		WriterBuffer::advanceToMultipleOf
				(uint32_t	multiple
				)
  {
    //  I.  Application validity check:

    //  II.  Attempt to advance 'heapRunPtr_':
    char	tempBuffer[256];
    size_t	toAdvance	= multiple - getNumBytes() % multiple;

    if  ( (toAdvance == multiple)  ||  (toAdvance == 0) )
    {
      //  Nothing to do:
    }
    else
    if  (toAdvance <= multiple)
    {
      memset(tempBuffer,'\0',toAdvance);
      append(tempBuffer,toAdvance);      
    }
    else
    {
      uint32_t	smallAdvance;

      memset(tempBuffer,'\0',sizeof(tempBuffer));

      for  ( ;  toAdvance > 0;  toAdvance -= smallAdvance)
      {
        smallAdvance	= std::min(toAdvance,sizeof(tempBuffer));
        append(tempBuffer,smallAdvance);
      }
    }

    //  III.  Finished:
  }


  //  PURPOSE:  To write() the data in '*this' concerning to file descriptor
  //		'fd' with file path 'filePathCPtr'.  No return value.
  void		WriterBuffer::write
				(int		fd,
				 const char*	filePathCPtr
				)
  {
    //  I.  Application validity check:

    //  II.  write() data to 'fd':
    size_t	numBytesWritten	= 0;

    while  (numBytesWritten < getNumBytes())
    {
      ssize_t	result	= ::write(fd,
				  numBytesWritten+getDataPtr(),
	  			  getNumBytes() - numBytesWritten
				 );

      if  (result < 0)
      {
	throw "Error writing to file";
      }

      numBytesWritten	+= result;
    }

    //  III.  Finished:
  }


  //  PURPOSE:  To return a reservation of 'numBytes' bytes to be written to
  //	later.
  ReservedVarSizedBufferSpace
		WriterBuffer::reserve
				(size_t		numBytes
				)
  {
    //  I.  Application validity check:

    //  II.  Reserve bytes:
    //  II.A.  Make instance that remembers where memory is:
    ReservedVarSizedBufferSpace
	returnMe	= ReservedVarSizedBufferSpace
				(heapRunPtr_ - beginHeapPtr_,
				 numBytes
				);

    //  II.B.  Reserve 'numBytes' on heap:
    if  (numBytes <= sizeof(uint64_t))
    {
      uint64_t	buffer	= 0x0ull;

      append((const char*)&buffer,numBytes);
    }
    else
    {
      char	buffer[MAX_TINY_ARRAY_LEN];

      memset(buffer,'\0',MAX_TINY_ARRAY_LEN);

      for  ( ; numBytes > MAX_TINY_ARRAY_LEN;  numBytes -= MAX_TINY_ARRAY_LEN)
      {
	append(buffer,MAX_TINY_ARRAY_LEN);
      }

      append(buffer,numBytes);
    }

    //  III.  Finished:
    return(returnMe);
  }
