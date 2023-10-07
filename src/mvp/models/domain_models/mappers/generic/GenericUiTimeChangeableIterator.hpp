#ifndef _GENERICUITIMECHANGEABLEITERATOR_HPP_
#define _GENERICUITIMECHANGEABLEITERATOR_HPP_

#include "GenericUiTimeChangeableIterator.h"

template <typename Type>
GenericUiTimeChangeableIterator<Type>::GenericUiTimeChangeableIterator(std::shared_ptr<ITimeChangeableRepositorySet<Type>> set,
                                                                       std::shared_ptr<IRepositoryIdIterator> id_iter)
    : set(set), id_iter(id_iter)
{
    if (nullptr == set || nullptr == id_iter)
        throw;

    this->id_end = this->set->end();

    if (this->id_end->notEqual(this->id_iter))
    {
        this->iter = this->set->beginId(this->id_iter);
        this->end = this->set->endId(this->id_iter);
    }
}

template <typename Type>
void GenericUiTimeChangeableIterator<Type>::next(void)
{
    this->iter->next();

    if (this->end->notEqual(this->iter))
        return;

    this->id_iter->next();

    if (this->id_end->notEqual(this->id_iter))
    {
        this->iter = this->set->beginId(this->id_iter);
        this->end = this->set->endId(this->id_iter);
    }
}

template <typename Type>
bool GenericUiTimeChangeableIterator<Type>::notEqual(std::shared_ptr<const InnerIter> iter) const
{
    std::shared_ptr<const GenericUiTimeChangeableIterator> citer = std::dynamic_pointer_cast<const GenericUiTimeChangeableIterator>(iter);

    if (nullptr == citer)
        throw;

    if (this->id_iter->notEqual(citer->id_iter))
        return true;

    if (!this->id_end->notEqual(this->id_iter))
        return false;

    return this->iter->notEqual(citer->iter);
}

template <typename Type>
GenericUiTimeChangeableSet<Type>::GenericUiTimeChangeableSet(std::shared_ptr<ITimeChangeableRepositorySet<Type>> set)
    : set(set)
{
    if (nullptr == set)
        throw;
}

template <typename Type>
std::shared_ptr<IAdminModel::InnerIter> GenericUiTimeChangeableSet<Type>::begin(void)
{
    return std::make_shared<GenericUiTimeChangeableIterator<Type>>(this->set, this->set->begin());
}

template <typename Type>
std::shared_ptr<IAdminModel::InnerIter> GenericUiTimeChangeableSet<Type>::end(void)
{
    return std::make_shared<GenericUiTimeChangeableIterator<Type>>(this->set, this->set->end());
}

#endif

