%{
  //  -----------------------------------------------------------------	//
  //									//
  //		ourPascal.lex						//
  //									//
  //	    This file defines a flex file that defines a C++ program	//
  //	that outputs the tokens encountered in a Pascal source file.	//
  //									//
  //	----	----	----	----	----	----	----	----	//
  //									//
  //	Version 1a		2024 January 25		Joseph Phillips	//
  //									//
  //  -----------------------------------------------------------------	//

  //  Compile and run with:
  //    $ flex -o ourPascalTokenizer.cpp ourPascal.lex
  //    $ g++ ourPascalTokenizer.cpp -o ourPascal
  //    $ ./ourPascal CS3.PAS

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>


//  PURPOSE:  To distinguish among the tokens that can be tokenized.
typedef		enum
		{
		  NO_LEX,
		  INTEGER_LEX,
		  FLOAT_LEX,
		  STRING_LEX,
		  IDENTIFIER_LEX,

		  AND_LEX,
		  ARRAY_LEX,
		  BEGIN_LEX,
		  CASE_LEX,
		  CONST_LEX,

		  DIV_LEX,
		  DO_LEX,
		  DOWNTO_LEX,
		  ELSE_LEX,
		  END_LEX,

		  FILE_LEX,
		  FOR_LEX,
		  FUNCTION_LEX,
		  GOTO_LEX,
		  IF_LEX,

		  IN_LEX,
		  LABEL_LEX,
		  MOD_LEX,
		  NIL_LEX,
		  NOT_LEX,

		  OF_LEX,
		  OR_LEX,
		  PACKED_LEX,
		  PROCEDURE_LEX,
		  PROGRAM_LEX,

		  RECORD_LEX,
		  REPEAT_LEX,
		  SET_LEX,
		  THEN_LEX,
		  TO_LEX,

		  TYPE_LEX,
		  UNTIL_LEX,
		  VAR_LEX,
		  WHILE_LEX,
		  WITH_LEX,

		  ASSIGN_LEX,
		  EQUAL_LEX,
		  LESSER_THAN_LEX,
		  LESSER_THAN_EQUAL_LEX,
		  GREATER_THAN_LEX,
		  GREATER_THAN_EQUAL_LEX,
		  NOT_EQUAL_LEX,
		  PLUS_LEX,
		  MINUS_LEX,
		  STAR_LEX,
		  SLASH_LEX,
		  RANGE_LEX,
		  CARET_LEX,

		  BEGIN_PAREN_LEX,
		  END_PAREN_LEX,
		  BEGIN_BRACKET_LEX,
		  END_BRACKET_LEX,
		  COLON_LEX,
		  COMMA_LEX,
		  SEMICOLON_LEX,
		  PERIOD_LEX
		}
		lex_ty;


//  PURPOSE:  To tell the size of typical buffers.
const int	BUFFER_LEN		= 4080;


//  PURPOSE:  To tell how many spaces are implied by a tab char.
const int	NUM_SPACES_PER_TAB	= 8;


//  PURPOSE:  To keep track of the line number.
extern int	lineNum;

#undef 		YY_INPUT

#define		YY_INPUT(buffer,numRetChars,bufferLen)	\
		{ numRetChars = getLexChar(buffer,bufferLen); }


//  PURPOSE:  To read the next char from 'yyin' and put it into 'buffer' of
//	length 'bufferLen'.  Returns '1' to signify that only one char was
//	obtained on success, or returns 'YY_NULL' on EOF error otherwise.
extern
int		getLexChar	(char*		buffer,
       				 int		bufferLen
				);

%}

