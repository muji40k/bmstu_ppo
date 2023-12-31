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
        virtual ~UserInfoManager(void) = default;

        virtual UserMapper::Map getInfo(std::string hash) const = 0;
        virtual void updateInfo(std::string hash, const UserMapper::Map &map) = 0;
        virtual bool isHuman(std::string hash) const = 0;
        virtual UserMapper::Map getHuman(std::string hash) const = 0;
};

DEF_EX(CommonUserInfoManagerException, ManagerException,
       "Common UserInfoManager exception");
DEF_EX(NotAuthenticatedUserInfoManagerException, CommonUserInfoManagerException,
       "User not authenticated");
DEF_EX(NotAuthorizedUserInfoManagerException, CommonUserInfoManagerException,
       "User not authorized");
DEF_EX(UnexpectedKeyUserInfoManagerException, CommonUserInfoManagerException,
       "Unexpected key occured");
DEF_EX(NotHumanUserInfoManagerException, CommonUserInfoManagerException,
       "Human isn't set for specified user");

#endif

