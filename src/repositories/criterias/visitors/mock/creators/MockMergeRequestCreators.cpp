#include "MockValueCriteriaMakers.hpp"

#include "MergeRequest.h"

template <>
const std::unordered_map<std::string, std::shared_ptr<MockValueCriteriaMakersCreator<MergeRequest>>> MockValueCriteriaCreatorSet<MergeRequest>::items =
{
    {TypeName::getAttribute<MergeRequest>("id"),
     std::make_shared<MockClassFieldCreator<MergeRequest, unsigned long long, &MergeRequest::getId>>()},
    {TypeName::getAttribute<MergeRequest>("state"),
     std::make_shared<MockClassFieldCreator<MergeRequest, std::string, &MergeRequest::getState>>()},
    {TypeName::getAttribute<MergeRequest>("user.id"),
     std::make_shared<MockClassFieldTransitiveCreator<MergeRequest, User, unsigned long long, &MergeRequest::getUser, &User::getId>>()},
    {TypeName::getAttribute<MergeRequest>("human.id"),
     std::make_shared<MockClassFieldTransitiveCreator<MergeRequest, Human, unsigned long long, &MergeRequest::getHuman, &Human::getId>>()}
};

