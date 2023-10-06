#ifndef _LOGADMINREQUESTMANAGER_H_
#define _LOGADMINREQUESTMANAGER_H_

#include <memory>

#include "ILogger.h"
#include "AdminRequestManager.h"

class LogAdminRequestManager : public AdminRequestManager
{
    public:
        LogAdminRequestManager(std::shared_ptr<ILogger> logger,
                        std::shared_ptr<AdminRequestManager> manager);
        virtual ~LogAdminRequestManager(void) override = default;

        virtual RequestSet getRequests(std::string hash) override;
        virtual void updateRequest(std::string hash, const MergeRequest &request) override;

    private:
        std::shared_ptr<ILogger> logger;
        std::shared_ptr<AdminRequestManager> manager;
};

DEF_EX(CommonLogAdminRequestManagerException, CommonAdminRequestManagerException,
       "Common LogAdminRequestManager exception");
DEF_EX(NullptrLogAdminRequestManagerException, CommonLogAdminRequestManagerException,
       "Nullptr occured");

#endif

