#ifndef _OSTREAM_OVERRIDES_H_
#define _OSTREAM_OVERRIDES_H_

#include <iostream>
#include <ctime>
#include <list>
#include <vector>

#include "Human.h"
#include "Place.h"
#include "Language.h"
#include "User.h"
#include "HumanLanguage.h"

#include "QueryableFilterGeneric.h"

#include "ICriteriaVisitor.h"
#include "ICriteriaVisitorResult.h"

#include "UnaryFieldCriteria.h"
#include "UnaryCompositeCriteria.h"
#include "FieldCriteria.h"
#include "ValueCriteria.h"
#include "CompositeCriteria.h"

std::string getTime(const std::time_t &time)
{
    std::string out = std::asctime(std::localtime(&time));

    return std::string(out.begin(), out.end() - 1);
}

std::ostream &operator << (std::ostream &stream, const std::list<std::time_t> &lst)
{
    stream << "[";

    for (auto iter = lst.begin(); lst.end() != iter;)
    {
        stream << '"' << getTime(*iter) << '"';

        if (lst.end() != ++iter)
            stream << ", ";
    }

    stream << "]";

    return stream;
}

template <typename T>
std::ostream &operator << (std::ostream &stream, const std::list<T> &lst)
{
    stream << "[";

    for (auto iter = lst.begin(); lst.end() != iter;)
    {
        stream << *iter;

        if (lst.end() != ++iter)
            stream << ", ";
    }

    stream << "]";

    return stream;
}

template <typename T>
std::ostream &operator << (std::ostream &stream, const std::vector<T> &lst)
{
    stream << "[";

    for (auto iter = lst.begin(); lst.end() != iter;)
    {
        stream << *iter;

        if (lst.end() != ++iter)
            stream << ", ";
    }

    stream << "]";

    return stream;
}

std::ostream &operator << (std::ostream &stream, const Place &item)
{
    stream << "{\"id\": " << item.id
           << ", \"type\": \"" << item.type << '"'
           << ", \"name\": \"" << item.name << '"'
           << ", \"area\": " << item.area
           << ", \"continent\": \"" << item.continent << '"'
           << ", \"valid_from\": \"" << getTime(item.validFrom) << '"'
           << "}";

    return stream;
}

std::ostream &operator << (std::ostream &stream, const Language &item)
{
    stream << "{\"id\": " << item.id
           << ", \"name\": \"" << item.name << '"'
           << ", \"family\": \"" << item.family << '"'
           << ", \"valid_from\": \"" << getTime(item.validFrom) << '"'
           << "}";

    return stream;
}

std::ostream &operator << (std::ostream &stream, const Human &item)
{
    stream << "{\"id\": " << item.id
           << ", \"first_name\": \"" << item.firstName << '"'
           << ", \"last_name\": \"" << item.lastName << '"';

    if (item.isPatronymic())
        stream << ", \"patronymic\": \"" << item.patronymic << '"';

    stream << ", \"birth_place\": " << item.birthPlace
           << ", \"valid_from\": \"" << getTime(item.validFrom) << '"'
           << "}";

    return stream;
}

std::ostream &operator << (std::ostream &stream, const User &item)
{
    stream << "{\"id\": " << item.id
           << ", \"name\": \"" << item.name << '"'
           << ", \"email\": \"" << item.email << '"'
           << ", \"password\": \"" << item.password << "\"}";

    return stream;
}

std::ostream &operator << (std::ostream &stream, const HumanLanguage &hl)
{
    std::list<Language> lst = hl.get(AllFilter<Language>());

    stream << "{\"id\": " << hl.id
           << ", \"languages\": [";

    for (auto iter = lst.begin(); lst.end() != iter;)
    {
        stream << "{\"language\": " << *iter
               << ", \"level\": \"" << hl.getLevel(*iter) << '"'
               << "}";

        if (lst.end() != ++iter)
            stream << ", ";
    }

    stream << "], \"valid_from\": \"" << getTime(hl.validFrom) << "\"}";

    return stream;
}

class Criteria2StringVisitor : public ICriteriaVisitor, public ICriteriaVisitorResult<std::string>
{};

