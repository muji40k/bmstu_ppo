#ifndef _MOCKVALUECRITERIAMAKERS_HPP_
#define _MOCKVALUECRITERIAMAKERS_HPP_

#include <memory>
#include <unordered_map>
#include <string>

#include "typestring.h"

#include "ValueCriteria.h"

#include "QueryableFilterGeneric.h"
#include "order_functions.h"

template <typename Type>
class MockOrderFunctionGetter
{
    public:
        using Func = bool (*)(const Type &, const Type&);

    public:
        static Func get(const std::string &op)
        {
            auto iter = MockOrderFunctionGetter<Type>::functions.find(op);

            if (MockOrderFunctionGetter<Type>::functions.end() == iter)
                return nullptr;

            return (*iter).second;
        }

    private:
        static const std::unordered_map<std::string, Func> functions;
};

template <typename Type>
const std::unordered_map<std::string, typename MockOrderFunctionGetter<Type>::Func> MockOrderFunctionGetter<Type>::functions =
{
    {"=",  eq<Type>},
    {"!=", ne<Type>},
    {"<",  lt<Type>},
    {"<=", le<Type>},
    {">",  gt<Type>},
    {">=", ge<Type>}
};

template <typename Class>
class MockValueCriteriaMakersCreator
{
    public:
        virtual ~MockValueCriteriaMakersCreator(void) = default;
        virtual std::shared_ptr<IQueryableFilter<Class>> create(const ValueCriteria &criteria) = 0;
};

template <typename Type>
class MockValueCriteriaCreatorSet
{
    public:
        static const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<Type>>> items;
};

template <typename Class>
class MockValueCriteriaMakers
{
    public:
        static std::shared_ptr<IQueryableFilter<Class>> get(const ValueCriteria &criteria)
        {
            auto iter = MockValueCriteriaCreatorSet<Class>::items.find(criteria.field);

            if (MockValueCriteriaCreatorSet<Class>::items.end() == iter)
                return nullptr;

            return (*iter).second->create(criteria);
        }

};

namespace MockValueCriteriaCaster
{
    template <typename Type>
    Type cast(const std::string &value);
}

template <typename Class, typename Type, const Type &(Class::* Getter)(void) const>
class MockClassFieldCreator : public MockValueCriteriaMakersCreator<Class>
{
    public:
        virtual ~MockClassFieldCreator(void) = default;
        virtual std::shared_ptr<IQueryableFilter<Class>> create(const ValueCriteria &criteria)
        {
            return std::make_shared<OrderFilter<Class, Type>>(Getter,
                                                              MockOrderFunctionGetter<Type>::get(criteria.op),
                                                              MockValueCriteriaCaster::cast<Type>(*criteria.value));
        }
};

template <typename Class, typename GClass>
class MockTransitiveFilter : public IQueryableFilter<Class>
{
    public:
        using Getter = const GClass &(Class::*)(void) const;

        MockTransitiveFilter(Getter getter, std::shared_ptr<IQueryableFilter<GClass>> inner)
            : getter(getter), inner(inner) {}
        virtual ~MockTransitiveFilter(void) override = default;
        virtual bool check(const Class &item) const override
        {
            return inner->check((item.*this->getter)());
        }

    private:
        Getter getter;
        std::shared_ptr<IQueryableFilter<GClass>> inner;
};

template <typename Class, typename GClass, typename Type,
          const GClass &(Class::*GGetter)(void) const,
          const Type   &(GClass::*Getter)(void) const>
class MockClassFieldTransitiveCreator : public MockValueCriteriaMakersCreator<Class>
{
    public:
        virtual ~MockClassFieldTransitiveCreator(void) = default;
        virtual std::shared_ptr<IQueryableFilter<Class>> create(const ValueCriteria &criteria)
        {
            return std::make_shared<MockTransitiveFilter<Class, GClass>>(GGetter,
                                                                        std::make_shared<OrderFilter<GClass, Type>>(Getter,
                                                                                                                    MockOrderFunctionGetter<Type>::get(criteria.op),
                                                                                                                    MockValueCriteriaCaster::cast<Type>(*criteria.value)));
        }
};

#endif

