#ifndef _IUSERVIEW_H_
#define _IUSERVIEW_H_

#include <memory>
#include "IUserModel.h"

class UserPresenter;

class IUserView
{
    public:
        virtual ~IUserView(void) = default;

        void setPresenter(UserPresenter *presenter);

    public: // slots
        virtual void onGetInfo(IUserModel::Data data) = 0;
        virtual void onIsHuman(bool mark) = 0;
        virtual void onGetHuman(IUserModel::Data data) = 0;
        virtual void onFindHuman(std::list<IUserModel::Data> result) = 0;
        virtual void onPresenterDestroied(void);

        virtual void onNotAuthenticated(void) = 0;
        virtual void onNotAuthorized(void) = 0;
        virtual void onError(std::string message) = 0;

    protected:
        UserPresenter *presenter;
};

#endif