class CriteriaJSONVisitor : public Criteria2StringVisitor
{
    public:
        virtual ~CriteriaJSONVisitor(void) override = default;

        virtual void visit(const UnaryFieldCriteria &criteria) override
        {
            this->res = std::string("{\"field\": \"") + criteria.field + '"'
                        + ", \"operator\": \"" + criteria.op + "\"}";
        }

        virtual void visit(const UnaryCompositeCriteria &criteria) override
        {
            std::string out = "{\"criteria\": ";
            criteria.criteria->accept(*this);
            out += this->res;
            out += std::string(", \"operator\": \"") + criteria.op + "\"}";

            this->res = out;
        }

        virtual void visit(const ValueCriteria &criteria) override
        {
            this->res = std::string("{\"field\": \"") + criteria.field + '"'
                         + ", \"operator\": \"" + criteria.op + '"'
                         + ", \"value\": \"" + criteria.value + "\"}";
        }

        virtual void visit(const FieldCriteria &criteria) override
        {
            this->res = std::string("{\"field1\": \"") + criteria.field1 + '"'
                         + ", \"operator\": \"" + criteria.op + '"'
                         + ", \"field1\": \"" + criteria.field2 + "\"}";
        }

        virtual void visit(const CompositeCriteria &criteria) override
        {
            std::string out = "{\"criteria1\": ";
            criteria.criteria1->accept(*this);
            out += this->res + ", \"operator\": \"" + criteria.op + '"'
                   + ", \"criteria2\": ";
            criteria.criteria2->accept(*this);
            out += this->res + "}";

            this->res = out;
        }

        virtual const std::string &result(void) const override
        {
            return this->res;
        }

    private:
        std::string res;
};

class CriteriaExpressionVisitor : public Criteria2StringVisitor
{
    public:
        virtual ~CriteriaExpressionVisitor(void) override = default;

        virtual void visit(const UnaryFieldCriteria &criteria) override
        {
            this->res = std::string("(") + criteria.op + " " + criteria.field + ")";
        }

        virtual void visit(const UnaryCompositeCriteria &criteria) override
        {
            criteria.criteria->accept(*this);
            this->res = std::string("(") + criteria.op + " " + this->res + ")";
        }

        virtual void visit(const ValueCriteria &criteria) override
        {
            this->res = std::string("(") + criteria.field + " " + criteria.op
                        + " " + criteria.value + ")";
        }

        virtual void visit(const FieldCriteria &criteria) override
        {
            this->res = std::string("(") + criteria.field1 + " " + criteria.op
                        + " " + criteria.field2 + ")";
        }

        virtual void visit(const CompositeCriteria &criteria) override
        {
            std::string out = "(";
            criteria.criteria1->accept(*this);
            out += this->res + " " + criteria.op + " ";
            criteria.criteria2->accept(*this);
            out += this->res + ")";

            this->res = out;
        }

        virtual const std::string &result(void) const override
        {
            return this->res;
        }

    private:
        std::string res;
};

class CriteriaPrintVisitor : public ICriteriaVisitor
{
    public:
        CriteriaPrintVisitor(std::ostream &stream, Criteria2StringVisitor &visitor) : stream(stream), visitor(visitor) {}
        virtual ~CriteriaPrintVisitor(void) override = default;

        virtual void visit(const UnaryFieldCriteria &criteria) override
        {
            criteria.accept(this->visitor);
            this->stream << this->visitor.result();
        }

        virtual void visit(const UnaryCompositeCriteria &criteria) override
        {
            criteria.accept(this->visitor);
            this->stream << this->visitor.result();
        }

        virtual void visit(const ValueCriteria &criteria) override
        {
            criteria.accept(this->visitor);
            this->stream << this->visitor.result();
        }

        virtual void visit(const FieldCriteria &criteria) override
        {
            criteria.accept(this->visitor);
            this->stream << this->visitor.result();
        }

        virtual void visit(const CompositeCriteria &criteria) override
        {
            criteria.accept(this->visitor);
            this->stream << this->visitor.result();
        }

    private:
        std::ostream &stream;
        Criteria2StringVisitor &visitor;
};

#endif

