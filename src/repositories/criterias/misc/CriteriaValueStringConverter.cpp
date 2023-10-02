#include "CriteriaValueStringConverter.h"

#include <utility>

CriteriaValueStringConverter::CriteriaValueStringConverter(std::list<std::shared_ptr<Item>> converters)
{
    for (auto item : converters)
    {
        if (nullptr == item)
            throw CALL_EX(NullptrCriteriaValueStringConverterException);

        if (this->converters.end() != this->converters.find(item->type()))
            throw CALL_EX(DuplicateCriteriaValueStringConverterException);

        this->converters.emplace(std::make_pair(item->type(), item));
    }
}

std::string CriteriaValueStringConverter::convert(const std::string &field, const std::string &value) const
{
    auto iter = this->converters.find(field);

    if (this->converters.end() == iter)
        return this->general(value);

    return (*iter).second->apply(value);
}

std::string CriteriaValueStringConverter::general(const std::string &value) const
{
    return value;
}

