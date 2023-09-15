#ifndef _MOCKGENERICREPOSITORY_HPP_
#define _MOCKGENERICREPOSITORY_HPP_

#include "MockGenericRepository.h"
#include "MockCriteriaInterpreter.h"

template <typename T>
MockRepositoryIterator<T>::MockRepositoryIterator(typename std::list<T>::const_iterator iter,
                                                  typename std::list<T>::const_iterator end,
                                                  std::shared_ptr<IQueryableFilter<T>> filter)
    : filter(filter), iter(iter), end(end)
{
    if (end == iter)
        return;

    if (!this->filter->check(*this->iter))
        this->next();
}

template <typename T>
T MockRepositoryIterator<T>::get(void)
{
    return *this->iter;
}

template <typename T>
void MockRepositoryIterator<T>::next()
{
    if (this->end == this->iter)
        return;

    while (this->end != ++this->iter && !this->filter->check(*this->iter));
}

template <typename T>
bool MockRepositoryIterator<T>::notEqual(std::shared_ptr<IRepositoryIterator<T>> iter)
{
    std::shared_ptr<MockRepositoryIterator<T>> cast = std::dynamic_pointer_cast<MockRepositoryIterator<T>>(iter);

    if (nullptr == cast)
        throw CALL_EX(IncompatibleRepositoryIteratorException);

    return this->iter != cast->iter;
}

template <typename T>
MockRepositorySet<T>::MockRepositorySet(const std::list<T> &container,
                                        std::shared_ptr<Interpreter> interpreter)
    : container(container)
{
    if (nullptr == interpreter)
        throw CALL_EX(NullptrRepositorySetException);

    this->interpreter = interpreter;
    this->filter = interpreter->result();

    if (nullptr == this->filter)
        throw CALL_EX(NullptrRepositorySetException);
}

template <typename T>
MockRepositorySet<T>::MockRepositorySet(const std::list<T> &container,
                                        std::shared_ptr<IQueryableFilter<T>> filter)
    : container(container)
{
    if (nullptr == filter)
        throw CALL_EX(NullptrRepositorySetException);

    this->filter = filter;
}

template <typename T>
std::shared_ptr<IRepositoryIterator<T>> MockRepositorySet<T>::begin(void)
try
{
    return std::make_shared<MockRepositoryIterator<T>>(this->container.begin(),
                                                       this->container.end(),
                                                       this->filter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositorySetException);
}

template <typename T>
std::shared_ptr<IRepositoryIterator<T>> MockRepositorySet<T>::end(void)
try
{
    return std::make_shared<MockRepositoryIterator<T>>(this->container.end(),
                                                       this->container.end(),
                                                       this->filter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositorySetException);
}

template <typename T>
void MockGenericRepository<T>::create(const T &item)
{
    if (0 == item.id)
    {
        T copy (item);
        copy.id = ++count;
        this->container.push_back(copy);
    }
    else
    {
        if (item.id < count)
            throw CALL_EX(CreateRepositoryException);
        else
        {
            this->count = item.id;
            this->container.push_back(item);
        }
    }
}

template <typename T>
void MockGenericRepository<T>::update(const T &item)
{
    if (0 == item.id)
        throw CALL_EX(UpdateRepositoryException);

    auto iter = this->container.begin();

    for (; this->container.end() != iter && (item.id != (*iter).id); ++iter);

    if (this->container.end() == iter)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    iter = this->container.erase(iter);
    this->container.insert(iter, item);
}

template <typename T>
void MockGenericRepository<T>::erase(const T &item)
{
    if (0 == item.id)
        throw CALL_EX(EraseRepositoryException);

    auto iter = this->container.begin();

    for (; this->container.end() != iter && (item.id != (*iter).id); ++iter);

    if (this->container.end() == iter)
        throw CALL_EX(NoObjectEraseRepositoryException);

    this->container.erase(iter);
}

template <typename T>
void MockGenericRepository<T>::erase(const ICriteria &criteria)
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
std::shared_ptr<IRepositorySet<T>> MockGenericRepository<T>::get(const ICriteria &criteria)
try
{
    std::shared_ptr<MockCriteriaInterpreter<T>> interpreter = std::make_shared<MockCriteriaInterpreter<T>>();
    criteria.accept(*interpreter);

    return std::make_shared<MockRepositorySet<T>>(this->container, interpreter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationReadRepositoryException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaReadRepositoryException, er.what());
}

template <typename T>
std::shared_ptr<IRepositorySet<T>> MockGenericRepository<T>::getAll(void)
try
{
    std::shared_ptr<IQueryableFilter<T>> filter = std::make_shared<AllFilter<T>>();

    return std::make_shared<MockRepositorySet<T>>(this->container, filter);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationReadRepositoryException);
}

#endif

