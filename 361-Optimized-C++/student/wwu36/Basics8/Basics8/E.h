//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef E_H
#define E_H

// MODIFY this file
//
// Write the methods missing in the class template
//     You cannot change the private data
//     Writing a basic stack in terms of STL Vector 

#include <vector>

template <typename T>
class StackE
{

public:
	// Write the following functions

    void push(const T& data)
    {
        elems.push_back(data);
    }

    // pop element
    void pop()
    {
        if (!elems.empty())
            elems.pop_back();
    }

    // return top element
    T top() const
    {
        if (!elems.empty())
        {
            return elems.back();
        }
        else
        {
            // Return a default-constructed value when the stack is empty
            return T();
        }
    }

    // return whether the stack is empty
    bool empty() const
    {
        return elems.empty();
    }

private:
	std::vector<T> elems;     // elements
};


#endif

// ---  End of File ---------------
