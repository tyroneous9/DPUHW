/*-------------------------------------------------------------------------*
 *---									---*
 *---		JSONValue.h						---*
 *---									---*
 *---	    This file declares classes for reading JSON text.		---*
 *---	See https://www.json.org/.					---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	-----	---*
 *---									---*
 *---	Version 9a		2019 March 5		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

  //  PURPOSE:  To distinguish among the derived classes of JSONValue.
  typedef	enum
		{
		  STRING_JSON,
		  NUMBER_JSON,
		  TRUE_JSON,
		  FALSE_JSON,
		  NULL_JSON,
		  ARRAY_JSON,
		  OBJECT_JSON,
		  LITERAL_JSON,

		  LO_LEGAL_JSON	= STRING_JSON,
		  HI_LEGAL_JSON	= OBJECT_JSON
		}
		json_ty;


  //  PURPOSE:  To return 'true' if 'json' is a legal value in 'json_ty' or
  //  	'false' otherwise.
  inline
  bool		isLegalJsonType	(int	json
  				)
				{
				  return( (json >= LO_LEGAL_JSON) &&
				  	  (json <= HI_LEGAL_JSON)
					);
				}

  class		JSONSyntacticElement;


  //  PURPOSE:  To serve as the base class of all JSON classes.
  class	JSONValue
  {
    //  0.  Internal classes:

    //  PURPOSE:  To return the next token.
    class	Tokenizer
    {
      //  I.  Member vars:
      //  PURPOSE:  To represent the occurence of EOF.
      static
      JSONSyntacticElement	eof_static;

      //  PURPOSE:  To represent the occurence of begin curly brace.
      static
      JSONSyntacticElement	beginCurlyBrace_static;

      //  PURPOSE:  To represent the occurence of end curly brace.
      static
      JSONSyntacticElement	endCurlyBrace_static;

      //  PURPOSE:  To represent the occurence of begin square bracket.
      static
      JSONSyntacticElement	beginSquareBracket_static;

      //  PURPOSE:  To represent the occurence of end square bracket.
      static
      JSONSyntacticElement	endSquareBracket_static;

      //  PURPOSE:  To represent the occurence of comma.
      static
      JSONSyntacticElement	comma_static;

      //  PURPOSE:  To represent the occurence of colon.
      static
      JSONSyntacticElement	colon_static;

      //  PURPOSE:  To do the low-level work of getting the next char
      FileInputCharStream	inputStream_;

      //  PURPOSE:  To hold the address of the last parsed JSONValue.
      JSONValue*		lastParsedPtr_;

      //  II.  Disallowed auto-generated methods:
      //  No default constructor:
      Tokenizer			();

      //  No copy constructor:
      Tokenizer			(const Tokenizer&
				);

      //  No copy assignment op:
      Tokenizer&
		operator=	(const Tokenizer&
				);

    protected :
      //  III.  Protected:
      //  PURPOSE:  To return a pointer to a JSONNumber representing the
      //  	number scanned from 'inputStream_' whose first char begins
      //	with 'c'.
      JSONValue*
		scanNumber	(char	firstC
				);

      //  PURPOSE:  To return a pointer to a JSONValue representing the string
      //  	scanned from 'inputStream_' whose beginning QUOTE_CHAR has
      //	already been read.
      JSONValue*
		scanString	();

      //  PURPOSE:  To scan 'null' or 'true' or 'false' appearing outside of
      //	quotes.  Return address of JSONValue instance corresponding to
      //	what was scanned.  'c' tells the character already scanned.
      JSONValue*
		scanNullTrueFalse
				(char		c
				);

      //  PURPOSE:  To return a pointer representing a scanned JSONValue.
      //	No parameters.
      JSONValue*
		scanner		();

    public :
      //  IV.  Constructor(s):
      //  PURPOSE:  To initialize '*this' to read JSON tokens from C-string
      //	'sourceCPtr'.  No return value.
      Tokenizer			(const char*	sourceCPtr
				) :
				inputStream_(sourceCPtr),
				lastParsedPtr_(NULL)
				{ }

      //  PURPOSE:  To release the resources of '*this'.  No parameters.
      //	No return value.
      ~Tokenizer		()
				{ }

      //  V.  Accessors:

      //  VI.  Mutators:

      //  VII.  Methods that do main and misc work of class:
      //  PURPOSE:  To return an integer to identity the type of the current
      //	token in the input stream.  No parameters.
      int	peek		()
      				{
				  if  (lastParsedPtr_ == NULL)
				    lastParsedPtr_	= scanner();

				  return(lastParsedPtr_->getType());
				}

      //  PURPOSE:  To return the pointer to the old JSONValue that was at the
      //	front of the symbol stream, and then to internally advance to
      //	the next JSONValue instance (if not already at the end).  No
      //	parameters.
      JSONValue*
		advance		()
				{
				  JSONValue* toReturn
						  = (lastParsedPtr_ == NULL)
				  	     	    ? scanner()
						    : lastParsedPtr_;

				  lastParsedPtr_  = scanner();
				  return(toReturn);
				}

    };

    //  I.  Member vars:

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:
    //  PURPOSE:  To return the address of JSONObject read from 'tokenizer'.
    static
    JSONValue*	parseObject	(Tokenizer&	tokenizer
				);

    //  PURPOSE:  To return the address of JSONArray read from 'tokenizer'.
    static
    JSONValue*	parseArray	(Tokenizer&	tokenizer
				);

    //  PURPOSE:  To return the address of the next JSONValue read from
    //	'tokenizer'.
    static
    JSONValue*	parseValue	(Tokenizer&	tokenizer
				);

    //  PURPOSE:  To ensure that 'typeValueCPtr' matches the value for key
    //		'JSON_TYPE_KEY_STR' read in 'valuePtr'.  Throws heap-
    //		allocated address of GeneralSyntaxException instance if
    //		either there is no value to key 'JSON_TYPE_KEY_STR', or
    //		if the value mis-matches 'typeValueCPtr'.
    static
    void	checkType	(const char*	typeValueCPtr,
  				 JSONValue*	valuePtr
				);

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this'.  No parameters.  No return value.
    JSONValue			( )
				{ }

    //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
    JSONValue			(const JSONValue&	source
				)
				{ }

    //  PURPOSE:  To release the resources of '*this', make '*this' a copy of
    //		'source', and to return a reference to '*this'.
    JSONValue&	operator=	(const JSONValue&	source
				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				  {
				    return(*this);
				  }

				  //  II.  Release resources:

				  //  III.  Copy 'source':

				  //  IV.  Finished:
				  return(*this);
				}

    //  PURPOSE:  To return the address of a JSONValue instance read from
    //		'sourceCPtr'.  Returns 'NULL' if no JSON value available.
    static
    JSONValue*	factory		(const char*	sourceCPtr
    				);

    //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
    //		return value.
    virtual
    ~JSONValue			();

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    virtual
    int		getType		()
				const
				= 0;

    //  PURPOSE:  To return the address to the parsed text.
    virtual
    const char*	getTextCPtr 	()
				const
				{ return(NULL); }

    //  PURPOSE:  To return 'true' if '*this' is an instance of a primitive
    //		class, i.e. instances of the class only a single value, and
    //		are neither composites nor data-structures with other parts.
    virtual
    bool	getIsPrimitive	()
				const
				{ return(true); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    virtual
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const;

    //  PURPOSE:  To return the length of '*this' array.  No parameters.
    virtual
    size_t	getLength	()
				const
				{ return(0); }

    //  PURPOSE:  To return the 'i'-th item in '*this' array, or 'NULL' if it
    //  	is out-of-range.
    virtual
    const JSONValue*
		getElement	(size_t		i
				)
				const
				{ return(NULL); }

    //  PURPOSE:  To return the value to which 'key' maps '*this', or 'NULL'
    //  	if 'keyCPtr' maps to no value.
    virtual
    const JSONValue*
		getElement	(const char*	keyCPtr
				)
				const
				{ return(NULL); }

    //  PURPOSE:  To return the integer implicit by 
    virtual
    int64_t
		getInteger	()
				const
				{ return(0); }

    //  PURPOSE:  To return the float 
    virtual
    double	getFloat 	()
				const
				{ return(0.0); }

    //  PURPOSE:  To set 'integer' to the integer in '*this' if '*this'
    //		represents an integer, or to set 'real' to the floating pt
    //		number in '*this' if '*this' represents a floating pt number.
    //		Returns 'true' if '*this' represents a float or 'false'
    //		otherwise.
    virtual
    bool	isInteger	(int64_t&	integer,
    				 double&	real
				)
				const
				{
				  real	= getFloat();
				  return(false);
				}

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent a JSON number.
  class	JSONNumber : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold the text of the parsed number.
    char*			textCPtr_;

    //  PURPOSE:  To hold the integer represented by '*this', if '*this'
    //		indeed represents an integer.  Results are undefined otherwise.
    int64_t		integer_;

    //  PURPOSE:  To hold the floating pt number represented by '*this', if
    //		'*this' indeed represents a float.  Results are undefined
    //		otherwise.
    double			float_;

    //  PURPOSE:  To hold 'true' if 'text_' represents an integer, or 'false'
    //		otherwise.
    bool			isInteger_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To note that '*this' number-representing JSON value has text
    //		'newText' representing integer 'newInteger'.  No return value.
    JSONNumber			(const char*	newTextCPtr,
				 int64_t	newInteger
				) :
				JSONValue(),
				textCPtr_(strdup(newTextCPtr)),
				integer_(newInteger),
				float_(0.0),
				isInteger_(true)
				{ }

    //  PURPOSE:  To note that '*this' number-representing JSON value has text
    //		'newText' representing floating pt number 'newFloat'.  No
    //		return value.
    JSONNumber			(const char*	newTextCPtr,
				 double	newFloat
				) :
				JSONValue(),
				textCPtr_(strdup(newTextCPtr)),
				integer_(0),
				float_(newFloat),
				isInteger_(false)
				{ }

    //  PURPOSE:  To note that '*this' number-representing JSON value has text
    //		'newText' representing integer 'newInteger'.  No return value.
    JSONNumber			(int64_t	newInteger
				) :
				JSONValue(),
				textCPtr_(NULL),
				integer_(newInteger),
				float_(0.0),
				isInteger_(true)
				{
				  char	numberText[MAX_TINY_ARRAY_LEN];

				  snprintf
					(numberText,MAX_TINY_ARRAY_LEN,
					 "%lld",newInteger
					);
				  textCPtr_	= strdup(numberText);
				}

    //  PURPOSE:  To note that '*this' number-representing JSON value has text
    //		'newText' representing floating pt number 'newFloat'.  No
    //		return value.
    JSONNumber			(double	newFloat
				) :
				JSONValue(),
				textCPtr_(NULL),
				integer_(0),
				float_(newFloat),
				isInteger_(false)
				{
				  char	numberText[MAX_TINY_ARRAY_LEN];

				  snprintf
					(numberText,MAX_TINY_ARRAY_LEN,
					 "%g",newFloat
					);
				  textCPtr_	= strdup(numberText);
				}

    //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
    //		return value.
    ~JSONNumber			()
				{
				  free(textCPtr_);
				}

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(NUMBER_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const;

    //  PURPOSE:  To return the address to the parsed text.
    const char*	getTextCPtr 	()
				const
				{ return(textCPtr_); }

    //  PURPOSE:  To return the integer implicit by 
    int64_t	getInteger	()
				const
				{ return(integer_); }

    //  PURPOSE:  To return the float 
    double	getFloat 	()
				const
				{ return(float_); }

    //  PURPOSE:  To set 'integer' to the integer in '*this' if '*this'
    //		represents an integer, or to set 'real' to the floating pt
    //		number in '*this' if '*this' represents a floating pt number.
    //		Returns 'true' if '*this' represents a float or 'false'
    //		otherwise.
    bool	isInteger	(int64_t&	integer,
    				 double&	real
				)
				const
				{
				  if  (isInteger_)
				  {
				    integer	= getInteger();
				    return(true);
				  }

				  real	= getFloat();
				  return(false);
				}

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent a JSON string.
  class	JSONString : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To point to the parsed text.
    char*			textCPtr_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To note that '*this' string-representing JSON value has text
    //		'newTextCPtr'.
    JSONString			(const char*	newTextCPtr
				) :
				JSONValue(),
				textCPtr_(strdup(newTextCPtr))
				{ }

    //  PURPOSE:  To release the resources of '*this'.  No parameters.
    //		No return value.
    ~JSONString			()
				{
				  free(textCPtr_);
				}

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(STRING_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const
				{
				  if  (shouldQuoteText)
				  {
				    buffer.append(QUOTE_CHAR);
				    buffer.append(textCPtr_);
				    buffer.append(QUOTE_CHAR);
				  }
				  else
				  {
				    buffer.append(textCPtr_);
				  }
				}

    //  PURPOSE:  To return the address to the parsed text.
    const char*	getTextCPtr 	()
				const
				{ return(textCPtr_); }

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent the JSON value "true"
  class	JSONTrue : public JSONValue
  {
    //  I.  Member vars:

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To representing 'true'.  No parameters.  No return value.
    JSONTrue			() :
				JSONValue()
				{ }

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(TRUE_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const
				{
				  if  (shouldQuoteText)
				  {
				    buffer.append("\"true\"");
				  }
				  else
				  {
				    buffer.append("true");
				  }
				}

    //  PURPOSE:  To return the address to the parsed text.
    const char*	getTextCPtr 	()
				const
				{ return("true"); }

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent the JSON value "false"
  class	JSONFalse : public JSONValue
  {
    //  I.  Member vars:

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To representing 'false'.  No parameters.  No return value.
    JSONFalse			() :
				JSONValue()
				{ }

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(FALSE_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const
				{
				  if  (shouldQuoteText)
				  {
				    buffer.append("\"false\"");
				  }
				  else
				  {
				    buffer.append("false");
				  }
				}

    //  PURPOSE:  To return the address to the parsed text.
    const char*	getTextCPtr 	()
				const
				{ return("false"); }

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent the JSON value "null"
  class	JSONNull : public JSONValue
  {
    //  I.  Member vars:

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To representing 'null'.  No parameters.  No return value.
    JSONNull			() :
				JSONValue()
				{ }

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(NULL_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const
				{
				  if  (shouldQuoteText)
				  {
				    buffer.append("\"null\"");
				  }
				  else
				  {
				    buffer.append("null");
				  }
				}

    //  PURPOSE:  To return the address to the parsed text.
    const char*	getTextCPtr 	()
				const
				{ return("null"); }

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To represent JSON arrays.
  class	JSONArray : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold the components of the array.
    std::vector<JSONValue*>	array_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this' as an empty array.  No parameters.
    //		No return value.
    JSONArray			() :
				JSONValue()
				{ }

    //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
    //		return value.
    ~JSONArray			()
				{
				  size_t	limit	= array_.size();

				  for  (size_t i = 0;  i < limit;  i++)
				  {
				    delete(array_[i]);
				  }
				}

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(ARRAY_JSON); }

    //  PURPOSE:  To return 'true' if '*this' is an instance of a primitive
    //		class, i.e. instances of the class only a single value, and
    //		are neither composites nor data-structures with other parts.
    bool	getIsPrimitive	()
				const
				{ return(false); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const;

    //  PURPOSE:  To return the length of '*this' array.  No parameters.
    size_t	getLength	()
				const
				{ return(array_.size()); }

    //  PURPOSE:  To return the 'i'-th item in '*this' array, or 'NULL' if it
    //  	is out-of-range.
    const JSONValue*
		getElement	(size_t		i
				)
				const
				{
				  return( (i >= getLength())
					  ? NULL
					  : array_[i]
					);
				}

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:
    //  PURPOSE:  To add 'jsonElePtr' to the end of '*this'.  No return
    //		value.
    void	add		(JSONValue*	jsonElePtr
				)
				{
				  array_.push_back(jsonElePtr);
				}

  };


  //  PURPOSE:  To represent the type of non-const iterators over values in
  //  	JSONObject instances.
  typedef	std::map<char*,JSONValue*,CStringComp>::iterator
  		JSONObjectIter;

  //  PURPOSE:  To represent the type of const iterators over values in
  //  	JSONObject instances.
  typedef	std::map<char*,JSONValue*,CStringComp>::const_iterator
  		JSONObjectConstIter;

  //  PURPOSE:  To represent JSON objects.
  class	JSONObject : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold map.
    std::map<char*,JSONValue*,CStringComp>
				map_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To represent an object about which initially nothing is
    //		known.  No parameters.  No return value.
    JSONObject			() :
				JSONValue()
				{ }

    //  PURPOSE:  To release the resources of '*this'.  No parameters.  No
    //		return value.
    ~JSONObject			();

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(OBJECT_JSON); }

    //  PURPOSE:  To serialize '*this' and then return the corresponding text.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    char*	giveAwayTextCPtr(bool		shouldQuoteText	= true
		    		)
				const;

    //  PURPOSE:  To return 'true' if '*this' is an instance of a primitive
    //		class, i.e. instances of the class only a single value, and
    //		are neither composites nor data-structures with other parts.
    bool	getIsPrimitive	()
				const
				{ return(false); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const;

    //  PURPOSE:  To return the value to which 'keyCPtr' maps '*this',
    //  	or 'NULL' if 'keyCPtr' maps to no value.
    const JSONValue*
		getElement	(const char*	keyCPtr
				)
				const
				{
				  std::map<char*,JSONValue*,CStringComp>::
					const_iterator
					iter = map_.find((char*)keyCPtr);

				  return( (iter == map_.end())
					  ? NULL
					  : iter->second
					);
				}

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:
    //  PURPOSE:  To add the mapping 'keyCPtr' => '*valuePtr' to '*this'.  No
    //		return value.
    void	add		(const char*	keyCPtr,
				 JSONValue*	valuePtr
				);

    //  PURPOSE  To return an iterator to the first element of '*this'.
    std::map<char*,JSONValue*,CStringComp>::const_iterator
		getBegin	()
				const
				{ return(map_.begin()); }

    //  PURPOSE  To return an iterator to the just past the last element of
    //		'*this'.
    std::map<char*,JSONValue*,CStringComp>::const_iterator
		getEnd		()
				const
				{ return(map_.end()); }

  };


  //  PURPOSE:  To represent JSON that already is in a string form.
  class JSONLiteral : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To point to the literal already JSON text.
    char*			literalTextCPtr_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this' to hold literal value 'literalText'.
    //		No return value.
    JSONLiteral			(const char*	literalTextCPtr
				) :
				JSONValue(),
				literalTextCPtr_(strdup(literalTextCPtr))
				{ }

    //  PURPOSE:  To release the resources of '*this'.  No parameters.
    //		No return value.
    ~JSONLiteral		()
    				{
				  free(literalTextCPtr_);
				}

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(LITERAL_JSON); }

    //  PURPOSE:  To build in 'buffer' the string representation of '*this'.
    //		Quotes text if 'shouldQuoteText' == 'true'.
    void	serialize	(WriterBuffer&	buffer,
				 bool		shouldQuoteText	= true
				)
				const
				{
				  buffer.append(literalTextCPtr_);
				}

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc work of class:

  };


  //  PURPOSE:  To represent syntactic elements, but not JSON values.
  class	JSONSyntacticElement : public JSONValue
  {
    //  I.  Member vars:
    //  PURPOSE:  To hold an integer representation of the element.
    int		syntacticElement_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To represent the JSON syntatic element indexed by
    //		'newSyntacticElement'.
    JSONSyntacticElement	(int		newSyntacticElement
				) :
				JSONValue(),
				syntacticElement_(newSyntacticElement)
				{ }

    //  V.  Accessors:
    //  PURPOSE:  To return the 'json_ty' or 'char' or 'int' value
    //		corresponding to the identity of '*this'.  No parameters.
    int		getType		()
				const
				{ return(syntacticElement_); }

    //  VI.  Mutators:

    //  VII.  Methods that do main and misc. work of class:

  };


  //  PURPOSE:  To define a path (a sequence of string attributes and/or
  //	integer indices) from root JSONValue to an internal node (e.g. leaf)
  class		JSONPath
  {
    //  0.  Internal classes:
    //  PURPOSE:  To serve as the base class of both 'IntegerIndex' and
    //		'StringIndex'.
    class	Index
    {
      //  I.  Member vars:

      //  II.  Disallowed auto-generated methods:

    protected :
      //  III.  Protected methods:

    public :
      //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
      //  PURPOSE:  To initialize '*this'.  No parameters.  No return value.
      Index			()
				{ }

      //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
      Index			(const Index&	source
				)
				{ }

      //  PURPOSE:  To release the resources of '*this', make '*this' a copy
      //	of 'source', and return a reference to '*this'.
      Index&	operator=	(const Index&	source
				)
				{
				  //  I.  Application validity check:
				  if  (this == &source)
				  {
				    return(*this);
				  }

				  //  II.  Release resources:

				  //  III.  Copy 'source':

				  //  IV.  Finished:
				  return(*this);
				}

      //  PURPOSE:  To release the resources of '*this'.  No parameters.
      //	No return value.
      virtual
      ~Index			()
				= 0;

      //  V.  Accessors:

      //  VI.  Mutators:

      //  VII.  Methods that do main and misc work of class:
      //  PURPOSE:  To return the result of following '*sourcePtr' indexed
      //	by the index of '*this'.
      virtual
      const JSONValue*
		follow		(const JSONValue*	sourcePtr
				)
				= 0;

      //  PURPOSE:  To return a copy of '*this'.  No parameters.
      virtual
      Index*	copy		()
      				= 0;

    };


    //  PURPOSE:  To serve as an index into JSONArray.
    class	IntegerIndex : public Index
    {
      //  I.  Member vars:
      //  PURPOSE: To hold the index stored at '*this'.
      size_t			index_;

      //  II.  Disallowed auto-generated methods:
      //  No default constructor:
      IntegerIndex		();

    protected :
      //  III.  Protected methods:

    public :
      //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
      //  PURPOSE:  To initialize '*this' to follow index 'newIndex'.  No
      //	return value.
      IntegerIndex		(size_t		newIndex
				) :
      				Index(),
				index_(newIndex)
				{ }

      //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
      IntegerIndex		(const IntegerIndex&	source
				) :
      				Index(source),
				index_(source.getIndex())
				{ }

      //  PURPOSE:  To release the resources of '*this', make '*this' a copy
      //	of 'source',  and return a reference to '*this'.
      IntegerIndex&
		operator=	(const IntegerIndex&	source
				)
				{
				  //  I.  Applicability validity check:
				  if  (this == &source)
				  {
				    return(*this);
				  }

				  //  II.  Release resources:
				  *(Index*)this = source;

				  //  III.  Copy 'source':
				  index_    = source.getIndex();

				  //  IV.  Finished:
				  return(*this);
				}

      //  PURPOSE:  To release the resources of '*this'.  No parameters.
      //	No return value.
      ~IntegerIndex		()
				{ }

      //  V.  Accessors:
      //  PURPOSE:  To return the index stored at '*this'.  No parameters.
      size_t	getIndex	()
				const
				{ return(index_); }

      //  VI.  Mutators:

      //  VII.  Methods that do main and misc work of class:
      //  PURPOSE:  To return the result of following '*sourcePtr' indexed
      //	by the index of '*this'.
      const JSONValue*
		follow		(const JSONValue*	sourcePtr
				)
				{
				  return(sourcePtr->getElement(getIndex()));
				}

      //  PURPOSE:  To return a copy of '*this'.  No parameters.
      Index*	copy		()
      				{ return(new IntegerIndex(*this)); }

    };


    //  PURPOSE:  To serve as an index into JSONObject.
    class	StringIndex : public Index
    {
      //  I.  Member vars:
      //  PURPOSE: To point to the index stored at '*this'.
      char*			indexCPtr_;

      //  II.  Disallowed auto-generated methods:
      //  No default constructor:
      StringIndex		();

    protected :
      //  III.  Protected methods:

    public :
      //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
      //  PURPOSE:  To initialize '*this' to follow index 'newIndexCPtr'.
      //	No return value.
      StringIndex		(const char*	newIndexCPtr
				) :
      				Index(),
				indexCPtr_(strdup(newIndexCPtr))
				{ }

      //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
      StringIndex		(const StringIndex&	source
				) :
				Index(source),
				indexCPtr_(strdup(source.getIndexCPtr()))
				{ }

      //  PURPOSE:  To release the resources of '*this', make '*this' a copy
      //	of 'source',  and return a reference to '*this'.
      StringIndex&
		operator=	(const StringIndex&	source
				)
				{
				  //  I.  Applicability validity check:
				  if  (this == &source)
				  {
				    return(*this);
				  }

				  //  II.  Release resources:
				  *(Index*)this = source;

				  //  III.  Copy 'source':
				  indexCPtr_    = strdup(source.getIndexCPtr());

				  //  IV.  Finished:
				  return(*this);
				}

      //  PURPOSE:  To release the resources of '*this'.  No parameters.
      //	No return value.
      ~StringIndex		()
				{ free(indexCPtr_);	}

      //  V.  Accessors:
      //  PURPOSE:  To return the index stored at '*this'.  No parameters.
      const char*
		getIndexCPtr	()
				const
				{ return(indexCPtr_); }

      //  VI.  Mutators:

      //  VII.  Methods that do main and misc work of class:
      //  PURPOSE:  To return the result of following '*sourcePtr' indexed
      //	by the index of '*this'.
      const JSONValue*
		follow		(const JSONValue*	sourcePtr
				)
				{
				  return(sourcePtr->getElement(getIndexCPtr())
					);
				}

      //  PURPOSE:  To return a copy of '*this'.  No parameters.
      Index*	copy		()
      				{ return(new StringIndex(*this)); }

    };


    //  I.  Member vars:
    //  PURPOSE:  To keep track of a path thru a JSONValue tree.
    std::vector<Index*>		pathDs_;

    //  II.  Disallowed auto-generated methods:

  protected :
    //  III.  Protected methods:

  public :
    //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
    //  PURPOSE:  To initialize '*this' to an empty path.  No parameters.
    //		No return value.
    JSONPath			() :
				pathDs_()
				{ }

    //  PURPOSE:  To make '*this' a copy of 'source'.  No return value.
    JSONPath			(const JSONPath&	source
				);

    //  PURPOSE:  To release the resources of '*this',  make '*this' a copy
    //		of 'source', and return a reference to '*this'.
    JSONPath&	operator=	(const JSONPath&	source
    				);

    //  PURPOSE:  To release the resources of '*this'.  No parameters.
    //		No return value.
    ~JSONPath			();

    //  V.  Accessors:
    //  PURPOSE:  To return the length of '*this' path.  No parameters.
    size_t	getLength	()
				const
				{ return(pathDs_.size()); }

    //  VI.  Mutators:
    //  PURPOSE:  To add integer index 'index' to the end of '*this' path.
    //		No return value.
    void	addInt		(size_t		index
    				)
				{
				  pathDs_.push_back(new IntegerIndex(index));
				}

    //  PURPOSE:  To add string index pointed to by 'indexCPtr' to the end of
    //		'*this' path.  No return value.
    void	addStr		(const char*	indexCPtr
    				)
				{
				  pathDs_.push_back(new StringIndex(indexCPtr));
				}

    //  VII.  Methods that do main and misc work of class:
    //  PURPOSE:  To return the address of an internal JSONValue instance
    //		that results from following '*this' path, or 'NULL' if the
    //		path ends along the way.
    const JSONValue*
		follow		(const JSONValue*	valuePtr
				);

  };
