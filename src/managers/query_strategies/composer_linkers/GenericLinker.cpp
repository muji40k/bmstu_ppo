#include "GenericLinker.h"

#include "ValueCriteria.h"
#include "CompositeCriteria.h"

GenericLinker::GenericLinker(LinkFunction func, const std::string &name)
    : func(func), name(name)
{
    if (nullptr == func)
        throw CALL_EX(NullptrGenericLinkerException);
}

void GenericLinker::link(CriteriaBank &bank, std::list<unsigned long long> ids)
try
{
    auto iter = ids.begin();
    std::shared_ptr<const ICriteria> base = bank.get(this->name);
    std::shared_ptr<const ICriteria> start = this->func(*iter);

    if (nullptr == base)
        this->builders.push_back(LogicCriteriaBuilder(start));
    else
    {
        this->builders.push_back(LogicCriteriaBuilder(base));
        this->builders.back().addAND(start);
    }

    LogicCriteriaBuilder &builder = this->builders.back();

    for (; ids.end() != iter; ++iter)
        builder.addOR(this->func(*iter));

    bank.set(this->name, builder.get());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationGenericLinkerException);
}
