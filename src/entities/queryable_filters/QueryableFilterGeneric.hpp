#include "QueryableFilterGeneric.h"

template <typename T>
bool AllFilter<T>::check(const T &) const { return true; }

template <typename T>
AndFilter<T>::AndFilter(const IQueryableFilter<T> &a, const IQueryableFilter<T> &b)
    : a(a), b(b)
{}

template <typename T>
bool AndFilter<T>::check(const T &item) const
{
    return a.check(item) && b.check(item);
}

template <typename T>
OrFilter<T>::OrFilter(const IQueryableFilter<T> &a, const IQueryableFilter<T> &b)
    : a(a), b(b)
{}

template <typename T>
bool OrFilter<T>::check(const T &item) const
{
    return a.check(item) || b.check(item);
}

template <typename T>
NotFilter<T>::NotFilter(const IQueryableFilter<T> &filter)
    : filter(filter)
{}

template <typename T>
bool NotFilter<T>::check(const T &item) const
{
    return !filter.check(item);
}

template <typename Class, typename T>
OrderFilter<Class, T>::OrderFilter(OrderFilter<Class, T>::Getter getter,
                                   OrderFilter<Class, T>::OrderFunction func,
                                   const T &value)
    : getter(getter), func(func), value(value)
{}

template <typename Class, typename T>
bool OrderFilter<Class, T>::check(const Class &item) const
{
    return this->func((item.*this->getter)(), this->value);
}

