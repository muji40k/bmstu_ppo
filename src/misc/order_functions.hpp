#ifndef _ORDER_FUNCTIONS_HPP_
#define _ORDER_FUNCTIONS_HPP_

#include "order_functions.h"

template <typename T>
bool eq(const T &a, const T &b)
{
    return a == b;
}

template <typename T>
bool ne(const T &a, const T &b)
{
    return a != b;
}

template <typename T>
bool lt(const T &a, const T &b)
{
    return a < b;
}

template <typename T>
bool le(const T &a, const T &b)
{
    return a <= b;
}

template <typename T>
bool gt(const T &a, const T &b)
{
    return a > b;
}

template <typename T>
bool ge(const T &a, const T &b)
{
    return a >= b;
}

#endif

