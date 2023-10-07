#ifndef _IQUERYAGGREGATOR_H_
#define _IQUERYAGGREGATOR_H_

#include "manager_exceptions.h"

template <typename Class>
class IQueryAggregator
{
    public:
        virtual ~IQueryAggregator(void) = default;
        virtual void apply(const Class &item) = 0;
};

template <typename Type>
class IQueryAggregatorResult
{
    public:
        virtual ~IQueryAggregatorResult(void) = default;
        virtual const Type &result(void) = 0;
};

template <typename Class, typename Type>
class ResultQueryAggregator : public IQueryAggregator<Class>,
                              public IQueryAggregatorResult<Type>
{
    public:
        virtual ~ResultQueryAggregator(void) = default;
};

DEF_EX(CommonIQueryAggregatorException, ManagerException,
       "Common IQueryAggregator exception");

#endif

