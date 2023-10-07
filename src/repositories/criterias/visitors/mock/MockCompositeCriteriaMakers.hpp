#ifndef _MOCKCOMPOSITECRITERIAMAKERS_HPP_
#define _MOCKCOMPOSITECRITERIAMAKERS_HPP_

#include <unordered_map>
#include <memory>

#include "QueryableFilterGeneric.h"

template <typename Type>
class MockCompositeCriteriaMaker
{
    private:
        using MapFunc = std::shared_ptr<IQueryableFilter<Type>> (*)(const IQueryableFilter<Type> &, const IQueryableFilter<Type> &);

    public:
        static std::shared_ptr<IQueryableFilter<Type>> get(const IQueryableFilter<Type> &c1, const std::string &op, const IQueryableFilter<Type> &c2)
        {
            static const std::unordered_map<std::string, MapFunc> map =
            {
                {"and", MockCompositeCriteriaMaker<Type>::And},
                {"or",  MockCompositeCriteriaMaker<Type>::Or}
            };

            auto iter = map.find(op);

            if (map.end() == iter)
                return nullptr;

            return (*iter).second(c1, c2);
        }

    private:
        static std::shared_ptr<IQueryableFilter<Type>> And(const IQueryableFilter<Type> &qf1, const IQueryableFilter<Type> &qf2)
        {
            return std::make_shared<AndFilter<Type>>(qf1, qf2);
        }

        static std::shared_ptr<IQueryableFilter<Type>> Or(const IQueryableFilter<Type> &qf1, const IQueryableFilter<Type> &qf2)
        {
            return std::make_shared<OrFilter<Type>>(qf1, qf2);
        }
};

#endif

