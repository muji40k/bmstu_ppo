#ifndef _DOMAINUSERMODEL_H_
#define _DOMAINUSERMODEL_H_

#include <memory>

#include "facade.h"
#include "IUserModel.h"

class DomainUserModel : public IUserModel
{
    public:
        DomainUserModel(std::shared_ptr<Facade> facade);
        virtual ~DomainUserModel(void) override = default;
        virtual Data getInfo(std::string hash) const override;
        virtual void setInfo(std::string hash, const Data data) override;
        virtual bool isHuman(std::string hash) const override;
        virtual Data getHuman(std::string hash) const override;
        virtual std::list<Data> findHuman(std::string hash, const Data data) override;
        virtual void setHuman(std::string hash, Data data) override;

    private:
        std::shared_ptr<Facade> facade;
};

#endif

