#ifndef _ORDER_FUNCTIONS_H_
#define _ORDER_FUNCTIONS_H_

template <typename T>
bool eq(const T &a, const T &b);

template <typename T>
bool ne(const T &a, const T &b);

template <typename T>
bool lt(const T &a, const T &b);

template <typename T>
bool le(const T &a, const T &b);

template <typename T>
bool gt(const T &a, const T &b);

template <typename T>
bool ge(const T &a, const T &b);

#include "order_functions.hpp"

#endif

