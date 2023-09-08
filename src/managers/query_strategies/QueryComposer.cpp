#include "QueryComposer.h"

#include <utility>
#include <algorithm>

QueryComposer::QueryComposer(std::initializer_list<std::shared_ptr<const QueryItem>> items)
{
    for (auto item : items)
        this->add(item);
}

void QueryComposer::add(std::shared_ptr<const QueryItem> item)
{
    if (nullptr == item)
        throw CALL_EX(NullptrQueryComposerException);

    const std::string &type = item->type();

    if (this->items.end() != this->items.find(type))
        throw CALL_EX(DuplicateQueryComposerException);

    this->items.emplace(std::make_pair(type, item));
}

std::list<unsigned long long> QueryComposer::run(AppContext &context, const CriteriaBank &bank) const
{
    std::list<unsigned long long> out;
    auto iter = this->items.begin();

    do
    {
        std::shared_ptr<const QueryItem> item = (*iter).second;
        std::list<unsigned long long> tmp, next;

        try
        {
            std::shared_ptr<const ICriteria> criteria = bank.get(item->type());
            tmp = item->run(context, criteria);
        }
        catch (NotSetCriteriaBankException &)
        {}

        tmp.sort();
        std::set_intersection(out.begin(), out.end(), tmp.begin(), tmp.end(),
                              std::back_inserter(next));
        out = next;
    }
    while(out.size() && this->items.end() != ++iter);

    return out;
}

