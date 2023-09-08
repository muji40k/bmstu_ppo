#ifndef _ITIMECHANGEABLEREPOSITORY_H_
#define _ITIMECHANGEABLEREPOSITORY_H_

#include <memory>

#include "repository_exceptions.h"

#include "ICriteria.h"

template <typename T>
class ITimeChangeableRepositoryIterator
{
    public:
        virtual ~ITimeChangeableRepositoryIterator(void) = default;
        virtual T get(void) = 0;
        virtual void next() = 0;
        virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator> iter) = 0;
};

class IRepositoryIdIterator
{
    public:
        virtual ~IRepositoryIdIterator(void) = default;
        virtual unsigned long long get(void) = 0;
        virtual void next() = 0;
        virtual bool notEqual(std::shared_ptr<IRepositoryIdIterator> iter) = 0;
};

template <typename T>
class ITimeChangeableRepositorySet
{
    public:
        virtual ~ITimeChangeableRepositorySet(void) = default;
        virtual std::shared_ptr<IRepositoryIdIterator> begin(void) = 0;
        virtual std::shared_ptr<IRepositoryIdIterator> end(void) = 0;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> beginId(std::shared_ptr<IRepositoryIdIterator>) = 0;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> endId(std::shared_ptr<IRepositoryIdIterator>) = 0;
};

template <typename T>
class ITimeChangeableRepository
{
    public:
        virtual ~ITimeChangeableRepository(void) = default;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<T>> get(const ICriteria &criteria) = 0;
        virtual std::shared_ptr<ITimeChangeableRepositorySet<T>> getAll(void) = 0;
};

DEF_EX(CommonTimeChangeableRepositoryException, RepositoryException,
       "Common Repository exception");
DEF_EX(WrongCriteriaTimeChangeableRepositoryException,
       CommonTimeChangeableRepositoryException,
       "Incorrect criteria passed");

#endif

