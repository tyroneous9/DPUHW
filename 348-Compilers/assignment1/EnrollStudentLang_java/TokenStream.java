/*-------------------------------------------------------------------------*
 *---									---*
 *---		TokenStream.java					---*
 *---									---*
 *---	    This file defines a class that creates a stream of Symbol	---*
 *---	instances from an input.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

import	java.util.HashMap;

//  PURPOSE:  To implement an interface that gathers characters into lexemes.
class	TokenStream
{
  //  I.  Member vars:
  //  PURPOSE:  To represent the string delimitor character.
  final
  public
  char	QUOTE_CHAR		= 0x22;

  //  PURPOSE:  To represent the decimal point character.
  final
  public
  char	DECIMAL_PT_CHAR		= '.';

  //  PURPOSE:  To hold the source of the character input.
  private
  InputCharStream	inputCharStream_;

  //  PURPOSE:  To hold the lastest lexeme parsed.
  private
  Symbol	   	lastParsed_;

  //  PURPOSE:  To hold the keyword string to symbol_ty mapping.
  private
  HashMap<String,Symbol.symbol_ty>
			keywordToSymbolTMap_;

  //  II.  Disallowed auto-generated methods:

  //  III.  Protected methods:
  //  PURPOSE:  To return a pointer representing a scanned string constant.
  //	No parameters.
  protected
  Symbol	scanString	()
  				throws Exception
  {
    StringBuilder	lex		= new StringBuilder();
    boolean		haveFoundEnd	= false;

    //  Advance past first quote:
    inputCharStream_.advance();

    while  ( !inputCharStream_.isAtEnd() )
    {
      char	c = inputCharStream_.peek();

      inputCharStream_.advance();

      if  (c == QUOTE_CHAR)
      {
	haveFoundEnd	= true;
	break;
      }

      lex.append(c);
    }

    if  (!haveFoundEnd)
    {
      throw new Exception("Non-terminated string constant");
    }

    return(new Symbol(lex.toString()));
  }


  //  PURPOSE:  To return a pointer representing a scanned number.  No
  //	parameters.
  protected
  Symbol   	scanNumber	()
  {
    boolean		haveSeenDecimalPt	= false;
    StringBuilder	lex			= new StringBuilder();
    char		c;

    for  ( c = inputCharStream_.peek();
	   Character.isDigit(c) || ((c==DECIMAL_PT_CHAR) && !haveSeenDecimalPt);
	   c = inputCharStream_.peek()
	 )
    {
      lex.append(c);
      haveSeenDecimalPt	 = (c==DECIMAL_PT_CHAR);
      inputCharStream_.advance();
    }

    return(new Symbol(Double.parseDouble(lex.toString())));
  }


  //  PURPOSE:  To return a pointer to a Symbol instance representing an
  //	address.
  protected
  Symbol	scanIdentifier	()
  {
    char		c;
    StringBuilder	lex	= new StringBuilder();

    lex.append(Character.toLowerCase(inputCharStream_.peek()));
    inputCharStream_.advance();

    for  ( c = inputCharStream_.peek();
	   Character.isAlphabetic(c) || Character.isDigit(c) || (c == '_');
	   c = inputCharStream_.peek()
	 )
    {
      lex.append(Character.toLowerCase(c));
      inputCharStream_.advance();
    }

    if  ( keywordToSymbolTMap_.containsKey(lex.toString()) )
      return(new Symbol(keywordToSymbolTMap_.get(lex.toString())));

    String	keywords;
    boolean	isFirst	= true;

    return(new Symbol(Symbol.symbol_ty.IDENTIFIER_SYM));
  }


  //  PURPOSE:  To return a pointer representing a scanned Symbol, or to return
  //	'new Symbol(Symbol.symbol_ty.END_OF_INPUT_SYM)' if the '*this' is at
  //	the end-of-input.  No parameters.
  protected
  Symbol	scanner		()
  				throws Exception
  {
    while  ( Character.isWhitespace(inputCharStream_.peek()) )
      inputCharStream_.advance();

    if  ( inputCharStream_.isAtEnd() )
      return( new Symbol(Symbol.symbol_ty.END_OF_INPUT_SYM) );

    if  ( inputCharStream_.peek() == QUOTE_CHAR )
      return( scanString() );

    if  ( Character.isDigit(inputCharStream_.peek()) )
      return( scanNumber() );

    if  ( Character.isAlphabetic(inputCharStream_.peek())	||
	  (inputCharStream_.peek() == '_')
	)
      return( scanIdentifier() );

    char	ch	= inputCharStream_.peek();
    Symbol	symbol	= null;

    inputCharStream_.advance();

    switch  (ch)
    {
    case '(' :
      symbol	= new Symbol(Symbol.symbol_ty.BEGIN_PAREN_SYM);
      break;

    case ')' :
      symbol	= new Symbol(Symbol.symbol_ty.END_PAREN_SYM);
      break;

    case ',' :
      symbol	= new Symbol(Symbol.symbol_ty.COMMA_SYM);
      break;

    case '.' :
      symbol	= new Symbol(Symbol.symbol_ty.PERIOD_SYM);
      break;

    default :
      throw new Exception("Unexpected character in input");
    }

    return(symbol);
  }

  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To initialize '*this' to tokenize given characters read from
  //  	'newInputCharStream'.  No parameters.
  public
  TokenStream			(InputCharStream	newInputCharStream
				)
  				throws Exception
  {
    inputCharStream_	= newInputCharStream;
    lastParsed_		= null;
    keywordToSymbolTMap_= new HashMap<String,Symbol.symbol_ty>();

    keywordToSymbolTMap_.put("fail",	Symbol.symbol_ty.FAIL_KEYWORD_SYM);
    keywordToSymbolTMap_.put("bomb",	Symbol.symbol_ty.BOMB_KEYWORD_SYM);
    keywordToSymbolTMap_.put("pass",	Symbol.symbol_ty.PASS_KEYWORD_SYM);
    keywordToSymbolTMap_.put("ace",	Symbol.symbol_ty.ACE_KEYWORD_SYM);
    keywordToSymbolTMap_.put("attend",	Symbol.symbol_ty.ATTEND_KEYWORD_SYM);
    keywordToSymbolTMap_.put("the",	Symbol.symbol_ty.THE_KEYWORD_SYM);
    keywordToSymbolTMap_.put("proficiency",
					Symbol.symbol_ty.PROFICIENCY_KEYWORD_SYM);
    keywordToSymbolTMap_.put("prereq",	Symbol.symbol_ty.PREREQ_KEYWORD_SYM);
    keywordToSymbolTMap_.put("prerequisite",
					Symbol.symbol_ty.PREREQ_KEYWORD_SYM);
    keywordToSymbolTMap_.put("exam",	Symbol.symbol_ty.EXAM_KEYWORD_SYM);
    keywordToSymbolTMap_.put("class",	Symbol.symbol_ty.CLASS_KEYWORD_SYM);
    advance();
  }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the 'symbol_ty' of the 'Symbol' instance that is next
  //	in the symbol stream.  No parameters.
  public
  Symbol.symbol_ty
		peek		()
  				throws Exception
  {
    if  (lastParsed_ == null)
      lastParsed_	= scanner();

    return(lastParsed_.getType());
  }

  //  PURPOSE:  To return the pointer to the old Symbol at that was at the
  //	front of the symbol stream, and then to internally advance to the next
  //	Symbol instance (if not already at the end).  No parameters.
  public
  Symbol	advance		()
  				throws Exception
  {
    Symbol	toReturn	= lastParsed_;

    lastParsed_	= scanner();
    return(toReturn);
  }

};


