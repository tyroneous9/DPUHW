%{

/*-------------------------------------------------------------------------*
 *---									---*
 *---		tree.lex						---*
 *---									---*
 *---	    This file defines a tokenizer for a parser that reads the	---*
 *---	definition of a tree.						---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1A				Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	"headers.h"
#include	"tree.tab.h"

%}

%%
"//"          [^\n]*           { /* Ignore // comments */ }

[ \t\r]+      { /* Ignore whitespace (spaces, tabs, carriage returns) */ }

\n            { ++lineNum; /* Increment line number for new lines */ }

"root"        { return root; }

"node"        { return node; }

"("           { return '('; }

")"           { return ')'; }

"["           { return '['; }

"]"           { return ']'; }

","           { return ','; }

\"[^"]*\"     {
                    yylval.strPtr_ = new std::string(yytext + 1, yylength() - 2);
                    return STRING;
              }

.             {
                    fprintf(stderr, "Non-supported char '%c' found on line %ld.\n", yytext[0], lineNum);
                    exit(EXIT_FAILURE);
              }

%%

//  PURPOSE:  To keep track of the line number.
size_t		lineNum		= 1;


int		yywrap		()
{
  return(1);
}