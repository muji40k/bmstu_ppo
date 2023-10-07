#ifndef _IUSERMODEL_H_
#define _IUSERMODEL_H_

#include <string>
#include <unordered_map>
#include <list>

#include "model_exception.h"

class IUserModel
{
    public:
        using Data = std::unordered_map<std::string, std::string>;

    public:
        virtual ~IUserModel(void) = default;
        virtual Data getInfo(std::string hash) const = 0;
        virtual void setInfo(std::string hash, const Data data) = 0;
        virtual bool isHuman(std::string hash) const = 0;
        virtual Data getHuman(std::string hash) const = 0;
        virtual std::list<Data> findHuman(std::string hash, const Data data) = 0;
        virtual void setHuman(std::string hash, Data data) = 0;
};

DEF_EX(CommonUserModelException, ModelException, "Common UserModel exception");
DEF_EX(NullptrUserModelException, CommonUserModelException, "Nullptr occured");
DEF_EX(NotAuthenticatedUserModelException, CommonUserModelException, "User not authenticated");
DEF_EX(NotAuthorizedUserModelException, CommonUserModelException, "User not authorized");
DEF_EX(RedirectUserModelException, CommonUserModelException, "");

#endif

