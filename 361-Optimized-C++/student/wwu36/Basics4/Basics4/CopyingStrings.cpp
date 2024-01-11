//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "CopyingStrings.h"

char *StringCopy_1( char * const dest, const char * const input)
{
	// using strcpy()
	size_t len = strlen(input) + 1;
	strcpy_s(dest, len, input);
	return dest;
}

char *StringCopy_2( char  * const dest, const char * const input)
{
	// using memcpy() and strlen()
	size_t len = strlen(input) + 1;
	memcpy(dest, input, len);
	return dest;
}

char *StringCopy_3( char  * const dest, const char * const input)
{
	// using char by char copies
	size_t len = strlen(input) + 1;
	size_t i = 0;
	while (i < len) {
		dest[i] = input[i];
		i++;
	}
	return dest;
}


// ---  End of File ---
