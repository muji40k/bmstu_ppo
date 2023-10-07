#ifndef _IQUERYABLE_H_
#define _IQUERYABLE_H_

#include <list>

template <typename T>
class IQueryableFilter
{
    public:
        virtual ~IQueryableFilter(void) = default;
        virtual bool check(const T &item) const = 0;
};

template <typename T>
class IQueryable
{
    public:
        virtual ~IQueryable(void) = default;
        virtual void add(const T &item) = 0;
        virtual void update(const T &item) = 0;
        virtual void del(const T &item) = 0;
        virtual std::list<T> get(const IQueryableFilter<T> &filter) const = 0;
        virtual void del(const IQueryableFilter<T> &filter) = 0;
};

#endif

