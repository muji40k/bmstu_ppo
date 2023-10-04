#ifndef _UIHUMANADDRESSMAPPER_H_
#define _UIHUMANADDRESSMAPPER_H_

#include "facade.h"
#include "IAdminModel.h"

class UiHumanAddressMapper : public IAdminModel::Mapper
{
    public:
        UiHumanAddressMapper(std::shared_ptr<Facade> facade);
        virtual ~UiHumanAddressMapper(void) = default;
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

