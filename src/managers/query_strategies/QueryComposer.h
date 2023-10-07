#ifndef _QUERYCOMPOSER_H_
#define _QUERYCOMPOSER_H_

#include <memory>
#include <list>
#include <unordered_map>
#include <initializer_list>

#include "manager_exceptions.h"

#include "CriteriaBank.h"

#include "AppContext.h"

class QueryComposer
{
    public:
        class QueryItem
        {
            public:
                virtual ~QueryItem(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual std::list<unsigned long long> run(AppContext &context, std::shared_ptr<const ICriteria> criteria) const = 0;
        };

    public:
        QueryComposer(void) = default;
        QueryComposer(std::initializer_list<std::shared_ptr<const QueryItem>> items);

        void add(std::shared_ptr<const QueryItem> item);
        std::list<unsigned long long> run(AppContext &context,
                                          const CriteriaBank &bank) const;

    private:
        std::unordered_map<std::string, std::shared_ptr<const QueryItem>> items;
};

DEF_EX(CommonQueryComposerException, ManagerException,
       "Common QueryComposer exception");
DEF_EX(NullptrQueryComposerException, CommonQueryComposerException,
       "Can't add nullptr to query items list");
DEF_EX(DuplicateQueryComposerException, CommonQueryComposerException,
       "Duplicate type in list");

#endif

