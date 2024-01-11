//--------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//--------------------------------------------------------

#include "CopyToBuffer.h"

// retrieve the message
char * Dog::GetMessage()
{
	return this->buff;
}
	
// user sets the message
void Dog::SetMessage( const char * const inMessage )
{
	// Do the copy to internal variable buff
	// make sure it's safe
	// ----> do work here
	size_t len = this->BUFF_SIZE;
	if (inMessage == nullptr) {
		memcpy(this->buff, "", len);
		this->buff[BUFF_SIZE - 1] = '\0';
		return;
	}
	memcpy(this->buff, inMessage, len);
	this->buff[BUFF_SIZE-1] = '\0';
}

// prints the mesage
void Dog::Print()
{
	Trace::out2("message: %s\n",this->buff);
}

Dog::Dog()
{
	memset( this->buff, 0xaa, BUFF_SIZE );
}

Dog::~Dog()
{
	memset( this->buff, 0xaa, BUFF_SIZE );
}


// ---  End of File ---
