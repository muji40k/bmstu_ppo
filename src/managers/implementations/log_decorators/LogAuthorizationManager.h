#ifndef _LOGAUTHORIZATIONMANAGER_H_
#define _LOGAUTHORIZATIONMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "AuthorizationManager.h"

class LogAuthorizationManager : public AuthorizationManager
{
    public:
        LogAuthorizationManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<AuthorizationManager> manager);
        virtual ~LogAuthorizationManager(void) override = default;

        virtual bool authorize(const std::string &hash,
                               std::initializer_list<std::string> roles) override;
        virtual bool authorize(const std::string &hash,
                               std::list<std::string> roles) override;

    private:
        template <typename Container>
        bool innerAuthorize(const std::string &hash,
                            const Container &container);

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<AuthorizationManager> manager;
};

DEF_EX(CommonLogAuthorizationManagerException, CommonAuthorizationManagerException,
       "Common LogAuthorizationManager exception");
DEF_EX(NullptrLogAuthorizationManagerException, CommonLogAuthorizationManagerException,
       "Nullptr occured");

#endif

