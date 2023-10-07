#include "LoginPresenter.h"

#include "ILoginView.h"

LoginPresenter::LoginPresenter(std::shared_ptr<ILoginModel> model,
                               std::shared_ptr<ILoginView> view)
    : view(view), model(model)
{
    if (nullptr == model || nullptr == view)
        throw CALL_EX(NullptrLoginPresenterException);

    this->view->setPresenter(this);
}

LoginPresenter::~LoginPresenter(void)
{
    this->view->onPresenterDestroied();
}

void LoginPresenter::login(std::string email, std::string password)
try
{
    std::string hash = this->model->login(email, password);
    this->view->onLoginSuccess(hash);
}
catch (CommonLoginModelException &er)
{
    this->view->onLoginFailure(er.what());
}

void LoginPresenter::update(std::string hash)
try
{
    std::string new_hash = this->model->update(hash);
    this->view->onUpdateSuccess(new_hash);
}
catch (CommonLoginModelException &er)
{
    this->view->onUpdateFailure(er.what());
}

void LoginPresenter::registerUser(std::string email, std::string password, std::string name)
try
{
    this->model->registerUser(email, password, name);
    this->view->onRegisterSuccess();
}
catch (CommonLoginModelException &er)
{
    this->view->onRegisterFailure(er.what());
}

void LoginPresenter::exit(std::string hash)
try
{
    this->model->exit(hash);
}
catch (CommonLoginModelException &er)
{
    this->view->onError(er.what());
}

