//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "SortStrings.h"

int compareAlph(const void* a, const void* b) {
	const char* str1 = *(const char**)a;
	const char* str2 = *(const char**)b;
	return strcmp(str1, str2);
}

void ReorderAlphabetical(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on alphabetical order, (a begin, z end)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) YOU need to use qsort() - might be a good function to know
	
	const size_t len = strlen(inString) + 1;
	char* chars = new char[len];
	strcpy_s(chars, len, inString);
	char* words[10];
	size_t numWords = 0;
	char* context = nullptr;
	char* token = strtok_s(chars, " ", &context);
	while (token != NULL) {
		words[numWords] = token;
		numWords++;
		token = strtok_s(nullptr, " ", &context);
	}
	qsort(words, numWords, sizeof(char*), compareAlph);
	memset(outString, '\0', len);
	outString[0] = '\0';
	size_t i = 0;
	while(i < numWords) {
		strcat_s(outString, len, words[i]);
		if(i != numWords-1)
			strcat_s(outString, len, " ");
		i++;
	}
	
	delete[] chars;
}


int compareLen(const void* a, const void* b) {
	const char* str1 = *(const char**)a;
	const char* str2 = *(const char**)b;
	if (strlen(str1) == strlen(str2)) {
		return strcmp(str1, str2);
	}
	return (int)(strlen(str1) - strlen(str2));
}

void ReorderWordLength(const char * const inString, char * const outString )
{
	// 1) reorder the words in the string, words are separated with spaces
	// 2) sort words on their word length order, (short, longest)
	// 3) you don't know how many words 
	// 4) if dynamically create any buffers inside this routine, clean them up
	// 5) use strtok and strcat in your answer
	// 6) You need to use qsort() - might be a good function to know

	const size_t len = strlen(inString) + 1;
	char* chars = new char[len];
	strcpy_s(chars, len, inString);
	char* words[64];
	size_t numWords = 0;
	char* context = nullptr;
	char* token = strtok_s(chars, " ", &context);
	while (token != NULL) {
		words[numWords] = token;
		numWords++;
		token = strtok_s(nullptr, " ", &context);
	}
	qsort(words, numWords, sizeof(char*), compareLen);
	memset(outString, '\0', len);
	outString[0] = '\0';
	size_t i = 0;
	while (i < numWords) {
		strcat_s(outString, len, words[i]);
		if (i != numWords - 1)
			strcat_s(outString, len, " ");
		i++;
	}
	delete[] chars;

}


// ---  End of File ---
