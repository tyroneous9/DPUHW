//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include"LengthOfStrings.h"

size_t LengthOfString_1( const char  * const input)
{
	// using strlen()
	size_t len = strlen(input);
	return len;
}

size_t LengthOfString_2( const char  * const input)
{
	// using char by char
	size_t i = 0;
	while (input[i] != '\0') {
		i++;
	}
	return i;
}


// ---  End of File ---

