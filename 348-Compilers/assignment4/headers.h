/*-------------------------------------------------------------------------*
 *---									---*
 *---		headers.h						---*
 *---									---*
 *---	    This file includes headers and defines constants needed by 	---*
 *---	the tree parsing program.					---*
 *---									---*
 *---	----	----	----	----	----	----	----	----	---*
 *---									---*
 *---	Version 1A				Joseph Phillips		---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<string>
#include	<vector>
#include	<map>


//  PURPOSE:  To tell the default length of C-string arrays.
const int	MAX_LINE	= 256;


#include	"Node.h"
#include	"NodeStore.h"


//  PURPOSE:  To be the file from which to read input.
extern
FILE*		yyin;


//  PURPOSE:  To keep track of the line number.
extern
size_t		lineNum;


//  PURPOSE:  To hold an array of space chars.
extern
char		spaceCharArray[MAX_LINE+1];


//  PURPOSE:  To return the integer token id of the next read token, and
//	to set a member of 'yysval' to the correspond read value (if
//	 appropriate).  No parameters.
extern
int		yylex		();


//  PURPOSE:  To tell the user that a syntax error described by 'errMsgCPtr'
//	was found.  Quits program an return 'EXIT_FAILURE' to OS.
extern
int	    	yyerror		(const char*	errMsgCPtr
				);