#ifndef _GENERICUICRITERIAPARSER_HPP_
#define _GENERICUICRITERIAPARSER_HPP_

#include "GenericUiCriteriaParser.h"

#include "typestring.h"

#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

template <typename Type>
std::shared_ptr<ValueCriteria> parseCriteria(const IAdminModel::CriteriaMap &map)
{
    return std::make_shared<ValueCriteria>(TypeName::getAttribute<Type>(map.field), map.op, map.value);
}

template <typename Type>
static std::shared_ptr<ICriteriaBuilder> buildCriteria(const std::list<IAdminModel::CriteriaMap> &list)
{
    if (list.empty())
        return nullptr;

    auto iter = list.begin();
    std::shared_ptr<LogicCriteriaBuilder> builder = std::make_shared<LogicCriteriaBuilder>(parseCriteria<Type>(*iter));

    for (; list.end() != iter; ++iter)
        builder->addAND(parseCriteria<Type>(*iter));

    return builder;
}

#endif

