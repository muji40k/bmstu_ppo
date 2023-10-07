#ifndef _MD5LOGINMANAGER_H_
#define _MD5LOGINMANAGER_H_

#include <openssl/evp.h>
#include <string>
#include <sstream>
#include <iomanip>

#include "manager_exceptions.h"

#include "User.h"

namespace MD5LoginManager
{
    std::string hash(const User &user);
}

DEF_EX(MD5LoginManagerCommonException, ManagerException,
       "Common MD5LoginManager exception");
DEF_EX(MD5AllocationException, ManagerException,
       "Unable to allocate during hash process");
DEF_EX(MD5HashInnerException, ManagerException,
       "Unable to create hash");

#endif

