#ifndef _SIMPLEQUERYCOMPOSERADAPTER_HPP_
#define _SIMPLEQUERYCOMPOSERADAPTER_HPP_

#include "SimpleQueryComposerAdapter.h"

#include <string>
#include <memory>

#include "SimpleAggregator.h"

#include "typestring.h"

template <typename Class, typename RepoType>
SimpleQueryComposerAdapter<Class, RepoType>::SimpleQueryComposerAdapter(Getter getter)
    : getter(getter)
{
    if (nullptr == getter)
        throw CALL_EX(NullptrSimpleQueryComposerAdapterException);
}

template <typename Class, typename RepoType>
const std::string &SimpleQueryComposerAdapter<Class, RepoType>::type(void) const
{
    return TypeName::get<Class>();
}

template <typename Class, typename RepoType>
std::list<unsigned long long> SimpleQueryComposerAdapter<Class, RepoType>::run(AppContext &context, std::shared_ptr<const ICriteria> criteria) const
try
{
    std::shared_ptr<SimpleQuery<Class, RepoType>> query = nullptr;
    SimpleAggregator<Class, unsigned long long> aggregator (&Class::getId);

    if (nullptr == criteria)
        query = std::make_shared<SimpleQuery<Class, RepoType>>(this->getter, aggregator);
    else
        query = std::make_shared<SimpleQuery<Class, RepoType>>(this->getter, aggregator,
                                                               *criteria);

    query->execute(context);

    return aggregator.result();
}
catch (std::bad_alloc &er)
{
    throw CALL_EX(AllocationSimpleQueryComposerAdapterException);
}

#endif

