#ifndef _USERINFOMANAGER_H_
#define _USERINFOMANAGER_H_

#include <unordered_map>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "UserMapper.h"

class UserMapper;

class UserInfoManager
{
    public:
        UserInfoManager(AppContext &context, UserMapper &mapper);
        virtual ~UserInfoManager(void) = default;

        virtual UserMapper::Map getInfo(std::string hash) const;
        virtual void updateInfo(std::string hash, const UserMapper::Map &map);
        virtual bool isHuman(std::string hash) const;
        virtual UserMapper::Map getHuman(std::string hash) const;

    private:
        UserHuman getUserHuman(std::string hash) const;

        AppContext &context;
        UserMapper &mapper;
};

DEF_EX(CommonUserInfoManagerException, ManagerException,
       "Common UserInfoManager exception");
DEF_EX(NotAuthenticatedUserInfoManagerException, CommonUserInfoManagerException,
       "User not authenticated");
DEF_EX(UnexpectedKeyUserInfoManagerException, CommonUserInfoManagerException,
       "Unexpected key occured");
DEF_EX(NotHumanUserInfoManagerException, CommonUserInfoManagerException,
       "Human isn't set for specified user");

#endif

