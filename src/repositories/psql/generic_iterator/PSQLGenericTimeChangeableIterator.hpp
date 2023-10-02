#ifndef _PSQLGENERICTIMECHANGEABLEITERATOR_HPP_
#define _PSQLGENERICTIMECHANGEABLEITERATOR_HPP_

#include "PSQLGenericTimeChangeableIterator.h"

#include <utility>

template <typename Type>
PSQLGenericTimeChangeableRepositoryIterator<Type>::PSQLGenericTimeChangeableRepositoryIterator(pqxx::result::const_iterator iter)
    : iter(iter)
{}

template <typename Type>
void PSQLGenericTimeChangeableRepositoryIterator<Type>::next()
{
    ++this->iter;
}

template <typename Type>
bool PSQLGenericTimeChangeableRepositoryIterator<Type>::notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> iter)
{
    std::shared_ptr<PSQLGenericTimeChangeableRepositoryIterator<Type>> citer = std::dynamic_pointer_cast<PSQLGenericTimeChangeableRepositoryIterator<Type>>(iter);

    if (nullptr == citer)
        throw CALL_EX(IncompatibleTimeChangeableRepositoryIteratorException);

    return this->iter != citer->iter;
}

template <typename Type>
PSQLGenericTimeChangeableRepositorySet<Type>::PSQLGenericTimeChangeableRepositorySet(std::shared_ptr<pqxx::connection> connection,
                                                                                     std::string query)
    : connection(connection), query("" == query ? "true" : query)
{
    if (nullptr == connection)
        throw CALL_EX(NullptrTimeChangeableRepositorySetException);
}

template <typename Type>
std::shared_ptr<IRepositoryIdIterator> PSQLGenericTimeChangeableRepositorySet<Type>::begin(void)
try
{
    this->getIdResult();

    return std::make_shared<PSQLGenericRepositoryIdIterator>(this->id_result->begin());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonTimeChangeableRepositorySetException, er.what());
}

template <typename Type>
std::shared_ptr<IRepositoryIdIterator> PSQLGenericTimeChangeableRepositorySet<Type>::end(void)
try
{
    this->getIdResult();

    return std::make_shared<PSQLGenericRepositoryIdIterator>(this->id_result->end());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonTimeChangeableRepositorySetException, er.what());
}

template <typename Type>
std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> PSQLGenericTimeChangeableRepositorySet<Type>::beginId(std::shared_ptr<IRepositoryIdIterator> iter)
try
{
    if (nullptr == std::dynamic_pointer_cast<PSQLGenericRepositoryIdIterator>(iter))
        throw CALL_EX(IncompatibleTimeChangeableRepositorySetException);

    std::shared_ptr<pqxx::result> result = this->getResult(iter->get());

    return std::make_shared<PSQLGenericTimeChangeableRepositoryIterator<Type>>(result->begin());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonTimeChangeableRepositorySetException, er.what());
}

template <typename Type>
std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> PSQLGenericTimeChangeableRepositorySet<Type>::endId(std::shared_ptr<IRepositoryIdIterator> iter)
try
{
    if (nullptr == std::dynamic_pointer_cast<PSQLGenericRepositoryIdIterator>(iter))
        throw CALL_EX(IncompatibleTimeChangeableRepositorySetException);

    std::shared_ptr<pqxx::result> result = this->getResult(iter->get());

    return std::make_shared<PSQLGenericTimeChangeableRepositoryIterator<Type>>(result->end());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonTimeChangeableRepositorySetException, er.what());
}

template <typename Type>
void PSQLGenericTimeChangeableRepositorySet<Type>::getIdResult(void)
{
    if (nullptr != this->id_result)
        return;

    this->id_result = this->makeIdResult();
}

template <typename Type>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<Type>::getResult(unsigned long long id)
{
    auto iter = this->result.find(id);

    if (this->result.end() != iter)
        return (*iter).second;

    std::shared_ptr<pqxx::result> out = this->makeResult(id);
    this->result.emplace(std::pair(id, out));

    return out;
}

#endif

