#ifndef _IREADREPOSITORY_H_
#define _IREADREPOSITORY_H_

#include <memory>

#include "repository_exceptions.h"

#include "ICriteria.h"

template <typename T>
class IRepositoryIterator
{
    public:
        virtual ~IRepositoryIterator(void) = default;
        virtual T get(void) = 0;
        virtual void next() = 0;
        virtual bool notEqual(std::shared_ptr<IRepositoryIterator> iter) = 0;
};

template <typename T>
class IRepositorySet
{
    public:
        virtual ~IRepositorySet(void) = default;
        virtual std::shared_ptr<IRepositoryIterator<T>> begin(void) = 0;
        virtual std::shared_ptr<IRepositoryIterator<T>> end(void) = 0;
};

template <typename T>
class IReadRepository
{
    public:
        virtual ~IReadRepository(void) = default;
        virtual std::shared_ptr<IRepositorySet<T>> get(const ICriteria &criteria) = 0;
        virtual std::shared_ptr<IRepositorySet<T>> getAll(void) = 0;
};

DEF_EX(CommonReadRepositoryException, RepositoryException,
       "Common Repository exception");
DEF_EX(WrongCriteriaReadRepositoryException, CommonReadRepositoryException,
       "Incorrect criteria passed");

#endif
