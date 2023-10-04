#ifndef _GENERICUIITERATOR_HPP_
#define _GENERICUIITERATOR_HPP_

#include "GenericUiIterator.h"

template <typename Type>
GenericUiIterator<Type>::GenericUiIterator(std::shared_ptr<IRepositoryIterator<Type>> iter)
    : iter(iter)
{
    if (nullptr == iter)
        throw;
}

template <typename Type>
void GenericUiIterator<Type>::next(void)
{
    this->iter->next();
}

template <typename Type>
bool GenericUiIterator<Type>::notEqual(std::shared_ptr<const InnerIter> iter) const
{
    std::shared_ptr<const GenericUiIterator> citer = std::dynamic_pointer_cast<const GenericUiIterator>(iter);

    if (nullptr == citer)
        throw;

    return this->iter->notEqual(citer->iter);
}

template <typename Type>
GenericUiSet<Type>::GenericUiSet(std::shared_ptr<IRepositorySet<Type>> set)
    : set(set)
{
    if (nullptr == set)
        throw;
}

template <typename Type>
std::shared_ptr<IAdminModel::InnerIter> GenericUiSet<Type>::begin(void)
{
    return std::make_shared<GenericUiIterator<Type>>(this->set->begin());
}

template <typename Type>
std::shared_ptr<IAdminModel::InnerIter> GenericUiSet<Type>::end(void)
{
    return std::make_shared<GenericUiIterator<Type>>(this->set->end());
}

#endif

