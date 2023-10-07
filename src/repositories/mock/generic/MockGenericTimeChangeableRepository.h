#ifndef _MOCKGENERICTIMECHANGEABLEREPOSITORY_H_
#define _MOCKGENERICTIMECHANGEABLEREPOSITORY_H_

#include <memory>
#include <list>
#include <unordered_map>

#include "IWriteRepository.h"
#include "ITimeChangeableRepository.h"

#include "IQueryable.h"
#include "ICriteriaVisitorResult.h"

template <typename T>
class MockTimeChangeableRepositoryIterator : public ITimeChangeableRepositoryIterator<T>
{
    public:
        MockTimeChangeableRepositoryIterator(typename std::list<T>::const_iterator iter);
        virtual ~MockTimeChangeableRepositoryIterator(void) override = default;
        virtual T get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<T>> iter) override;

    private:
        typename std::list<T>::const_iterator iter;
};

template <typename T>
class MockTimeChangeableRepositoryIdIterator : public IRepositoryIdIterator
{
    public:
        MockTimeChangeableRepositoryIdIterator(typename std::unordered_map<unsigned long long, std::list<T>>::const_iterator iter);
        virtual ~MockTimeChangeableRepositoryIdIterator(void) override = default;
        virtual unsigned long long get(void) override;
        virtual void next() override;
        virtual bool notEqual(std::shared_ptr<IRepositoryIdIterator> iter) override;

    private:
        typename std::unordered_map<unsigned long long, std::list<T>>::const_iterator iter;
};

template <typename T>
class MockTimeChangeableRepositorySet : public ITimeChangeableRepositorySet<T>
{
    public:
        using Interpreter = ICriteriaVisitorResult<std::shared_ptr<IQueryableFilter<T>>>;

    public:
        MockTimeChangeableRepositorySet(const std::list<T> &container,
                                        std::shared_ptr<Interpreter> interpreter);
        MockTimeChangeableRepositorySet(const std::list<T> &container,
                                        std::shared_ptr<IQueryableFilter<T>> filter);
        virtual ~MockTimeChangeableRepositorySet(void) override = default;
        virtual std::shared_ptr<IRepositoryIdIterator> begin(void) override;
        virtual std::shared_ptr<IRepositoryIdIterator> end(void) override;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> beginId(std::shared_ptr<IRepositoryIdIterator> iter) override;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> endId(std::shared_ptr<IRepositoryIdIterator> iter) override;

    private:
        void splitInGroups(const std::list<T> &container);

    private:
        std::unordered_map<unsigned long long, std::list<T>> container;
        std::shared_ptr<Interpreter> interpreter = nullptr;
        std::shared_ptr<IQueryableFilter<T>> filter = nullptr;
};

template <typename T>
class MockGenericTimeChangeableRepository : public IWriteRepository<T>, public ITimeChangeableRepository<T>
{
    public:
        virtual ~MockGenericTimeChangeableRepository(void) override = default;
        virtual void create(const T &item) override;
        virtual void update(const T &item) override;
        virtual void erase(const T &item) override;
        virtual void erase(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<T>> get(const ICriteria &criteria) override;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<T>> getAll(void) override;

    private:
        std::list<T> container;
};

#include "MockGenericTimeChangeableRepository.hpp"

#endif

