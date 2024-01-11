//-----------------------------------------------------------------------------
// Copyright 2023, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------- 

#ifndef F_H
#define F_H

// MODIFY this file

// There should be two classes defined in this header
//     Generalized template class
//     Full class specification class 
//
// Generalized: Cut & Paste from E.h for the general class template
//     Then add a second full specialization class
//
// Write a full class specialization for float
//     in this class when you push() a float it pushes the data twice
//     in this class when you pop() it pops a singe element off the stack
//     top() and empty() behave the same.

#include <vector>

template <typename T>
class StackF
{
public:
	// Write the following functions

    void push(T const& data)
    {
        elems.push_back(data);
    }

    void pop()
    {
        if (!elems.empty())
        {
            elems.pop_back();
        }
    }

    T top() const
    {
        if (!elems.empty())
        {
            return elems.back();
        }
        else
        {
            return T();
        }
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
	std::vector<T> elems;     // elements
};

template <>
class StackF<float>
{
public:
    void push(float data)
    {
        elems.push_back(data);
        elems.push_back(data);
    }

    void pop()
    {
        if (!elems.empty())
        {
            elems.pop_back();
        }
    }

    float top() const
    {
        if (!elems.empty())
        {
            return elems.back();
        }
        else
        {
            return float();
        }
    }

    bool empty() const
    {
        return elems.empty();
    }

private:
    std::vector<float> elems;
};

#endif

// ---  End of File ---------------
