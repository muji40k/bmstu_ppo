#include "RepositoryContext.h"

RepositoryContext::RepositoryContext(std::shared_ptr<RepositoryAbstractFactory> factory)
    : factory(factory)
{
    if (nullptr == factory)
        throw CALL_EX(FactoryNullptrRepositoryContextException);
}

#define DEFINE_GET(type)                                                               \
std::shared_ptr<I##type##Repository> RepositoryContext::get##type##Repository(void)    \
{                                                                                      \
    if (nullptr == this->_##type)                                                      \
    {                                                                                  \
        try                                                                            \
        {                                                                              \
            this->_##type = this->factory->make##type##Repository();                   \
        }                                                                              \
        catch (AllocationRepositoryAbstractFactoryException &er)                       \
        {                                                                              \
            throw CALL_EX_MSG(AllocationRepositoryContextException,                    \
                              "Unable to allocate repository of type" #type);          \
        }                                                                              \
    }                                                                                  \
                                                                                       \
    return this->_##type;                                                              \
}

DEFINE_GET(Country)
DEFINE_GET(HumanAddress)
DEFINE_GET(HumanGeneral)
DEFINE_GET(HumanLanguage)
DEFINE_GET(HumanLivingDates)
DEFINE_GET(Human)
DEFINE_GET(HumanSocial)
DEFINE_GET(Language)
DEFINE_GET(MergeRequest)
DEFINE_GET(PlaceCountry)
DEFINE_GET(Place)
DEFINE_GET(PlaceResource)
DEFINE_GET(Resource)
DEFINE_GET(UserHuman)
DEFINE_GET(User)
DEFINE_GET(UserRole)

