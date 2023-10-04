#include "AdminPresenter.h"

#include "IAdminView.h"

AdminPresenter::AdminPresenter(std::shared_ptr<IAdminModel> model,
                               std::shared_ptr<IAdminView> view)
    : view(view), model(model)
{
    if (nullptr == model || nullptr == view)
        throw CALL_EX(NullptrAdminPresenterException);

    this->view->setPresenter(this);
}

AdminPresenter::~AdminPresenter(void)
{
    this->view->onPresenterDestroied();
}

void AdminPresenter::isAdmin(std::string hash)
try
{
    bool res = this->model->isAdmin(hash);
    this->view->onIsAdmin(res);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::getRequests(std::string hash)
try
{
    IAdminModel::Set set = this->model->getRequests(hash);
    this->view->onGetRequests(set);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::setRequest(std::string hash, IAdminModel::Map map)
try
{
    this->model->setRequest(hash, map);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::create(std::string hash, std::string name, IAdminModel::Map map)
try
{
    this->model->create(hash, name, map);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::update(std::string hash, std::string name, IAdminModel::Map map)
try
{
    this->model->update(hash, name, map);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::remove(std::string hash, std::string name, IAdminModel::Map map)
try
{
    this->model->remove(hash, name, map);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::remove(std::string hash, std::string name, std::list<IAdminModel::CriteriaMap> criterias)
try
{
    this->model->remove(hash, name, criterias);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

void AdminPresenter::get(std::string hash, std::string name, std::list<IAdminModel::CriteriaMap> criterias)
try
{
    IAdminModel::Set set = this->model->get(hash, name, criterias);
    this->view->onGet(name, set);
}
catch (NotAuthenticatedAdminModelException &)
{
    this->view->onNotAuthenticated();
}
catch (NotAuthorizedAdminModelException &)
{
    this->view->onNotAuthorized();
}
catch (RedirectAdminModelException &er)
{
    this->view->onError(er.what());
}

IAdminModel::Map AdminPresenter::getEmptyMap(std::string name)
{
    return this->model->getEmptyMap(name);
}

