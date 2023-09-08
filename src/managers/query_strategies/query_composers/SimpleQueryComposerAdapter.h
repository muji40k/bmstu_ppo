#ifndef _SIMPLEQUERYCOMPOSERADAPTER_H_
#define _SIMPLEQUERYCOMPOSERADAPTER_H_

#include "manager_exceptions.h"

#include "QueryComposer.h"
#include "SimpleQuery.h"

template <typename Class, typename RepoType>
class SimpleQueryComposerAdapter : public QueryComposer::QueryItem
{
    public:
        using Getter = typename SimpleQuery<Class, RepoType>::Getter;

    public:
        SimpleQueryComposerAdapter(Getter getter);
        virtual ~SimpleQueryComposerAdapter(void) override = default;
        virtual const std::string &type(void) const override;
        virtual std::list<unsigned long long> run(AppContext &context, std::shared_ptr<const ICriteria> criteria) const override;

    private:
        Getter getter;
};

DEF_EX(CommonSimpleQueryComposerAdapterException, CommonQueryComposerException,
       "Common QueryComposer exception");
DEF_EX(NullptrSimpleQueryComposerAdapterException, CommonSimpleQueryComposerAdapterException,
       "Getter isn't set");
DEF_EX(AllocationSimpleQueryComposerAdapterException, CommonSimpleQueryComposerAdapterException,
       "Unable to allocate query");

#include "SimpleQueryComposerAdapter.hpp"

#endif

