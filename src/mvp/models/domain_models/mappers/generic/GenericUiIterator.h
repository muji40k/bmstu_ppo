#ifndef _GENERICUIITERATOR_H_
#define _GENERICUIITERATOR_H_

#include "IAdminModel.h"
#include "IReadRepository.h"

template <typename Type>
class GenericUiIterator : public IAdminModel::InnerIter
{
    public:
        GenericUiIterator(std::shared_ptr<IRepositoryIterator<Type>> iter);
        virtual ~GenericUiIterator(void) override = default;
        virtual void next(void) override;
        virtual IAdminModel::Map get(void) const override;
        virtual bool notEqual(std::shared_ptr<const InnerIter> iter) const override;

    private:
        std::shared_ptr<IRepositoryIterator<Type>> iter;
};

template <typename Type>
class GenericUiSet : public IAdminModel::InnerSet
{
    public:
        GenericUiSet(std::shared_ptr<IRepositorySet<Type>> set);
        virtual ~GenericUiSet(void) override = default;
        virtual std::shared_ptr<IAdminModel::InnerIter> begin(void) override;
        virtual std::shared_ptr<IAdminModel::InnerIter> end(void) override;

    private:
        std::shared_ptr<IRepositorySet<Type>> set;
};

#include "GenericUiIterator.hpp"

#endif

