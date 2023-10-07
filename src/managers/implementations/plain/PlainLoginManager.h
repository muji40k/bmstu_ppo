#ifndef _PLAINLOGINMANAGER_H_
#define _PLAINLOGINMANAGER_H_

#include "LoginManager.h"

class PlainLoginManager : public LoginManager
{
    public:
        PlainLoginManager(RepositoryContext &context, HashFunc func,
                            std::shared_ptr<RegistrationHook> hook = nullptr);
        virtual ~PlainLoginManager(void) override = default;

        virtual std::string login(std::string email, std::string password) override;
        virtual void registerUser(User user) override;
        virtual std::string update(std::string hash) override;
        virtual void exit(std::string hash) override;
        virtual bool isAuthenticated(std::string hash) const override;
        virtual const User &getAuthenticated(std::string hash) const override;

    private:
        RepositoryContext &context;
        HashFunc hash;
        std::shared_ptr<RegistrationHook> hook = nullptr;
        std::unordered_map<std::string, User> authenticated;
};

#endif

