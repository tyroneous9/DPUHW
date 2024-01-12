/*--------------------------------------------------------------------------*
 *----									----*
 *----		EnrollStudentLang.java					----*
 *----									----*
 *----		 (1) Paragraph -> Fail Succeed Attend (endOfInput)	----*
 *----		 (2) Fail -> fail the prereq . Fail			----*
 *----		 (3) Fail -> bomb the proficiency exam . Fail		----*
 *----		 (4) Fail -> 						----*
 *----		 (5) Succeed -> pass the prereq .			----*
 *----		 (6) Succeed -> ace the proficiency exam .		----*
 *----		 (7) Attend -> attend the class .			----*
 *----									----*
 *----	----	----	----	----	----	----	----	----	----*
 *----									----*
 *----	Version 1.0		2024 January 10		Joseph Phillips	----*
 *----									----*
 *--------------------------------------------------------------------------*/

import	java.lang.*;
import	java.util.Scanner;


public
class	EnrollStudentLang
{
  //  PURPOSE:  To parse non-terminal 'Fail' from 'tokenizer'.
  protected
  static
  void		parseFail	(TokenStream	tokenizer
				)
				throws Exception
  {
     //  I.  Application validity check:

    //  II.  Attempt to parse finish:
    Symbol.symbol_ty	peek	= tokenizer.peek();

    if  (peek == Symbol.symbol_ty.FAIL_KEYWORD_SYM)
    {
      //  II.A.  Parse "Fail"
      tokenizer.advance();

      if  (tokenizer.peek() != Symbol.symbol_ty.THE_KEYWORD_SYM)
      {
	throw new Exception("Expected \"the\"");
      }

      tokenizer.advance();

      if  (tokenizer.peek() != Symbol.symbol_ty.PREREQ_KEYWORD_SYM)
      {
	throw new Exception("Expected \"prerequisite\"");
      }

      tokenizer.advance();

      if  (tokenizer.peek() != Symbol.symbol_ty.PERIOD_SYM)
      {
	throw new Exception("Expected \".\"");
      }

      tokenizer.advance();

      parseFail(tokenizer);
    }
    else
    if  (peek == Symbol.symbol_ty.BOMB_KEYWORD_SYM)
    {
      //  YOUR CODE HERE
    }
    else
    if  ( (peek == Symbol.symbol_ty.PASS_KEYWORD_SYM)  ||
    	  (peek == Symbol.symbol_ty.ACE_KEYWORD_SYM)
	)
    {
      //  YOUR CODE HERE
    }
    else
    {
      throw new Exception("Expected \"fail\", \"bomb\", \"pass\" or \"ace\".");
    }

    //  III.  Finished:
  }


  //  PURPOSE:  To parse non-terminal 'Succeed' from 'tokenizer'.
  protected
  static
  void		parseSucceed	(TokenStream	tokenizer
				)
				throws Exception
  {
    //  I.  Application validity check:

    //  II.  Attempt to parse Succeed:
    Symbol.symbol_ty	peek	= tokenizer.peek();

    if  (peek == Symbol.symbol_ty.PASS_KEYWORD_SYM)
    {
      //  YOUR CODE HERE
    }
    else
    if  (peek == Symbol.symbol_ty.ACE_KEYWORD_SYM)
    {
      //  YOUR CODE HERE
    }
    else
    {
      throw new Exception("Expected \"pass\" or \"ace\".");
    }

  //  III.  Finished:
}


  //  PURPOSE:  To parse non-terminal 'Attend' from 'tokenizer'.
  protected
  static
  void		parseAttend	(TokenStream	tokenizer
				)
				throws Exception
  {
    //  I.  Application validity check:

    //  II.  Attempt to parse cycle:
    //  YOUR CODE HERE

    //  III.  Finished:
  }


  //  PURPOSE:  To parse non-terminal 'Paragraph' from 'tokenizer'.
  protected
  static
  void		parseParagraph	(TokenStream	tokenizer
				)
				throws Exception
  {
    //  I.  Application validity check:

    //  II.  Attempt to parse recipe:
    Symbol.symbol_ty	peek	= tokenizer.peek();

    if  ( (peek == Symbol.symbol_ty.FAIL_KEYWORD_SYM)	||
	  (peek == Symbol.symbol_ty.BOMB_KEYWORD_SYM)	||
	  (peek == Symbol.symbol_ty.PASS_KEYWORD_SYM)	||
	  (peek == Symbol.symbol_ty.ACE_KEYWORD_SYM)
	)
    {
      parseFail(tokenizer);
      parseSucceed(tokenizer);
      parseAttend(tokenizer);

      if  (tokenizer.peek() != Symbol.symbol_ty.END_OF_INPUT_SYM)
      {
        throw new Exception("Expected end after \"Attend the class .\"");
      }

      tokenizer.advance();
    }
    else
    {
      throw new Exception("Expected \"fail\", \"bomb\", \"pass\" or \"ace\".");
    }

    //  III.  Finished:
  }


  //  PURPOSE:  To return a string with the expression to compute, either from
  //	the command line or the keyboard.  'argc' tells how many arguments
  //	were on the command line and 'argv[]' points to those arguments.
  protected
  static
  String	getInput	(String		args[]
				)
  {
    //  I.  Application validity check:

    //  II.  Get input:
    //  II.A.  Handle command line input:
    if  (args.length > 0)
      return(args[0]);

    //  II.B.  Handle keyboard input:
    Scanner input = new Scanner(System.in);

    System.out.print("Expression to compute: ");

    //  III.  Finished:
    return(input.nextLine());
  }


  //  PURPOSE:  To get, and attempt to compute, the expression.  The expression
  //	may either come from the command line or the keyboard.  'args[]' has
  //	the command line arguments.  No return value.
  public
  static
  void		main		(String		args[]
				)
  {
    String		input		= getInput(args);
    InputCharStream	charStream	= new InputCharStream(input);

    try
    {
      TokenStream	tokenizer	= new TokenStream(charStream);

      parseParagraph(tokenizer);
      System.out.println("Congratulations, you in the class!");
    }
    catch  (Exception	error
	   )
    {
      System.err.println(error.toString());
      System.err.println("Sorry, you are not enrolled!");
    }

  }

}
