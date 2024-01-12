/*-------------------------------------------------------------------------*
 *---									---*
 *---		InputCharStream.java					---*
 *---									---*
 *---	    This file defines a class that creates a stream of char	---*
 *---	instances from a string.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a					Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

/*  PURPOSE:  To implement an interface that manages the character source.
 */
class	InputCharStream
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the input.
  private
  String		input_;

  //  PURPOSE:  To hold where the cursor is.
  private
  int			index_;

  //  II.  Disallowed auto-generated methods:
  
  //  III.  Protected methods:

  //  IV.  Constructor(s), assignment op(s), factory(s) and destructor:
  //  PURPOSE:  To
  public
  InputCharStream	(String	newInput
			)
  {
    input_	= newInput;
    index_	= 0;
  }

  //  V.  Accessors:

  //  VI.  Mutators:

  //  VII.  Methods that do main and misc work of class:
  //  PURPOSE:  To return the current char, or '\0' if there are no more.
  //	No parameters.
  char		peek	()
  {
    return( (index_ >= input_.length()) ? '\0' : input_.charAt(index_) );
  }

  //  PURPOSE:  To return 'true' if at eof-of-input, or 'false' otherwise.
  boolean		isAtEnd	()
  {
    return(index_ >= input_.length());
  }

  //  PURPOSE:  To advance to the next char (if not already at end).  No
  //	parameters.  No return value.
  void		advance	()
  {
    if  (index_ < input_.length())  index_++;
  }

};


