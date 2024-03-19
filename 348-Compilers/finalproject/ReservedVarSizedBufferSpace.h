/*-------------------------------------------------------------------------*
 *---									---*
 *---		ReservedVarSizedBufferSpace.h				---*
 *---									---*
 *---	    This file declares a class that represents a region in a	---*
 *---	ConstContentOrVarSizedBuffer heap buffer to be reserved and	---*
 *---	written into later.						---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 9a		2022 February 14	Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

  class	ReservedVarSizedBufferSpace
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold the offset in the ConstContentOrVarSizedBuffer
    //		instance of where the reserved space should be.
    size_t			offset_;

    //  PURPOSE:  To hold the length of the reserved space.
    size_t			len_;

    //  PURPOSE:  To hold the index to advance, starting at 'offset_', when
    //		writing.
    size_t			runIndex_;

    //  II.  Disallowed auto-generated methods:
    //  No default constructor
    ReservedVarSizedBufferSpace	();

  protected :
    //  III.  Protected methods:
    //  PURPOSE:  To return the length of the reserved space.  No return value.
    size_t	getLength	()
				const
				{ return(len_); }

    //  PURPOSE:  To return the index to advance, starting at 'offset_', when
    //		writing.  No return value.
    size_t	getRunIndex  	()
				const
				{ return(runIndex_); }

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this' to index 'newOffset' as the place to
    //		reserve 'newLen' bytes in a ConstContentOrVarSizedBuffer
    //		instance to write to later.  No return value.
    ReservedVarSizedBufferSpace	(size_t		newOffset,
				 size_t		newLen
				) :
				offset_(newOffset),
				len_(newLen),
				runIndex_(newOffset)
				{ }

    //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
    ReservedVarSizedBufferSpace	(const ReservedVarSizedBufferSpace&	source
				) :
				offset_(source.getOffset()),
				len_(source.getLength()),
				runIndex_(source.getRunIndex())
				{ }

    //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
    //		'source', and return a reference to '*this'.
    ReservedVarSizedBufferSpace&
		operator=	(const ReservedVarSizedBufferSpace&
					source
				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				  {
				    return(*this);
				  }

				  //  II.  Release resources of '*this':

				  //  III.  Copy 'source':
				  offset_	= source.getOffset();
				  len_		= source.getLength();
				  runIndex_	= source.getRunIndex();

				  //  IV.  Finished:
				  return(*this);
				}

    //  PURPOSE:  To release the resources of '*this'.  No parameters.
    //		No return value.
    ~ReservedVarSizedBufferSpace()
				{ }

    //  V.  Accessor(s):
    //  PURPOSE:  To return the offset in the ConstContentOrVarSizedBuffer
    //		instance of where the reserved space should be.  No return
    //		value.
    size_t	getOffset 	()
				const
				{ return(offset_); }

    //  VI.  Mutator(s):

    //  VII.  Methods that do main and misc. work of class:
    //  PURPOSE:  To give away 'len' bytes of '*this' reservation.  Returns
    //		index at which the reservation starts.  Updates '*this' so
    //		that reservation start 'len' bytes further along.
    size_t	giveAway	(size_t		len
				)
				{
				  //  I.  Application validity check:
				  if  ( (getRunIndex() + len)	>
				      	(getOffset() + getLength())
				      )
				  {
				    throw 
					"Insufficient reserved space"
					" in ReservedVarSizedBufferSpace";
				  }

				  //  II.  Give away '*this' reservation:
				  //  II.A.  Remember index to give:
				  size_t   returnMe	 = getRunIndex();

				  //  II.B.  Update '*this' after giving:
				  runIndex_		+= len;

				  //  III.  Finished:
				  return(returnMe);
				}

  };
