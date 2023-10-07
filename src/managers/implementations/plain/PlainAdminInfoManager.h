#ifndef _PLAINADMININFOMANAGER_H_
#define _PLAINADMININFOMANAGER_H_

#include "AdminInfoManager.h"

class PlainAdminInfoManager : public AdminInfoManager
{
    public:
        PlainAdminInfoManager(AppContext &context);
        virtual ~PlainAdminInfoManager(void) override = default;

        virtual void process(std::string hash, AdminInfoStrategy &strategy) override;

    private:
        AppContext &context;
};

#endif

