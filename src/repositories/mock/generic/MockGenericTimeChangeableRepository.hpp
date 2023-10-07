#ifndef _MOCKGENERICTIMECHANGEABLEREPOSITORY_HPP_
#define _MOCKGENERICTIMECHANGEABLEREPOSITORY_HPP_

#include <utility>

#include "MockGenericTimeChangeableRepository.h"
#include "MockCriteriaInterpreter.h"

template <typename T>
MockTimeChangeableRepositoryIterator<T>::MockTimeChangeableRepositoryIterator(typename std::list<T>::const_iterator iter)
    : iter(iter)
{}

template <typename T>
T MockTimeChangeableRepositoryIterator<T>::get(void)
{
    return *this->iter;
}

template <typename T>
void MockTimeChangeableRepositoryIterator<T>::next()
{
    ++this->iter;
}

template <typename T>
bool MockTimeChangeableRepositoryIterator<T>::notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<T>> iter)
{
    std::shared_ptr<MockTimeChangeableRepositoryIterator<T>> cast = std::dynamic_pointer_cast<MockTimeChangeableRepositoryIterator<T>>(iter);

    if (nullptr == cast)
        throw CALL_EX(IncompatibleTimeChangeableRepositoryIteratorException);

    return this->iter != cast->iter;
}

template <typename T>
MockTimeChangeableRepositoryIdIterator<T>::MockTimeChangeableRepositoryIdIterator(typename std::unordered_map<unsigned long long, std::list<T>>::const_iterator iter)
    : iter(iter)
{}

template <typename T>
unsigned long long MockTimeChangeableRepositoryIdIterator<T>::get(void)
{
    return (*this->iter).first;
}

template <typename T>
void MockTimeChangeableRepositoryIdIterator<T>::next()
{
    ++this->iter;
}

template <typename T>
bool MockTimeChangeableRepositoryIdIterator<T>::notEqual(std::shared_ptr<IRepositoryIdIterator> iter)
{
    std::shared_ptr<MockTimeChangeableRepositoryIdIterator<T>> cast = std::dynamic_pointer_cast<MockTimeChangeableRepositoryIdIterator<T>>(iter);

    if (nullptr == cast)
        throw CALL_EX(IncompatibleRepositoryIdIteratorException);

    return this->iter != cast->iter;
}

template <typename T>
MockTimeChangeableRepositorySet<T>::MockTimeChangeableRepositorySet(const std::list<T> &container,
                                                                    std::shared_ptr<Interpreter> interpreter)
{
    if (nullptr == interpreter)
        throw CALL_EX(NullptrTimeChangeableRepositorySetException);

    this->interpreter = interpreter;
    this->filter = interpreter->result();

    if (nullptr == this->filter)
        throw CALL_EX(NullptrTimeChangeableRepositorySetException);

    this->splitInGroups(container);
}

template <typename T>
MockTimeChangeableRepositorySet<T>::MockTimeChangeableRepositorySet(const std::list<T> &container,
                                                                    std::shared_ptr<IQueryableFilter<T>> filter)
{
    if (nullptr == filter)
        throw CALL_EX(NullptrTimeChangeableRepositorySetException);

    this->filter = filter;
    this->splitInGroups(container);
}