%%
and|And|AND                     { return AND_LEX; }
array|Array|ARRAY               { return ARRAY_LEX; }
begin|Begin|BEGIN               { return BEGIN_LEX; }
case|Case|CASE                  { return CASE_LEX; }
const|Const|CONST               { return CONST_LEX; }
div|Div|DIV                     { return DIV_LEX; }
do|Do|DO                        { return DO_LEX; }
downto|Downto|DOWNTO            { return DOWNTO_LEX; }
else|Else|ELSE                  { return ELSE_LEX; }
end|End|END                     { return END_LEX; }
file|File|FILE                  { return FILE_LEX; }
for|For|FOR                     { return FOR_LEX; }
function|Function|FUNCTION      { return FUNCTION_LEX; }
goto|Goto|GOTO                  { return GOTO_LEX; }
if|If|IF                        { return IF_LEX; }
in|In|IN                        { return IN_LEX; }
label|Label|LABEL               { return LABEL_LEX; }
mod|Mod|MOD                     { return MOD_LEX; }
nil|Nil|NIL                     { return NIL_LEX; }
not|Not|NOT                     { return NOT_LEX; }
of|Of|OF                        { return OF_LEX; }
or|Or|OR                        { return OR_LEX; }
packed|Packed|PACKED            { return PACKED_LEX; }
procedure|Procedure|PROCEDURE   { return PROCEDURE_LEX; }
program|Program|PROGRAM         { return PROGRAM_LEX; }
record|Record|RECORD            { return RECORD_LEX; }
repeat|Repeat|REPEAT            { return REPEAT_LEX; }
set|Set|SET                     { return SET_LEX; }
then|Then|THEN                  { return THEN_LEX; }
to|To|TO                        { return TO_LEX; }
type|Type|TYPE                  { return TYPE_LEX; }
until|Until|UNTIL               { return UNTIL_LEX; }
var|Var|VAR                     { return VAR_LEX; }
while|While|WHILE               { return WHILE_LEX; }
with|With|WITH                  { return WITH_LEX; }
[a-zA-Z_][a-zA-Z0-9_]*          { return IDENTIFIER_LEX; }
[0-9]+                          { return INTEGER_LEX; }
[0-9]+\.[0-9]*                  { return FLOAT_LEX; }
\\'([^\\n\\']|\\\\(.|\\n))*\\'  { return STRING_LEX; }
":="                            { return ASSIGN_LEX; }
"="                             { return EQUAL_LEX; }
"<"                             { return LESSER_THAN_LEX; }
"<="                            { return LESSER_THAN_EQUAL_LEX; }
">"                             { return GREATER_THAN_LEX; }
">="                            { return GREATER_THAN_EQUAL_LEX; }
"<>"                            { return NOT_EQUAL_LEX; }
"+"                             { return PLUS_LEX; }
"-"                             { return MINUS_LEX; }
"*"                             { return STAR_LEX; }
"/"                             { return SLASH_LEX; }
".."                            { return RANGE_LEX; }
"^"                             { return CARET_LEX; }
"("                             { return BEGIN_PAREN_LEX; }
")"                             { return END_PAREN_LEX; }
"["                             { return BEGIN_BRACKET_LEX; }
"]"                             { return END_BRACKET_LEX; }
":"                             { return COLON_LEX; }
","                             { return COMMA_LEX; }
";"                             { return SEMICOLON_LEX; }
"."                             { return PERIOD_LEX; }
\{[^}]*\}                       { /* comments */ }
[ \t\r]                         { /* spaces n' tabs */ }
\n                              { lineNum++; }
%%

//  PURPOSE:  To hold the names of the tokens given in 'lex_ty'.
const char*	lexTypeName[]	= { "not a legal lexeme",
				    "INTEGER",
				    "FLOAT",
				    "STRING",
				    "IDENTIFIER",

				    "AND",
				    "ARRAY",
				    "BEGIN",
				    "CASE",
				    "CONST",

				    "DIV",
				    "DO",
				    "DOWNTO",
				    "ELSE",
				    "END",

				    "FILE",
				    "FOR",
				    "FUNCTION",
				    "GOTO",
				    "IF",

				    "IN",
				    "LABEL",
				    "MOD",
				    "NIL",
				    "NOT",

				    "OF",
				    "OR",
				    "PACKED",
				    "PROCEDURE",
				    "PROGRAM",

				    "RECORD",
				    "REPEAT",
				    "SET",
				    "THEN",
				    "TO",

				    "TYPE",
				    "UNTIL",
				    "VAR",
				    "WHILE",
				    "WITH",

				    "ASSIGN",
				    "EQUAL",
				    "LESSER_THAN",
				    "LESSER_THAN_EQUAL",
				    "GREATER_THAN",
				    "GREATER_THAN_EQUAL",
				    "NOT_EQUAL",
				    "PLUS",
				    "MINUS",
				    "STAR",
				    "SLASH",
				    "RANGE",
				    "CARET",

				    "BEGIN_PAREN",
				    "END_PAREN",
				    "BEGIN_BRACKET",
				    "END_BRACKET",
				    "COLON",
				    "COMMA",
				    "SEMICOLON",
				    "PERIOD"
				  };


