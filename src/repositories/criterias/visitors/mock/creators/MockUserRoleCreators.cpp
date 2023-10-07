#include "MockValueCriteriaMakers.hpp"

#include "UserRole.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<UserRole>>> MockValueCriteriaCreatorSet<UserRole>::items =
{
    {TypeName::getAttribute<UserRole>("id"),
     std::make_shared<MockClassFieldCreator<UserRole, unsigned long long, &UserRole::getId>>()},
    {TypeName::getAttribute<UserRole>("userId"),
     std::make_shared<MockClassFieldCreator<UserRole, unsigned long long, &UserRole::getUserId>>()},
    {TypeName::getAttribute<UserRole>("role"),
     std::make_shared<MockClassFieldCreator<UserRole, std::string, &UserRole::getRole>>()}
};

