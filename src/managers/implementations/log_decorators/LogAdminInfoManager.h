#ifndef _LOGADMININFOMANAGER_H_
#define _LOGADMININFOMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "AdminInfoManager.h"

class LogAdminInfoManager : public AdminInfoManager
{
    public:
        LogAdminInfoManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<AdminInfoManager> manager);
        virtual ~LogAdminInfoManager(void) override = default;

        virtual void process(std::string hash, AdminInfoStrategy &strategy) override;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<AdminInfoManager> manager;
};

DEF_EX(CommonLogAdminInfoManagerException, CommonAdminInfoManagerException,
       "Common LogAdminInfoManager exception");
DEF_EX(NullptrLogAdminInfoManagerException, CommonLogAdminInfoManagerException,
       "Nullptr occured");

#endif

