/*-------------------------------------------------------------------------*
 *---									---*
 *---		header.h						---*
 *---									---*
 *---	    This file includes other header files and defines constants	---*
 *---	needed for a JSON-reading and printing application.  See	---*
 *---	https://www.json.org/.						---*
 *---									---*
 *---		This is a declassified version of an original		---*
 *---			CONFIDENTIAL source file owned by:		---*
 *---			Applied Philosophy of Science			---*
 *---									---*
 *---	----	----	----	----	----	----	----	-----	---*
 *---									---*
 *---	Version 9a		2024 March 17		Joseph Phillips	---*
 *---									---*
 *-------------------------------------------------------------------------*/

#include	<cstdlib>
#include	<cstdio>
#include	<cstring>
#include	<sys/types.h>
#include	<sys/stat.h>
#include	<fcntl.h>
#include	<unistd.h>
#include	<string>
#include	<vector>
#include	<map>
#include	<stack>


const int	MAX_TINY_ARRAY_LEN	= 1024;

const int	COMMON_ARRAY_LEN	= 4096;

const char	QUOTE_CHAR		= (char)34;

const char	JSON_MAPPER		= ':';

const char	JSON_SEPARATOR		= ',';

const char	BEGIN_JSON_ARRAY	= '[';

const char	END_JSON_ARRAY		= ']';

const char	BEGIN_JSON_BRACE	= '{';

const char	END_JSON_BRACE		= '}';


extern
char		commonCArray[COMMON_ARRAY_LEN];


//  PURPOSE:  To define a comparison operator for ordering two C-strings
//		objects.
struct		CStringComp
{
  bool		operator()	(const char*    lhsPtr,
				 const char*    rhsPtr
				)
				const
				{
				  return( strcmp(lhsPtr,rhsPtr) < 0 );
				}
};


class		WriterBuffer;

#include	"ReservedVarSizedBufferSpace.h"
#include	"WriterBuffer.h"
#include	"InputCharStream.h"
#include	"JSONValue.h"
