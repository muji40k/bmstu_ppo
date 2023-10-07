#ifndef _PSQLGENERICITERATOR_H_
#define _PSQLGENERICITERATOR_H_

#include <pqxx/pqxx>

#include "IReadRepository.h"

template <typename Type>
class PSQLGenericRepositoryIterator : public IRepositoryIterator<Type>
{
    public:
        PSQLGenericRepositoryIterator(pqxx::result::const_iterator iter);
        virtual ~PSQLGenericRepositoryIterator(void) = default;
        virtual Type get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<IRepositoryIterator<Type>> iter) override;

    private:
        pqxx::result::const_iterator iter;
};

template <typename Type>
class PSQLGenericRepositorySet : public IRepositorySet<Type>
{
    public:
        PSQLGenericRepositorySet(std::shared_ptr<pqxx::result> result);
        virtual ~PSQLGenericRepositorySet(void) override = default;
        virtual std::shared_ptr<IRepositoryIterator<Type>> begin(void) override;
        virtual std::shared_ptr<IRepositoryIterator<Type>> end(void) override;

    private:
        std::shared_ptr<pqxx::result> result;
};

#include "PSQLGenericIterator.hpp"

#endif

