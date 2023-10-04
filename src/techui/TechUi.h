#ifndef _TECHUI_H_
#define _TECHUI_H_

#include <memory>

#include "App.h"

#include "AdminPresenter.h"
#include "UserPresenter.h"
#include "LoginPresenter.h"

class TechUi : public App
{
    public:
        class Item
        {
            public:
                virtual ~Item(void) = default;
                virtual bool check(std::string command) = 0;
                virtual int perform(std::string command, std::string &hash) = 0;
        };

    public:
        TechUi(std::shared_ptr<IAdminModel> admin_model,
               std::shared_ptr<IUserModel> user_model,
               std::shared_ptr<ILoginModel> login_model);

        virtual ~TechUi(void) override = default;
        virtual int run(void) override;

    private:
        std::shared_ptr<AdminPresenter> admin_presenter;
        std::shared_ptr<UserPresenter> user_presenter;
        std::shared_ptr<LoginPresenter> login_presenter;
        std::list<std::shared_ptr<Item>> items;
        std::string hash;
};

#endif

