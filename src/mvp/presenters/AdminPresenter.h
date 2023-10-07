#ifndef _ADMINPRESENTER_H_
#define _ADMINPRESENTER_H_

#include <memory>

#include "IAdminModel.h"

#include "model_exception.h"

class IAdminView;

class AdminPresenter
{
    public:
        AdminPresenter(std::shared_ptr<IAdminModel> model,
                       std::shared_ptr<IAdminView> view);
        ~AdminPresenter(void);
        IAdminModel::Map getEmptyMap(std::string name);

    public: // signals
        void isAdmin(std::string hash);
        void getRequests(std::string hash);
        void setRequest(std::string hash, IAdminModel::Map map);

        void create(std::string hash, std::string name, IAdminModel::Map map);
        void update(std::string hash, std::string name, IAdminModel::Map map);
        void remove(std::string hash, std::string name, IAdminModel::Map map);
        void remove(std::string hash, std::string name, std::list<IAdminModel::CriteriaMap> criterias=std::list<IAdminModel::CriteriaMap>());
        void get(std::string hash, std::string name, std::list<IAdminModel::CriteriaMap> criterias=std::list<IAdminModel::CriteriaMap>());

    private:
        std::shared_ptr<IAdminView> view;
        std::shared_ptr<IAdminModel> model;
};

DEF_EX(CommonAdminPresenterException, ModelException,
       "Common AdminPresenter exception");
DEF_EX(NullptrAdminPresenterException, CommonAdminPresenterException,
       "Nullptr occured");

#endif

