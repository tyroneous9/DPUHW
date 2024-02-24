/*-------------------------------------------------------------------------*
 *---									---*
 *---		Sentence.java						---*
 *---									---*
 *---	    This file defines a class representing a sentence composed	---*
 *---	of 1 or 2 phrase, the present-tense verb "to go" that is either	---*
 *---	in a question or declarative form.		      	 	---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1a	2023 December 6		Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

 class	Sentence
 {
   //  I.  Member vars:
   //  PURPOSE:  To refer to the topic phrase, if one is given.
   private
   SubjectPhrase			asFor_		= null;
 
   //  PURPOSE:  To refer to the location phrase, if one is given.
   private
   ToPhrase			to_		= null;
 
   //  PURPOSE:  To hold 'true' if '*this' represents a question or 'false'
   //	if '*this' represents a declarative sentence.
   private
   boolean			isAQuestion_	= false;
 
   //  II.  Protected methods:
   //  PURPOSE:  To attach phrase 'phrase' to '*this' Sentence.
   //	No return value.
   protected
   void		attach		(SubjectPhrase		phrase
                 )
   {
     if  (phrase != null)
     {
       if  (asFor_ != null)
       {
     System.err.println("Ambiguity: 2 people mentioned.");
     System.exit(1);
       }
 
       asFor_	= phrase;
     }
   }
 
   //  PURPOSE:  To attach phrase 'phrase' to '*this' Sentence.
   //	No return value.
   protected
   void		attach		(ToPhrase		phrase
                 )
   {
     if  (phrase != null)
     {
       if  (to_ != null)
       {
     System.err.println("Ambiguity: 2 places mentioned.");
     System.exit(1);
       }
 
       to_	= phrase;
     }
   }
 
   //  III.  Constructor(s), assignment op(s), factory(s) and destructor:
   //  PURPOSE:  To initialize 'this' Sentence with the list of phrases given
   //	in 'phrase' to be a question if 'isAQuestion' is 'true' or a
   //	declarative sentence otherwise.  No return value.
   public
   Sentence			(Phrase		phrase,
                  boolean	isAQuestion
                 )
   {
     isAQuestion_	= isAQuestion;
 
     if  (phrase != null)
     {
       if  (phrase instanceof SubjectPhrase)
       {
     attach((SubjectPhrase)phrase);
       }
       else
       if  (phrase instanceof ToPhrase)
       {
     attach((ToPhrase)phrase);
       }
 
       if  (phrase.getNext() != null)
       {
     if  (phrase.getNext() instanceof SubjectPhrase)
     {
       attach((SubjectPhrase)phrase.getNext());
     }
     else
     if  (phrase.getNext() instanceof ToPhrase)
     {
       attach((ToPhrase)phrase.getNext());
           }
       }
     }
   }
 
   //  V.  Accessors:
 
   //  VI.  Mutators:
 
   //  VII.  Methods that do the main and misc work of the class:
   //  PURPOSE:  To compose and return a string representation of 'this'
   //  	Sentence in conventional English.
   public
   String	toString	()
   {
     StringBuffer	buf	= new StringBuffer();
 
     if  (isAQuestion_)
     {
       if  ( (asFor_ == null)  ||  (asFor_.toString() == "you") )
     buf.append("Are you going");
       else
     buf.append("Am I going");
 
       if  (to_ != null)
       {
     buf.append(" " + to_.toString() + "?\n");
       }
       else
     buf.append("?\n");
     }
     else
     {
       if  ( (asFor_ == null)  ||  (asFor_.toString() == "I") )
     buf.append("I am going");
       else
     buf.append("You are going");
 
       if  (to_ != null)
       {
     buf.append(" to " + to_.toString() + ".\n");
       }
       else
     buf.append(".\n");
     }
 
     return(buf.toString());
   }
 
 }