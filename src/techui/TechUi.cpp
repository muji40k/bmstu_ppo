#include "TechUi.h"

#include <iostream>

#include "IAdminModel.h"
#include "IUserModel.h"
#include "ILoginModel.h"

#include "TechUiAdminItem.h"
#include "TechUiUserItem.h"
#include "TechUiLoginItem.h"

TechUi::TechUi(std::shared_ptr<IAdminModel> admin_model,
               std::shared_ptr<IUserModel> user_model,
               std::shared_ptr<ILoginModel> login_model)
{
    auto aitem = std::make_shared<TechUiAdminItem>();
    auto uitem = std::make_shared<TechUiUserItem>();
    auto litem = std::make_shared<TechUiLoginItem>(this->hash);
    this->admin_presenter = std::make_shared<AdminPresenter>(admin_model, aitem);
    this->user_presenter = std::make_shared<UserPresenter>(user_model, uitem);
    this->login_presenter = std::make_shared<LoginPresenter>(login_model, litem);
    this->items.push_back(aitem);
    this->items.push_back(uitem);
    this->items.push_back(litem);
}

int TechUi::run(void)
{
    std::string input;

    for (bool run = true; run;)
    {
        std::cout << "$ ";
        std::cin >> input;
        std::cin.ignore();

        if ("quit" == input)
            run = false;
        else
            for (auto item : this->items)
                if (item->check(input))
                    item->perform(input, this->hash);
    }

    return 0;
}

