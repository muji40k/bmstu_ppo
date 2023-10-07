#ifndef _MOCKGENERICREPOSITORY_H_
#define _MOCKGENERICREPOSITORY_H_

#include <list>
#include <memory>

#include "IReadRepository.h"
#include "IWriteRepository.h"

#include "IQueryable.h"
#include "ICriteriaVisitorResult.h"

template <typename T>
class MockRepositoryIterator : public IRepositoryIterator<T>
{
    public:
        MockRepositoryIterator(typename std::list<T>::const_iterator iter,
                               typename std::list<T>::const_iterator end,
                               std::shared_ptr<IQueryableFilter<T>> filter);
        virtual ~MockRepositoryIterator(void) override = default;
        virtual T get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<IRepositoryIterator<T>> iter) override;

    private:
        std::shared_ptr<IQueryableFilter<T>> filter;
        typename std::list<T>::const_iterator iter;
        typename std::list<T>::const_iterator end;
};

template <typename T>
class MockRepositorySet : public IRepositorySet<T>
{
    public:
        using Interpreter = ICriteriaVisitorResult<std::shared_ptr<IQueryableFilter<T>>>;

    public:
        MockRepositorySet(const std::list<T> &container,
                          std::shared_ptr<Interpreter> interpreter);
        MockRepositorySet(const std::list<T> &container,
                          std::shared_ptr<IQueryableFilter<T>> filter);
        virtual ~MockRepositorySet(void) override = default;
        virtual std::shared_ptr<IRepositoryIterator<T>> begin(void) override;
        virtual std::shared_ptr<IRepositoryIterator<T>> end(void) override;

    private:
        const std::list<T> &container;
        std::shared_ptr<Interpreter> interpreter = nullptr;
        std::shared_ptr<IQueryableFilter<T>> filter = nullptr;
};

template <typename T>
class MockGenericRepository : public IWriteRepository<T>, public IReadRepository<T>
{
    public:
        virtual ~MockGenericRepository(void) override = default;
        virtual void create(const T &item) override;
        virtual void update(const T &item) override;
        virtual void erase(const T &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<T>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<IRepositorySet<T>> getAll(void) override;

    private:
        std::list<T> container;
        size_t count = 0;
};

#include "MockGenericRepository.hpp"

#endif