//  PURPOSE:  To keep track of the line number.
int		lineNum		= 0;

//  PURPOSE:  To read the next char from 'yyin' and put it into 'buffer' of
//	length 'bufferLen'.  Returns '1' to signify that only one char was
//	obtained on success, or returns 'YY_NULL' on EOF error otherwise.
int		getLexChar	(char*	buffer,
       				 int	bufferLen
				)
{
  //  PURPOSE:  To hold the chars of the most recently read line:
  static
  char		line[BUFFER_LEN];

  //  PURPOSE:  To hold the position of the next char to read in 'linePtr',
  //	or 'line + BUFFER_LEN' if should read a new line.
  static
  char*		linePtr	= line + BUFFER_LEN;


  //  I.  Application validity check:

  //  II.  Get next char:
  //  II.A.  If at end of current line then keep reading lines:
  while  ( (linePtr >= line + BUFFER_LEN)  ||  (*linePtr == '\0') )
  {
    //  II.A.1.  Read next line:
    if  (fgets(line,BUFFER_LEN,yyin) == NULL)
    {
      //  II.A.1.a. Give up if no more lines:
      return(YY_NULL);
    }

    //  II.A.2.  Reset 'linePtr':
    linePtr = line;
  }

  //  II.B.  Update 'buffer'
  buffer[0]	= *linePtr++;
  buffer[1]	= '\0';

  //  III.  Finished:
  return(1);
}


//  PURPOSE:  To return '0' if tokenizing should continue after reaching feof()
//	on 'yyin', or '1' otherwise.  No parameters.
int		yywrap		()
{
  //  I.  Application validity check:

  //  II.  Return value:
  return(1);
}


//  PURPOSE:  To tokenize the Pascal program given as the first argument in
//	'argv[1]'.  Returns 'EXIT_SUCCESS' on success or 'EXIT_FAILURE'
//	otherwise.
int		main		(int argc, char* argv[])
{
  //  I.  Application validity check:
  if  (argc < 2)
  {
    fprintf(stderr,"Usage:\tourPascal \n");
    exit(EXIT_FAILURE);
  }

  //  II.  Attempt to tokenize file:
  //  II.A.  Attempt to open file:
  const char*	filePathCPtr	= argv[1];

  if  ((yyin = fopen(filePathCPtr,"r")) == NULL)
  {
    fprintf(stderr,"Cannot open %s\n",filePathCPtr);
    exit(EXIT_FAILURE);
  }

  //  II.B.  Attempt to tokenize 'filePathCPtr':
  int	result;

  //  II.B.1.  Each iteration gets and prints the next token:
  while  ( (result = yylex()) != YY_NULL )
  {
    printf("%s",lexTypeName[result]);

    switch  (result)
    {
    case INTEGER_LEX :
      printf(":\t%d",strtol(yytext,NULL,0));
      break;

    case FLOAT_LEX :
      printf(":\t\t%g",strtod(yytext,NULL));
      break;

    case STRING_LEX :
      printf(":\t\t%s",yytext);
      break;

    case IDENTIFIER_LEX :
      printf(":\t%s",yytext);
      break;

    default :
      break;
    }

    putchar('\n');
  }

  //  II.C.  Clean up:
  fclose(yyin);

  //  III.  Finished:
  return(EXIT_SUCCESS);
}