#ifndef _USERREQUESTMANAGER_H_
#define _USERREQUESTMANAGER_H_

#include <list>
#include <unordered_map>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"
#include "UserMapper.h"

class UserRequestManager
{
    public:
        UserRequestManager(AppContext &context, UserMapper &mapper);
        virtual ~UserRequestManager(void) = default;

        virtual std::list<UserMapper::Map> findHuman(std::string hash, const UserMapper::Map &data) const;
        virtual void setHuman(std::string hash, const UserMapper::Map &data) const;

    private:
        AppContext &context;
        UserMapper &mapper;
};

DEF_EX(CommonUserRequestManagerException, ManagerException,
       "Common UserRequestManager exception");
DEF_EX(NotAuthenticatedUserRequestManagerException, CommonUserRequestManagerException,
       "User not authenticated");
DEF_EX(EmptyDataUserRequestManagerException, CommonUserRequestManagerException,
       "Data specifier can't be empty");
DEF_EX(UnspecifiedDataUserRequestManagerException, CommonUserRequestManagerException,
       "Data specifier can't be empty");
DEF_EX(UnsuitableDataUserRequestManagerException, CommonUserRequestManagerException,
       "Data specifier can't be empty");
DEF_EX(NotFoundUserRequestManagerException, CommonUserRequestManagerException,
       "Data specifier can't be empty");

#endif

