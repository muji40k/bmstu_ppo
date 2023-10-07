#ifndef _PLAINUSERINFOMANAGER_H_
#define _PLAINUSERINFOMANAGER_H_

#include "UserInfoManager.h"

class PlainUserInfoManager : public UserInfoManager
{
    public:
        PlainUserInfoManager(AppContext &context, UserMapper &mapper);
        virtual ~PlainUserInfoManager(void) override = default;

        virtual UserMapper::Map getInfo(std::string hash) const override;
        virtual void updateInfo(std::string hash, const UserMapper::Map &map) override;
        virtual bool isHuman(std::string hash) const override;
        virtual UserMapper::Map getHuman(std::string hash) const override;

    private:
        UserHuman getUserHuman(std::string hash) const;

        AppContext &context;
        UserMapper &mapper;
};

#endif

