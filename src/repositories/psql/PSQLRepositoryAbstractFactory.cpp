#include "PSQLRepositoryAbstractFactory.h"

#include "PSQLCountryRepository.h"
#include "PSQLHumanAddressRepository.h"
#include "PSQLHumanGeneralRepository.h"
#include "PSQLHumanLanguageRepository.h"
#include "PSQLHumanLivingDatesRepository.h"
#include "PSQLHumanRepository.h"
#include "PSQLHumanSocialRepository.h"
#include "PSQLLanguageRepository.h"
#include "PSQLMergeRequestRepository.h"
#include "PSQLPlaceCountryRepository.h"
#include "PSQLPlaceRepository.h"
#include "PSQLPlaceResourceRepository.h"
#include "PSQLResourceRepository.h"
#include "PSQLUserHumanRepository.h"
#include "PSQLUserRepository.h"
#include "PSQLUserRoleRepository.h"

PSQLRepositoryAbstractFactory::PSQLRepositoryAbstractFactory(std::shared_ptr<pqxx::connection> connection,
                                                             std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder)
    : connection(connection), builder(builder)
{
    if (nullptr == connection || nullptr == builder)
        throw CALL_EX(InitializtionRepositoryAbstractFactoryException);
}

#define ADD_REPO_HEADER(type) \
std::shared_ptr<I##type##Repository> PSQLRepositoryAbstractFactory::make##type##Repository(void)

#define ADD_REPO(type)                                                                \
ADD_REPO_HEADER(type)                                                                 \
try                                                                                   \
{                                                                                     \
    return std::make_shared<PSQL##type##Repository>(this->connection, this->builder); \
}                                                                                     \
catch (std::bad_alloc &)                                                              \
{                                                                                     \
    throw CALL_EX(AllocationRepositoryAbstractFactoryException);                      \
}

#define ADD_REPO_WRAP(type, body)                                \
ADD_REPO_HEADER(type)                                            \
try                                                              \
{                                                                \
    body                                                         \
}                                                                \
catch (std::bad_alloc &)                                         \
{                                                                \
    throw CALL_EX(AllocationRepositoryAbstractFactoryException); \
}

ADD_REPO(Country)
ADD_REPO(HumanAddress)
ADD_REPO(HumanGeneral)
ADD_REPO(HumanLivingDates)
ADD_REPO(Human)
ADD_REPO(HumanSocial)
ADD_REPO(Language)
ADD_REPO(PlaceCountry)
ADD_REPO(Place)
ADD_REPO(Resource)
ADD_REPO(User)
ADD_REPO(UserRole)

ADD_REPO_WRAP(HumanLanguage,
    return std::make_shared<PSQLHumanLanguageRepository>(this->connection, this->builder, this->makeLanguageRepository());
)

ADD_REPO_WRAP(PlaceResource,
    return std::make_shared<PSQLPlaceResourceRepository>(this->connection, this->builder, this->makeResourceRepository());
)

ADD_REPO_WRAP(MergeRequest,
    return std::make_shared<PSQLMergeRequestRepository>(this->connection, this->builder,
                                                        this->makeUserRepository(),
                                                        this->makeHumanRepository());
)

ADD_REPO_WRAP(UserHuman,
    return std::make_shared<PSQLUserHumanRepository>(this->connection, this->builder,
                                                     this->makeHumanRepository());
)

