#ifndef _USERPRESENTER_H_
#define _USERPRESENTER_H_

#include <memory>

#include "IUserModel.h"

#include "model_exception.h"

class IUserView;

class UserPresenter
{
    public:
        UserPresenter(std::shared_ptr<IUserModel> model,
                       std::shared_ptr<IUserView> view);
        ~UserPresenter(void);

    public: // signals
        void getInfo(std::string hash);
        void setInfo(std::string hash, const IUserModel::Data data);
        void isHuman(std::string hash);
        void getHuman(std::string hash);
        void findHuman(std::string hash, const IUserModel::Data data);
        void setHuman(std::string hash, IUserModel::Data data);

    private:
        std::shared_ptr<IUserView> view;
        std::shared_ptr<IUserModel> model;
};

DEF_EX(CommonUserPresenterException, ModelException,
       "Common UserPresenter exception");
DEF_EX(NullptrUserPresenterException, CommonUserPresenterException,
       "Nullptr occured");

#endif

