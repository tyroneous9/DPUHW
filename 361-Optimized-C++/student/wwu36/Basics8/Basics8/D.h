#ifndef D_H
#define D_H

#include <string.h>

template <typename T>
const T& minD(const T& a, const T& b)
{
    if (a < b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

const char* const& minD(const char* const& a, const char* const& b)
{
    if (strcmp(a, b) < 0)
    {
        return a;
    }
    else
    {
        return b;
    }
}

template <typename T>
const T& minD(const T& a, const T& b, const T& c)
{
    return minD(minD(a, b), c);
}

#endif
