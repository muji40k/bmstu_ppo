#ifndef _DOMAINLOGINMODEL_H_
#define _DOMAINLOGINMODEL_H_

#include <memory>

#include "facade.h"
#include "ILoginModel.h"

class DomainLoginModel : public ILoginModel
{
    public:
        DomainLoginModel(std::shared_ptr<Facade> facade);
        virtual ~DomainLoginModel(void) = default;
        virtual std::string login(std::string email, std::string password) override;
        virtual std::string update(std::string hash) override;
        virtual void registerUser(std::string email, std::string password, std::string name) override;
        virtual void exit(std::string hash) override;

    private:
        std::shared_ptr<Facade> facade;
};

#endif

