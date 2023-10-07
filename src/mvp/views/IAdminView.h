#ifndef _IADMINVIEW_H_
#define _IADMINVIEW_H_

#include <memory>
#include "IAdminModel.h"

class AdminPresenter;

class IAdminView
{
    public:
        virtual ~IAdminView(void) = default;

        void setPresenter(AdminPresenter *presenter);

    public: // slots
        virtual void onIsAdmin(bool result) = 0;
        virtual void onGetRequests(IAdminModel::Set result) = 0;
        virtual void onGet(std::string name, IAdminModel::Set result) = 0;
        virtual void onPresenterDestroied(void);

        virtual void onNotAuthenticated(void) = 0;
        virtual void onNotAuthorized(void) = 0;
        virtual void onError(std::string message) = 0;

    protected:
        AdminPresenter *presenter;
};

#endif

