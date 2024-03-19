/*-------------------------------------------------------------------------*
 *---									---*
 *---		InputCharStream.h					---*
 *---									---*
 *---	    This file defines a class that implements reading chars 	---*
 *---	from a file.							---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	-----	---*
 *---									---*
 *---	Version 9a		2024 March 17		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  PURPOSE:  To implement InputCharStream where chars come from a file.
class	FileInputCharStream
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the file.
  FILE*				filePtr_;

  //  PURPOSE:  To hold the filepath.
  char				filepath_[COMMON_ARRAY_LEN];

  //  PURPOSE:  To hold the input.
  char				input_[COMMON_ARRAY_LEN];

  //  PURPOSE:  To hold where the cursor is.
  int				index_;

  //  PURPOSE:  To hold the line number.
  size_t			lineNum_;

  //  II.  Disallowed auto-generated methods:
  //  No default constructor:
  FileInputCharStream		()
				= delete;

  //  No copy constructor:
  FileInputCharStream		(const FileInputCharStream&
				)
				= delete;

  //  No copy assignment op:
  FileInputCharStream&
		operator=	(const FileInputCharStream&
				)
				= delete;

  //  III.  Protected methods:
protected :

public:
  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to read from 'newFilepathCPtr'.
  //	No return value.
  FileInputCharStream		(const char*	newFilepathCPtr
				) :
				filePtr_(fopen(newFilepathCPtr,"r")),
				index_(0),
				lineNum_(0)
  {
    if  ( (filePtr_ == NULL)			||
	  (fgets(input_,COMMON_ARRAY_LEN,filePtr_) == NULL)
	)
    {
      fprintf(stderr,"Cannot open %s\n",newFilepathCPtr);
      exit(EXIT_FAILURE);
    }

    lineNum_++;
    strncpy(filepath_,newFilepathCPtr,COMMON_ARRAY_LEN);
  }


  //  PURPOSE:  To release the resources of '*this'.  No parameters.
  //	No return value.
  ~FileInputCharStream		()
				{
				  fclose(filePtr_);
				}

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the current char, or '\0' if there are no more.
  //	No parameters.
  char		peek		()
  {
    if  (input_[index_] == '\0')
    {
      if  (fgets(input_,COMMON_ARRAY_LEN,filePtr_) == NULL)
      {
	return('\0');
      }

      lineNum_++;
      index_	= 0;
      return(peek());
    }

    return( input_[index_] );
  }


  //  PURPOSE:  To return 'true' if the next chars to return are equal to
  //	'cPtr', or 'false' otherwise.
  bool		isPeekEqualTo	(const char*	cPtr
  				)
				const
  {
    size_t	numBytesToCompare	= strlen(cPtr);

    return( strncmp(cPtr,input_+index_,numBytesToCompare) == 0 );
  }


  //  PURPOSE:  To return 'true' if at eof-of-input, or 'false' otherwise.
  bool		isAtEnd		()
				{ return(peek() == '\0'); }

  //  PURPOSE:  To advance to the next char (if not already at end).  No
  //	parameters.  No return value.
  void		advance		()
				{
				  if  (peek() != '\0')  index_++;
				}

  //  PURPOSE:  To get the current location in '*this'.
  std::string	getLocation	()
				const
				{
				  char	text[COMMON_ARRAY_LEN];

				  snprintf
					(text,COMMON_ARRAY_LEN,"line %lld of %s",
					 lineNum_,filepath_
				  	);
				  return(std::string(text));
				}

};
