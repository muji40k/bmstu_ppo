#ifndef _PLAINADMINREQUESTMANAGER_H_
#define _PLAINADMINREQUESTMANAGER_H_

#include "AdminRequestManager.h"

class PlainAdminRequestManager : public AdminRequestManager
{
    public:
        PlainAdminRequestManager(AppContext &context, RequestHandlerSet &handler);
        virtual ~PlainAdminRequestManager(void) override = default;

        virtual RequestSet getRequests(std::string hash) override;
        virtual void updateRequest(std::string hash, const MergeRequest &request) override;

    private:
        AppContext &context;
        RequestHandlerSet &handler;
};

#endif

