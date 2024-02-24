/*-------------------------------------------------------------------------*
 *---									---*
 *---		ToPhrase.java						---*
 *---									---*
 *---	    This file defines a class representing phrases telling	---*
 *---	"to where".							---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 December 6		Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  PURPOSE:  To represent phrase telling where to.
public
class	ToPhrase implements Phrase
{
  //  I.  Member vars:
  //  PURPOSE:  To hold the location.
  private
  String			str_	= "";

  //  PURPOSE:  To hold the next phrase in the list, if there is one.
  private
  Phrase			next_	= null;

  //  II.  Protected methods:

  //  III.  Constructor(s) and factory(s):
  //  PURPOSE:  To make a phrase the represents "to newStr".
  //	No return value.
  public
  ToPhrase			(String		newStr
				)
				{
				  str_	= newStr;
				}

  //  IV.  Accessors:
  //  PURPOSE: To return the name of the place.  No parameters.
  public
  String	toString	()
				{ return(str_); }

  //  PURPOSE: To return the next phrase, or 'null' if there is none.
  //	No parameters.
  public
  Phrase	getNext		()
				{ return(next_); }

  //  V.  Mutators:
  //  PURPOSE:  To make 'next' the phrase after 'this' one.  No return value.
  public
  void		attach		(Phrase		next
				)
				{ next_	= next; }

}