#ifndef _PLAINUSERREQUESTMANAGER_H_
#define _PLAINUSERREQUESTMANAGER_H_

#include "UserRequestManager.h"

class PlainUserRequestManager : public UserRequestManager
{
    public:
        PlainUserRequestManager(AppContext &context, UserMapper &mapper);
        virtual ~PlainUserRequestManager(void) override = default;

        virtual std::list<UserMapper::Map> findHuman(std::string hash, const UserMapper::Map &data) const override;
        virtual void setHuman(std::string hash, const UserMapper::Map &data) const override;

    private:
        AppContext &context;
        UserMapper &mapper;
};

#endif