template <typename T>
std::shared_ptr<IRepositoryIdIterator> MockTimeChangeableRepositorySet<T>::begin(void)
try
{
    return std::make_shared<MockTimeChangeableRepositoryIdIterator<T>>(this->container.begin());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <typename T>
std::shared_ptr<IRepositoryIdIterator> MockTimeChangeableRepositorySet<T>::end(void)
try
{
    return std::make_shared<MockTimeChangeableRepositoryIdIterator<T>>(this->container.end());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <typename T>
std::shared_ptr<ITimeChangeableRepositoryIterator<T>> MockTimeChangeableRepositorySet<T>::beginId(std::shared_ptr<IRepositoryIdIterator> iter)
try
{
    if (nullptr == std::dynamic_pointer_cast<MockTimeChangeableRepositoryIdIterator<T>>(iter))
        throw CALL_EX(IncompatibleTimeChangeableRepositorySetException);

    auto initer = this->container.find(iter->get());

    return std::make_shared<MockTimeChangeableRepositoryIterator<T>>((*initer).second.begin());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <typename T>
std::shared_ptr<ITimeChangeableRepositoryIterator<T>> MockTimeChangeableRepositorySet<T>::endId(std::shared_ptr<IRepositoryIdIterator> iter)
try
{
    if (nullptr == std::dynamic_pointer_cast<MockTimeChangeableRepositoryIdIterator<T>>(iter))
        throw CALL_EX(IncompatibleTimeChangeableRepositorySetException);

    auto initer = this->container.find(iter->get());

    return std::make_shared<MockTimeChangeableRepositoryIterator<T>>((*initer).second.end());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <typename T>
bool sorTime(const T &a, const T &b)
{
    return a.validFrom > b.validFrom;
}

template <typename T>
void MockTimeChangeableRepositorySet<T>::splitInGroups(const std::list<T> &container)
{
    for (auto item : container)
        if (this->filter->check(item))
        {
            auto iter = this->container.find(item.id);

            if (this->container.end() == iter)
                this->container.emplace(std::make_pair(*item.id, std::list<T>({item})));
            else
                (*iter).second.push_back(item);
        }

    for (auto iter = this->container.begin();
         this->container.end() != iter;
         ++iter)
        (*iter).second.sort(sorTime<T>);
}

template <typename T>
void MockGenericTimeChangeableRepository<T>::create(const T &item)
{
    if (0 == item.id)
        throw CALL_EX(CreateRepositoryException);

    this->container.push_back(item);
}

template <typename T>
void MockGenericTimeChangeableRepository<T>::update(const T &item)
{
    if (0 == item.id)
        throw CALL_EX(UpdateRepositoryException);

    auto iter = this->container.begin();

    for (; this->container.end() != iter && item != (*iter); ++iter);

    if (this->container.end() == iter)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    iter = this->container.erase(iter);
    this->container.insert(iter, item);
}

template <typename T>
void MockGenericTimeChangeableRepository<T>::erase(const T &item)
{
    if (0 == item.id)
        throw CALL_EX(EraseRepositoryException);

    auto iter = this->container.begin();

    for (; this->container.end() != iter && item != (*iter); ++iter);

    if (this->container.end() == iter)
        throw CALL_EX(NoObjectEraseRepositoryException);

    this->container.erase(iter);
}

template <typename T>
void MockGenericTimeChangeableRepository<T>::erase(const ICriteria &criteria)
try
{
    MockCriteriaInterpreter<T> interpreter;
    criteria.accept(interpreter);

    std::shared_ptr<IQueryableFilter<T>> filter = interpreter.result();

    auto iter = this->container.begin();

    while (this->container.end() != iter)
        if (filter->check(*iter))
            iter = this->container.erase(iter);
        else
            ++iter;
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaWriteRepositoryException, er.what());
}

template <typename T>
std::shared_ptr<ITimeChangeableRepositorySet<T>> MockGenericTimeChangeableRepository<T>::get(const ICriteria &criteria)
try
{
    std::shared_ptr<MockCriteriaInterpreter<T>> interpreter = std::make_shared<MockCriteriaInterpreter<T>>();
    criteria.accept(*interpreter);

    return std::make_shared<MockTimeChangeableRepositorySet<T>>(this->container, interpreter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

template <typename T>
std::shared_ptr<ITimeChangeableRepositorySet<T>> MockGenericTimeChangeableRepository<T>::getAll(void)
try
{
    std::shared_ptr<IQueryableFilter<T>> filter = std::make_shared<AllFilter<T>>();

    return std::make_shared<MockTimeChangeableRepositorySet<T>>(this->container, filter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationMockCriteriaInterpreterException);
}

#endif

