#include "MockValueCriteriaMakers.hpp"

#include "User.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<User>>> MockValueCriteriaCreatorSet<User>::items =
{
    {TypeName::getAttribute<User>("id"),
     std::make_shared<MockClassFieldCreator<User, unsigned long long, &User::getId>>()},
    {TypeName::getAttribute<User>("name"),
     std::make_shared<MockClassFieldCreator<User, std::string, &User::getName>>()},
    {TypeName::getAttribute<User>("password"),
     std::make_shared<MockClassFieldCreator<User, std::string, &User::getPassword>>()},
    {TypeName::getAttribute<User>("email"),
     std::make_shared<MockClassFieldCreator<User, std::string, &User::getEmail>>()}
};

