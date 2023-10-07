#ifndef _DOMAINADMINMODEL_H_
#define _DOMAINADMINMODEL_H_

#include <memory>

#include "facade.h"
#include "IAdminModel.h"

class DomainAdminModel : public IAdminModel
{
    public:
        DomainAdminModel(std::shared_ptr<Facade> facade);
        virtual ~DomainAdminModel(void) override = default;
        virtual bool isAdmin(std::string hash) const override;
        virtual Set getRequests(std::string hash) override;
        virtual void setRequest(std::string hash, Map map) override;

    private:
        std::shared_ptr<Facade> facade;
};

#endif

