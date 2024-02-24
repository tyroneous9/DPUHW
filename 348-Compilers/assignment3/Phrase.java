/*-------------------------------------------------------------------------*
 *---									---*
 *---		Phrase.java						---*
 *---									---*
 *---	    This file defines an interface of phrases in a Sentence.	---*
 *---	The phrases are kind of equivalent to prepositional phrases.	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 December 6		Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

//  PURPOSE:  To serve as the interface for all phrases.
public
interface	Phrase
{
  //  PURPOSE:  To return the reference to the next phrase, if there is one.
  //	No parameters.
  public
  Phrase	getNext		();

  //  PURPOSE:  To make 'next' the phrase after '*this' one.  No return value.
  public
  void		attach		(Phrase		next
				);

}