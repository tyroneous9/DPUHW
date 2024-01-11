//----------------------------------------------------------------------------
// Copyrigth 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "E.h"	

// ----------------------------------------------------------------------
//
// E - Project
//
// Rules: Dog's don't meow
//        Fix the code to have the dog bark
//		  Nothing can be hard coded
//
// ----------------------------------------------------------------------

Animal::Animal()
	: action("meow")
{
}

Animal::Animal(const Animal & a)
	: action(a.action)
{
}

Dog::Dog()
{
	action = "bark";
}

Dog::Dog(const Dog &r)
{
	this->action = r.action;
}

// You cannot modify this method
const char *Dog::GetAction(const Dog d)
{
	return d.action;
}

// End of File