#ifndef _PSQLGENERICTIMECHANGEABLEITERATOR_H_
#define _PSQLGENERICTIMECHANGEABLEITERATOR_H_

#include <pqxx/pqxx>

#include "ITimeChangeableRepository.h"

template <typename Type>
class PSQLGenericTimeChangeableRepositoryIterator : public ITimeChangeableRepositoryIterator<Type>
{
    public:
        PSQLGenericTimeChangeableRepositoryIterator(pqxx::result::const_iterator iter);
        virtual ~PSQLGenericTimeChangeableRepositoryIterator(void) = default;
        virtual Type get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> iter) override;

    private:
        pqxx::result::const_iterator iter;
};

class PSQLGenericRepositoryIdIterator : public IRepositoryIdIterator
{
    public:
        PSQLGenericRepositoryIdIterator(pqxx::result::const_iterator iter);
        virtual ~PSQLGenericRepositoryIdIterator(void) = default;
        virtual unsigned long long get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<IRepositoryIdIterator> iter) override;

    private:
        pqxx::result::const_iterator iter;
};

template <typename Type>
class PSQLGenericTimeChangeableRepositorySet : public ITimeChangeableRepositorySet<Type>
{
    public:
        PSQLGenericTimeChangeableRepositorySet(std::shared_ptr<pqxx::connection> connection,
                                               std::string query="");
        virtual ~PSQLGenericTimeChangeableRepositorySet(void) override = default;
        virtual std::shared_ptr<IRepositoryIdIterator> begin(void) override;
        virtual std::shared_ptr<IRepositoryIdIterator> end(void) override;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> beginId(std::shared_ptr<IRepositoryIdIterator> iter) override;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> endId(std::shared_ptr<IRepositoryIdIterator> iter) override;

    private:
        std::shared_ptr<pqxx::result> makeIdResult(void);
        std::shared_ptr<pqxx::result> makeResult(unsigned long long id);

    private:
        void getIdResult(void);
        std::shared_ptr<pqxx::result> getResult(unsigned long long id);

    private:
        std::shared_ptr<pqxx::connection> connection;
        const std::string query;
        std::shared_ptr<pqxx::result> id_result = nullptr;
        std::unordered_map<unsigned long long, std::shared_ptr<pqxx::result>> result;
};

#include "PSQLGenericTimeChangeableIterator.hpp"

#endif

