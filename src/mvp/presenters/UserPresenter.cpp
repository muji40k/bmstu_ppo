#include "UserPresenter.h"

#include "IUserView.h"

UserPresenter::UserPresenter(std::shared_ptr<IUserModel> model,
                               std::shared_ptr<IUserView> view)
    : view(view), model(model)
{
    if (nullptr == model || nullptr == view)
        throw CALL_EX(NullptrUserPresenterException);

    this->view->setPresenter(this);
}

UserPresenter::~UserPresenter(void)
{
    this->view->onPresenterDestroied();
}

void UserPresenter::getInfo(std::string hash)
try
{
    auto res = this->model->getInfo(hash);
    this->view->onGetInfo(res);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

void UserPresenter::setInfo(std::string hash, const IUserModel::Data data)
try
{
    this->model->setInfo(hash, data);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

void UserPresenter::isHuman(std::string hash)
try
{
    bool mark = this->model->isHuman(hash);
    this->view->onIsHuman(mark);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

void UserPresenter::getHuman(std::string hash)
try
{
    auto res = this->model->getHuman(hash);
    this->view->onGetHuman(res);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

void UserPresenter::findHuman(std::string hash, const IUserModel::Data data)
try
{
    auto res = this->model->findHuman(hash, data);
    this->view->onFindHuman(res);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

void UserPresenter::setHuman(std::string hash, IUserModel::Data data)
try
{
    this->model->setHuman(hash, data);
}
catch (NotAuthenticatedUserModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedUserModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectUserModelException &er)
{
    this->view->onError(er.what());
}

