#ifndef _LOGINPRESENTER_H_
#define _LOGINPRESENTER_H_

#include <memory>

#include "model_exception.h"

#include "ILoginModel.h"

class ILoginView;

class LoginPresenter
{
    public:
        LoginPresenter(std::shared_ptr<ILoginModel> model,
                       std::shared_ptr<ILoginView> view);
        ~LoginPresenter(void);

    public: // signals
        void login(std::string email, std::string password);
        void update(std::string hash);
        void registerUser(std::string email, std::string password, std::string name);
        void exit(std::string hash);

    private:
        std::shared_ptr<ILoginView> view;
        std::shared_ptr<ILoginModel> model;
};

DEF_EX(CommonLoginPresenterException, ModelException,
       "Common LoginPresenter exception");
DEF_EX(NullptrLoginPresenterException, CommonLoginPresenterException,
       "Nullptr occured");

#endif

