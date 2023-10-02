#ifndef _PSQLGENERICITERATOR_HPP_
#define _PSQLGENERICITERATOR_HPP_

#include "PSQLGenericIterator.h"

template <typename Type>
PSQLGenericRepositoryIterator<Type>::PSQLGenericRepositoryIterator(pqxx::result::const_iterator iter)
    : iter(iter)
{}

template <typename Type>
void PSQLGenericRepositoryIterator<Type>::next()
{
    ++this->iter;
}

template <typename Type>
bool PSQLGenericRepositoryIterator<Type>::notEqual(std::shared_ptr<IRepositoryIterator<Type>> iter)
{
    std::shared_ptr<PSQLGenericRepositoryIterator<Type>> citer = std::dynamic_pointer_cast<PSQLGenericRepositoryIterator<Type>>(iter);

    if (nullptr == citer)
        throw CALL_EX(IncompatibleRepositoryIteratorException);

    return this->iter != citer->iter;
}

template <typename Type>
PSQLGenericRepositorySet<Type>::PSQLGenericRepositorySet(std::shared_ptr<pqxx::result> result)
    : result(result)
{
    if (nullptr == result)
        throw CALL_EX(InitializationRepositorySetException);
}

template <typename Type>
std::shared_ptr<IRepositoryIterator<Type>> PSQLGenericRepositorySet<Type>::begin(void)
try
{
    return std::make_shared<PSQLGenericRepositoryIterator<Type>>(this->result->begin());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositorySetException);
}

template <typename Type>
std::shared_ptr<IRepositoryIterator<Type>> PSQLGenericRepositorySet<Type>::end(void)
try
{
    return std::make_shared<PSQLGenericRepositoryIterator<Type>>(this->result->end());
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositorySetException);
}

#endif

