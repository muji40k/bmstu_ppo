#ifndef _APPROVEHANDLER_H_
#define _APPROVEHANDLER_H_

#include "RequestHandlerSet.h"

class ApproveHandler : public RequestHandlerSet::Handler
{
    public:
        virtual ~ApproveHandler(void) override = default;
        virtual const std::string &state(void) override;
        virtual void handle(AppContext &context, const MergeRequest &request) override;
};

#endif

