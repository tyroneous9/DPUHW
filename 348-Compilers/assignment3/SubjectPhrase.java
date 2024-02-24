/*-------------------------------------------------------------------------*
 *---									---*
 *---		SubjectPhrase.java					---*
 *---									---*
 *---	    This file defines a class representing phrases telling	---*
 *---	the subject of a sentence.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 December 6		Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

 public
 class	SubjectPhrase implements Phrase
 {
   //  I.  Member vars:
   //  PURPOSE:  To hold the what or whom.
   private
   String			str_		= "";
 
   //  PURPOSE:  To hold the next phrase in the list, if there is one.
   private
   Phrase			next_		= null;
 
   //  II.  Protected methods:
 
   //  III.  Constructor(s), assignment op(s), factory(s) and destructor:
   //  PURPOSE:  To make a phrase the represents "asFor *newStr".
   //	No return value.
   public
   SubjectPhrase			(String		newStr
                 )
                 {
                     str_	= newStr;
                 }
 
   //  IV.  Accessors:
   //  PURPOSE: To return the name of what or whom.  No parameters.
   public
   String	toString	()
                 { return(str_); }
 
   //  PURPOSE: To return the address of the next phrase, or 'NULL' if there is
   //	none.  No parameters.
   public
   Phrase	getNext		()
                 { return(next_); }
 
   //  V.  Mutators:
   //  PURPOSE:  To make 'next' the phrase after '*this' one.
   //	No return value.
   public
   void		attach		(Phrase		next
                 )
                 {
                   next_	= next;
                 }
 
 }