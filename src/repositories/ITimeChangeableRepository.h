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
        virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<T>> iter) = 0;
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
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> beginId(std::shared_ptr<IRepositoryIdIterator> iter) = 0;
        virtual std::shared_ptr<ITimeChangeableRepositoryIterator<T>> endId(std::shared_ptr<IRepositoryIdIterator> iter) = 0;
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

DEF_EX(CommonTimeChangeableRepositoryIteratorException, CommonTimeChangeableRepositoryException,
       "Common TimeChangeableRepositoryIterator exception");
DEF_EX(InitializaionTimeChangeableRepositoryIteratorException, CommonTimeChangeableRepositoryIteratorException,
       "Unable to initialize object");
DEF_EX(NullptrTimeChangeableRepositoryIteratorException, CommonTimeChangeableRepositoryIteratorException,
       "Nullptr occured");
DEF_EX(IncompatibleTimeChangeableRepositoryIteratorException, CommonTimeChangeableRepositoryIteratorException,
       "Unable to allocate");

DEF_EX(CommonRepositoryIdIteratorException, CommonTimeChangeableRepositoryException,
       "Common RepositoryIdIterator exception");
DEF_EX(InitializaionRepositoryIdIteratorException, CommonRepositoryIdIteratorException,
       "Unable to initialize object");
DEF_EX(NullptrRepositoryIdIteratorException, CommonRepositoryIdIteratorException,
       "Nullptr occured");
DEF_EX(IncompatibleRepositoryIdIteratorException, CommonRepositoryIdIteratorException,
       "Unable to allocate");

DEF_EX(CommonTimeChangeableRepositorySetException, CommonTimeChangeableRepositoryException,
       "Common TimeChangeableRepositorySet exception");
DEF_EX(InitializaionTimeChangeableRepositorySetException, CommonTimeChangeableRepositorySetException,
       "Unable to initialize object");
DEF_EX(NullptrTimeChangeableRepositorySetException, CommonTimeChangeableRepositorySetException,
       "Nullptr occured");
DEF_EX(AllocationTimeChangeableRepositorySetException, CommonTimeChangeableRepositorySetException,
       "Unable to allocate");
DEF_EX(IncompatibleTimeChangeableRepositorySetException, CommonTimeChangeableRepositorySetException,
       "Unable to allocate");

#endif

