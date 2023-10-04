#ifndef _ILOGINVIEW_H_
#define _ILOGINVIEW_H_

#include <memory>
#include "ILoginModel.h"

class LoginPresenter;

class ILoginView
{
    public:
        virtual ~ILoginView(void) = default;

        void setPresenter(LoginPresenter *presenter);

    public: // slots
        virtual void onLoginSuccess(std::string hash) = 0;
        virtual void onLoginFailure(std::string message) = 0;
        virtual void onUpdateSuccess(std::string hash) = 0;
        virtual void onUpdateFailure(std::string message) = 0;
        virtual void onRegisterSuccess(void) = 0;
        virtual void onRegisterFailure(std::string message) = 0;
        virtual void onExit(void) = 0;
        virtual void onPresenterDestroied(void);

        virtual void onError(std::string message) = 0;

    protected:
        LoginPresenter *presenter;
};

#endif

