#ifndef _UIMERGEREQUESTSET_H_
#define _UIMERGEREQUESTSET_H_

#include "IAdminModel.h"
#include "AdminRequestManager.h"

namespace UiMergeRequestMapper
{
    IAdminModel::Map mapRequest(const MergeRequest &mr);
    MergeRequest unmapRequest(IAdminModel::Map map);
}

class UiMergeRequestIterator : public IAdminModel::InnerIter
{
    public:
        UiMergeRequestIterator(RequestSetIterator iter);
        virtual ~UiMergeRequestIterator(void) override = default;
        virtual void next(void) override;
        virtual IAdminModel::Map get(void) const override;
        virtual bool notEqual(std::shared_ptr<const InnerIter> iter) const override;

    private:
        RequestSetIterator iter;
};

class UiMergeRequestSet : public IAdminModel::InnerSet
{
    public:
        UiMergeRequestSet(RequestSet set);
        virtual ~UiMergeRequestSet(void) override = default;
        virtual std::shared_ptr<IAdminModel::InnerIter> begin(void) override;
        virtual std::shared_ptr<IAdminModel::InnerIter> end(void) override;

    private:
        RequestSet set;
};

#endif

