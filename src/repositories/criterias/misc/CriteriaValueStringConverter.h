#ifndef _CRITERIAVALUESTRINGCONVERTER_H_
#define _CRITERIAVALUESTRINGCONVERTER_H_

#include <memory>
#include <string>
#include <unordered_map>
#include <list>

#include "repository_exceptions.h"

class CriteriaValueStringConverter
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual const std::string &type(void) const = 0;
                virtual std::string apply(const std::string &value) = 0;
        };

    public:
        CriteriaValueStringConverter(std::list<std::shared_ptr<Item>> converters);
        virtual ~CriteriaValueStringConverter(void) = default;
        std::string convert(const std::string &field, const std::string &value) const;

    private:
        virtual std::string general(const std::string &value) const;

    private:
        std::unordered_map<std::string, std::shared_ptr<Item>> converters;
};

DEF_EX(CommonCriteriaValueStringConverterException, RepositoryException,
       "Common CriteriaValueStringConverter Exception");
DEF_EX(NullptrCriteriaValueStringConverterException, CommonCriteriaValueStringConverterException,
       "Nullptr occured");
DEF_EX(DuplicateCriteriaValueStringConverterException, CommonCriteriaValueStringConverterException,
       "Duplicate converter found");


#endif

