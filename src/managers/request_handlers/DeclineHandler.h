#ifndef _DECLINEHANDLER_H_
#define _DECLINEHANDLER_H_

#include "RequestHandlerSet.h"

class DeclineHandler : public RequestHandlerSet::Handler
{
    public:
        virtual ~DeclineHandler(void) override = default;
        virtual const std::string &state(void) override;
        virtual void handle(AppContext &context, const MergeRequest &request) override;
};

#endif

