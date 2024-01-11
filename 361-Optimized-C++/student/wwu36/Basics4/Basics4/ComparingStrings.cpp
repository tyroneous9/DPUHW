//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "ComparingStrings.h"

int StringCompare_1( const char  * const s1, const char * const s2)
{
	// using strcmp()
	int result = strcmp(s1, s2);
	return result;
}

int StringCompare_2( const char  * const s1, const char * const s2)
{
	// using memcmp() & strlen()
	size_t len = strlen(s2);
	int result = memcmp(s1, s2, len);
	return result;
}

int StringCompare_3( const char  * const s1, const char * const s2)
{
	// using char by char comparisions
	size_t len = strlen(s1);
	size_t i = 0;
	int result = 0;
	while (i < len) {
		result = s1[i]-s2[i];
		if (result != 0)
			break;
		i++;
	}
	if (result > 0)
		return 1;
	else if (result < 0)
		return -1;
	else
		return result;
}


// ---  End of File ---
