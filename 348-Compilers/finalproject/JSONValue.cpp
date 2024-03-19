/*-------------------------------------------------------------------------*
 *---									---*
 *---		JSONValue.cpp						---*
 *---									---*
 *---	    This file defines members for classes for reading JSON	---*
 *---	text.  See https://www.json.org/.				---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	-----	---*
 *---									---*
 *---	Version 9a		2019 March 6		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"header.h"

char		commonCArray[COMMON_ARRAY_LEN];

  //  PURPOSE:  To tell the expected type to be returned by the key
  //	'JSON_TYPE_KEY' for a JSON msg intended for the
  //	Scienceomatic environment.
//  const
//  std::string	SOM_REQUEST_JSON_TYPE_VALUE_STR(SOM_REQUEST_JSON_TYPE_VALUE);
  


  //  PURPOSE:  To represent the occurence of EOF.
  JSONSyntacticElement
		JSONValue::Tokenizer::eof_static(EOF);


  //  PURPOSE:  To represent the occurence of begin curly brace.
  JSONSyntacticElement
		JSONValue::Tokenizer::beginCurlyBrace_static((int)BEGIN_JSON_BRACE);


  //  PURPOSE:  To represent the occurence of end curly brace.
  JSONSyntacticElement
		JSONValue::Tokenizer::endCurlyBrace_static((int)END_JSON_BRACE);


  //  PURPOSE:  To represent the occurence of begin square bracket.
  JSONSyntacticElement
		JSONValue::Tokenizer::
			beginSquareBracket_static((int)BEGIN_JSON_ARRAY);


  //  PURPOSE:  To represent the occurence of end square bracket.
  JSONSyntacticElement
		JSONValue::Tokenizer::endSquareBracket_static((int)END_JSON_ARRAY);


  //  PURPOSE:  To represent the occurence of comma.
  JSONSyntacticElement
		JSONValue::Tokenizer::comma_static((int)JSON_SEPARATOR);


  //  PURPOSE:  To represent the occurence of colon.
  JSONSyntacticElement
		JSONValue::Tokenizer::colon_static((int)JSON_MAPPER);


  //  PURPOSE:  To return a pointer to a JSONNumber representing the
  //  	number scanned from 'inputStream_' whose first char begins
  //	with 'c'.
  JSONValue*	JSONValue::Tokenizer::scanNumber
				(char	firstC
				)
  {
    //  I.  Application validity check:

    //  II.  Read number:
    WriterBuffer	text;

    //  YOUR CODE HERE

    //  III.  Finished:
    return( NULL );	//  CHANGE THAN NULL!
  }


  //  PURPOSE:  To return a pointer to a JSONValue representing the string
  //  	scanned from 'inputStream_' whose beginning QUOTE_CHAR has
  //	already been read.
  JSONValue*	JSONValue::Tokenizer::scanString
				()
  {
    //  I.  Application validity check:

    //  II.  Parse string:
    WriterBuffer	text;
    char		c;

    while  ( !inputStream_.isAtEnd() )
    {
      c	= inputStream_.peek();

      inputStream_.advance();

      if  (c == QUOTE_CHAR)
      {
        break;
      }
      else
      if  (c == '\\')
      {
        if  ( inputStream_.isAtEnd() )
	{
	  throw "Illegal escape sequence";
	}

	c	= inputStream_.peek();
      	inputStream_.advance();

	switch  (c)
	{
	case QUOTE_CHAR :
	  text	+= QUOTE_CHAR;
	  break;
	case '\\' :
	  text	+= '\\';
	  break;
	case '/' :
	  text	+= '/';
	  break;
	case 'b' :
	  text	+= '\b';
	  break;
	case 'f' :
	  text	+= '\f';
	  break;
	case 'n' :
	  text	+= '\n';
	  break;
	case 'r' :
	  text	+= '\r';
	  break;
	case 't' :
	  text	+= '\t';
	  break;
	default :
	  throw "Illegal char sequence";
	}

      }
      else
      {
        text	+= c;
      }
    }

    //  III.  Finished:
    if  (text == "true")
    {
      return(new JSONTrue());
    }

    if  (text == "false")
    {
      return(new JSONFalse());
    }

    if  (text == "null")
    {
      return(new JSONNull());
    }

    return(new JSONString(text.getDataPtr()));
  }


  //  PURPOSE:  To scan 'null' or 'true' or 'false' appearing outside of quotes.
  //	Return address of JSONValue instance corresponding to what was scanned.
  //	'c' tells the character already scanned.
  JSONValue*	JSONValue::Tokenizer::scanNullTrueFalse
				(char		c
				)
  {
    //  I.  Application validity check:

    //  II.  Scan text:
    WriterBuffer text;

    text	+= c;

    while  ( !inputStream_.isAtEnd() && isalpha(c = inputStream_.peek()) )
    {
      text	+= c;
      inputStream_.advance();
    }

    //  III.  Finished:
    if  (text == "true")
    {
      return(new JSONTrue());
    }

    if  (text == "false")
    {
      return(new JSONFalse());
    }

    if  (text == "null")
    {
      return(new JSONNull());
    }

    snprintf(commonCArray,COMMON_ARRAY_LEN,
	     "Unexpected non-quoted text '%s' while reading JSON",
	     text.getDataPtr()
	    );
    throw commonCArray;
  }


  //  PURPOSE:  To return a pointer representing a scanned JSONValue.
  //	No parameters.
  JSONValue*	JSONValue::Tokenizer::scanner
				()
  {
    //  I.  Application validity check:

    //  II.  Get next token:
    //  II.A.  Fast-forward past spaces:
    while  ( !inputStream_.isAtEnd() )
    {
      char	c = inputStream_.peek();

      inputStream_.advance();

      switch  (c)
      {
      case ' ' :
      case '\n' :
      case '\t' :
      case '\v' :
      case '\f' :
      case '\r' :
	continue;

      case '-' :
      case '+' :
      case '0' :
      case '1' :
      case '2' :
      case '3' :
      case '4' :
      case '5' :
      case '6' :
      case '7' :
      case '8' :
      case '9' :
	return(scanNumber(c));

      case 'n' :
      case 't' :
      case 'f' :
	return(scanNullTrueFalse(c));

      case QUOTE_CHAR :
	return(scanString());

      case BEGIN_JSON_BRACE :
	return(&beginCurlyBrace_static);

      case END_JSON_BRACE :
	return(&endCurlyBrace_static);

      case BEGIN_JSON_ARRAY :
	return(&beginSquareBracket_static);

      case END_JSON_ARRAY :
	return(&endSquareBracket_static);

      case JSON_SEPARATOR :
	return(&comma_static);

      case JSON_MAPPER :
	return(&colon_static);

      case '\0' :
	return(&eof_static);

      default :
	snprintf(commonCArray,COMMON_ARRAY_LEN,
		 "Unexpected char '%c' (ASCII = %d) while reading JSON",
		 c,c
		);
	throw commonCArray;
      }
    }

    //  III.  Finished:
    return(&eof_static);
  }


  //  PURPOSE:  To return the address of a JSONObject read from 'tokenizer'.
  JSONValue*	JSONValue::parseObject
				(Tokenizer&	tokenizer
				)
  {
    //  I.  Application validity check:

    //  II.  Parse the JSON object:
    WriterBuffer	key;
    JSONValue*		readPtr;
    JSONObject*		toReturn	= new JSONObject();

    //  YOUR CODE HERE

    //  III.  Finished:
    return(toReturn);
  }


  //  PURPOSE:  To return the address of JSONArray read from 'tokenizer'.
  JSONValue*	JSONValue::parseArray
				(Tokenizer&	tokenizer
				)
  {
    //  I.  Application validity check:

    //  II.  Parse the JSON array:
    JSONValue*	readPtr;
    JSONArray*	toReturn	= new JSONArray();

    //  YOUR CODE HERE

    //  III.  Finished:
    return(toReturn);
  }


  //  PURPOSE:  To return the address of the next JSONValue read from
  //	'tokenizer'.
  JSONValue*	JSONValue::parseValue
				(Tokenizer&	tokenizer
				)
  {
    //  I.  Application validity check:

    //  II.  Get the next JSON value from 'tokenizer':
    JSONValue*	readPtr	= tokenizer.advance();

    switch  (readPtr->getType())
    {
    case STRING_JSON :
    case NUMBER_JSON :
    case TRUE_JSON :
    case FALSE_JSON :
    case NULL_JSON :
    case EOF :
      break;

    case BEGIN_JSON_BRACE :
      return(parseObject(tokenizer));

    case BEGIN_JSON_ARRAY :
      return(parseArray(tokenizer));

    default :
      throw "Expected JSON value";
    }

    //  III.  Finished:
    return(readPtr);
  }


  //  PURPOSE:  To return the address of a JSONValue instance read from
  //	'sourceCPtr'.  Returns 'NULL' if no JSON value available.
  JSONValue*	JSONValue::factory
				(const char*	sourceCPtr
    				)
  {
    //  I.  Application validity check:

    //  II.  Read the JSON value from 'fd':
    Tokenizer	tokenizer(sourceCPtr);

    JSONValue*	valuePtr	= parseValue(tokenizer);

    //  III.  Finished:
    return( (valuePtr->getType() == EOF) ? NULL : valuePtr );
  }


  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //		return value.
  JSONValue::~JSONValue		()
  {
    //  I.  Application validity check:

    //  II.  Release resources:

    //  III.  Finished:
  }


  //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
  //		Quotes text if 'shouldQuoteText' == 'true'.
  void		JSONValue::serialize
				(WriterBuffer&
						buffer,
				 bool		shouldQuoteText	// = true
				)
				const
  {
    //  I.  Application validity check:
    throw "Attempt to serialize JSON object without useful content";
  }


  //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
  //		Quotes text if 'shouldQuoteText' == 'true'.
  void		JSONNumber::serialize
				(WriterBuffer&
						buffer,
				 bool		shouldQuoteText	// = true
				)
				const
  {
    //  I.  Application validity check:

    //  II.  Get string
    //  II.A.  Use 'text_' if already defined:
    if  ( (textCPtr_ != NULL)  &&  (*textCPtr_ != '\0') )
    {
      buffer += textCPtr_;
      return;
    }

    //  II.B.  Create text:
    char	text[MAX_TINY_ARRAY_LEN];

    if  (isInteger_)
    {
      snprintf(text,MAX_TINY_ARRAY_LEN,"%ld",getInteger());
    }
    else
    {
      snprintf(text,MAX_TINY_ARRAY_LEN,"%g",getFloat());
    }

    buffer += text;

    //  III.  Finished:
  }


  //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
  //		Quotes text if 'shouldQuoteText' == 'true'.
  void		JSONArray::serialize
				(WriterBuffer&
						buffer,
				 bool		shouldQuoteText	// = true
				)
				const
  {
    //  I.  Application validity check:

    //  II.  Compose string:
    size_t	length	= array_.size();

    buffer	+= BEGIN_JSON_ARRAY;

    for  (size_t index = 0;  index < length;  index++)
    {
      if  (index > 0)
      {
	buffer	+= JSON_SEPARATOR;
      }

      array_[index]->serialize(buffer,shouldQuoteText);
    } 

    buffer	+= END_JSON_ARRAY;

    //  III.  Finished:
  }


  //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
  //		return value.
  JSONObject::~JSONObject	()
  {
    //  I.  Application validity check:

    //  II.  Remove resources:
    JSONObjectIter	iter	= map_.begin();
    JSONObjectIter	end	= map_.end();
    JSONObjectIter	next;

    for  ( ;  iter != end;  iter = next)
    {
      char*	keyCPtr	= iter->first;

      next		= iter;
      next++;

      free(keyCPtr);
      delete(iter->second);
      map_.erase(iter);
    }

    //  III.  Finished:
  }


  //  PURPOSE:  To serialize '*this' and then return the corresponding text.
  //		Quotes text if 'shouldQuoteText' == 'true'.
  char*		JSONObject::giveAwayTextCPtr
	  			(bool		shouldQuoteText	// = true
		    		)
				const
  {
    //  I.  Application validity:
 
    //  II.  Create text to give away:
    WriterBuffer	buffer;

    serialize(buffer,shouldQuoteText);

    //  III.  Finished:
    return(strdup(buffer.getDataPtr()));
  }


  //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
  //		Quotes text if 'shouldQuoteText' == 'true'.
  void		JSONObject::serialize
				(WriterBuffer&
						buffer,
				 bool		shouldQuoteText	// = true
				)
				const
  {
    //  I.  Application validity check:

    //  II.  Compose string:
    bool		isFirstIter	= true;
    JSONObjectConstIter	iter		= map_.begin();
    JSONObjectConstIter	end		= map_.end();

    buffer	+= BEGIN_JSON_BRACE;

    for  ( ;  iter != end;  iter++)
    {
      if  (isFirstIter)
      {
	isFirstIter	= false;
      }
      else
      {
	buffer	+= JSON_SEPARATOR;
      }

      buffer	+= QUOTE_CHAR;
      buffer	+= iter->first;
      buffer	+= QUOTE_CHAR;
      buffer	+= JSON_MAPPER;
      iter->second->serialize(buffer,shouldQuoteText);
    } 

    buffer	+= END_JSON_BRACE;

    //  III.  Finished:
  }


  //  PURPOSE:  To add the mapping 'keyCPtr' => '*valuePtr' to '*this'.  No
  //		return value.
  void		JSONObject::add	(const char*	keyCPtr,
				 JSONValue*	valuePtr
				)
  {
    //  I.  Application validity check:

    //  II.  Insert 'keyCPtr' => 'valuePtr' in *this:
    //  II.A.  Look for existing mapping:
    char	keySpace[MAX_TINY_ARRAY_LEN];

    strncpy(keySpace,keyCPtr,MAX_TINY_ARRAY_LEN-1);
    keySpace[MAX_TINY_ARRAY_LEN-1]	= '\0';

    JSONObjectIter	iter		= map_.find(keySpace);

    if  (iter != map_.end())
    {
      delete(iter->second);
      iter->second		= valuePtr;
    }
    else
    {
      map_[strdup(keyCPtr)]	= valuePtr;
    }

    //  III.  Finished:
  }


//  PURPOSE:  To return a C-string for the purpose described by
//	'descriptionCPtr', either from the command line or 'stdin'.  If from
//	the command line then 'argIndex' tells where it should be in 'argv[]'.
//	'argc' tells how many arguments were on the command line and 'argv[]'
//	points to those arguments.
char*		getInput	(char*		inputCArray,
				 size_t		inputLen,
				 int		argc,
				 char*		argv[],
				 const char*	descriptionCPtr,
				 size_t		argIndex
				)
{
  //  I.  Application validity check:

  //  II.  Get input:
  //  II.A.  Handle command line input:
  if  (argc > argIndex)
  {
    strncpy(inputCArray,argv[argIndex],inputLen);
    return(inputCArray);
  }

  //  II.B.  Handle keyboard input:
  char*	cPtr;

  printf("%s: ",descriptionCPtr);
  fgets(inputCArray,inputLen,stdin);

  cPtr	= strchr(inputCArray,'\n');

  if  (cPtr != NULL)
  {
    *cPtr	= '\0';
  }

  //  III.  Finished:
  return(inputCArray);
}


int		main		(int		argc,
				 char*		argv[]
				)
{
  //  I.  Application validity check:

  //  II.  Attempt to do translation:
  //  II.A.  Get file paths:
  char	inputFilePath[COMMON_ARRAY_LEN];
  char	outputFilePath[COMMON_ARRAY_LEN];

  getInput( inputFilePath,COMMON_ARRAY_LEN,argc,argv, "Input Json filepath",1);
  getInput(outputFilePath,COMMON_ARRAY_LEN,argc,argv,"Output Json filepath",2);

  //  II.B.  Attempt to translate:
  int	status	= EXIT_SUCCESS;

  try
  {
    int			outFd;
    WriterBuffer	buffer;
    JSONValue*		elementPtr;

    if  ( (outFd = open(outputFilePath,O_WRONLY|O_CREAT|O_TRUNC,0660)) < 0 )
    {
      fprintf
	(stderr,"Cannot open output file %s: %s.\n",
	 outputFilePath,strerror(errno)
	);
      exit(EXIT_FAILURE);
    }

    elementPtr	= JSONValue::factory(inputFilePath);

    elementPtr->serialize(buffer);
    buffer.write(outFd,outputFilePath);
    write(outFd,"\n",1);
    close(outFd);
  }
  catch  (const char*	errorCPtr)
  {
    fprintf(stderr,"%s\n",errorCPtr);
    status	= EXIT_FAILURE;
  }
  catch  (std::string	errorStr)
  {
    fprintf(stderr,"%s\n",errorStr.c_str());
    status	= EXIT_FAILURE;
  }

  //  III.  Finished:
  return(status);
}
