#ifndef _QUERYABLEFILTERGENERIC_H_
#define _QUERYABLEFILTERGENERIC_H_

#include "IQueryable.h"

template <typename T>
class AllFilter : public IQueryableFilter<T>
{
    public:
        virtual ~AllFilter(void) override = default;
        virtual bool check(const T &item) const override;
};

template <typename T>
class AndFilter : public IQueryableFilter<T>
{
    public:
        AndFilter(const IQueryableFilter<T> &a, const IQueryableFilter<T> &b);
        virtual ~AndFilter(void) override = default;
        virtual bool check(const T &item) const override;

    private:
        const IQueryableFilter<T> &a;
        const IQueryableFilter<T> &b;
};

template <typename T>
class OrFilter : public IQueryableFilter<T>
{
    public:
        OrFilter(const IQueryableFilter<T> &a, const IQueryableFilter<T> &b);
        virtual ~OrFilter(void) override = default;
        virtual bool check(const T &item) const override;

    private:
        const IQueryableFilter<T> &a;
        const IQueryableFilter<T> &b;
};

template <typename T>
class NotFilter : public IQueryableFilter<T>
{
    public:
        NotFilter(const IQueryableFilter<T> &filter);
        virtual ~NotFilter(void) override = default;
        virtual bool check(const T &item) const override;

    private:
        const IQueryableFilter<T> &filter;
};

template <typename Class, typename T>
class OrderFilter : public IQueryableFilter<Class>
{
    public:
        using Getter = const T &(Class::*)(void) const;
        using OrderFunction = bool (*)(const T &, const T &);

        OrderFilter(Getter getter, OrderFunction func, const T &value);
        virtual ~OrderFilter(void) override = default;
        virtual bool check(const Class &item) const override;

    private:
        Getter getter;
        OrderFunction func;
        const T value;
};

#include "QueryableFilterGeneric.hpp"

#endif

