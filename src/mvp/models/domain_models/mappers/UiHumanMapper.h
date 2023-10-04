#ifndef _UIHUMANMAPPER_H_
#define _UIHUMANMAPPER_H_

#include "facade.h"
#include "IAdminModel.h"

class UiHumanMapper : public IAdminModel::Mapper
{
    public:
        UiHumanMapper(std::shared_ptr<Facade> facade);
        virtual ~UiHumanMapper(void) = default;
        virtual void create(std::string hash, IAdminModel::Map map) override;
        virtual void update(std::string hash, IAdminModel::Map map) override;
        virtual void remove(std::string hash, IAdminModel::Map map) override;
        virtual void remove(std::string hash, std::list<IAdminModel::CriteriaMap> criterias) override;
        virtual IAdminModel::Set get(std::string hash, std::list<IAdminModel::CriteriaMap> criterias) override;
        virtual IAdminModel::Map getEmptyMap(void) override;

    private:
        std::shared_ptr<Facade> facade;
};

#endif

