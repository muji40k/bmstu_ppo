#ifndef _ILOGINMODEL_H_
#define _ILOGINMODEL_H_

#include <string>

#include "model_exception.h"

class ILoginModel
{
    public:
        virtual ~ILoginModel(void) = default;
        virtual std::string login(std::string email, std::string password) = 0;
        virtual std::string update(std::string hash) = 0;
        virtual void registerUser(std::string email, std::string password, std::string name) = 0;
        virtual void exit(std::string hash) = 0;
};

DEF_EX(CommonLoginModelException, ModelException, "Common LoginModel exception");
DEF_EX(NullptrLoginModelException, CommonLoginModelException, "Nullptr occured");
DEF_EX(NotAuthenticatedLoginModelException, CommonLoginModelException, "User not authenticated");
DEF_EX(RedirectLoginModelException, CommonLoginModelException, "");

#endif

