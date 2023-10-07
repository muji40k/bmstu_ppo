#ifndef _GENERICUITIMECHANGEABLEITERATOR_H_
#define _GENERICUITIMECHANGEABLEITERATOR_H_

#include "IAdminModel.h"
#include "ITimeChangeableRepository.h"

template <typename Type>
class GenericUiTimeChangeableIterator : public IAdminModel::InnerIter
{
    public:
        GenericUiTimeChangeableIterator(std::shared_ptr<ITimeChangeableRepositorySet<Type>> set,
                                        std::shared_ptr<IRepositoryIdIterator> id_iter);
        virtual ~GenericUiTimeChangeableIterator(void) override = default;
        virtual void next(void) override;
        virtual IAdminModel::Map get(void) const override;
        virtual bool notEqual(std::shared_ptr<const InnerIter> iter) const override;

    private:
        std::shared_ptr<ITimeChangeableRepositorySet<Type>> set;
        std::shared_ptr<IRepositoryIdIterator> id_iter;
        std::shared_ptr<IRepositoryIdIterator> id_end;
        std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> iter = nullptr;
        std::shared_ptr<ITimeChangeableRepositoryIterator<Type>> end = nullptr;
};

template <typename Type>
class GenericUiTimeChangeableSet : public IAdminModel::InnerSet
{
    public:
        GenericUiTimeChangeableSet(std::shared_ptr<ITimeChangeableRepositorySet<Type>> set);
        virtual ~GenericUiTimeChangeableSet(void) override = default;
        virtual std::shared_ptr<IAdminModel::InnerIter> begin(void) override;
        virtual std::shared_ptr<IAdminModel::InnerIter> end(void) override;

    private:
        std::shared_ptr<ITimeChangeableRepositorySet<Type>> set;
};

#include "GenericUiTimeChangeableIterator.hpp"

#endif

