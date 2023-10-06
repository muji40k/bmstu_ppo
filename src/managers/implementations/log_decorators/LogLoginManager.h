#ifndef _LOGLOGINMANAGER_H_
#define _LOGLOGINMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "LoginManager.h"

class LogLoginManager : public LoginManager
{
    public:
        LogLoginManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<LoginManager> manager);
        virtual ~LogLoginManager(void) = default;

        virtual std::string login(std::string email, std::string password);
        virtual void registerUser(User user);
        virtual std::string update(std::string hash);
        virtual void exit(std::string hash);
        virtual bool isAuthenticated(std::string hash) const;
        virtual const User &getAuthenticated(std::string hash) const;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<LoginManager> manager;
};

DEF_EX(CommonLogLoginManagerException, CommonLoginManagerException,
       "Common LogLoginManager exception");
DEF_EX(NullptrLogLoginManagerException, CommonLogLoginManagerException,
       "Nullptr occured");

#endif

