//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

// --------------------------------
// ---      DO NOT MODIFY       ---
// --------------------------------

#ifndef COPY_TO_BUFFER_H
#define COPY_TO_BUFFER_H

class Dog
{
public:
	static const unsigned int BUFF_SIZE = 10;
public:
	Dog();
	Dog(const Dog &) = delete;
	Dog & operator=(const Dog &) = delete;
	~Dog();

	// retrieve the message
	char *GetMessage();
	
	// user sets the message
	void SetMessage( const char * const inMessage );
	
	// prints the mesage
	void Print();

private:

	// holds the message
	char buff[BUFF_SIZE];

};

#endif


// ---  End of File ---

