#include "PSQLRepositoryContextBuilder.h"

#include "typestring.h"

#include "PSQLRepositoryAbstractFactory.h"

#include "CriteriaFieldMapper.h"
#include "PSQLTimeConverter.h"
#include "PSQLCriteriaValueStringConverter.h"
#include "PSQLCriteriaVisitorBuilder.h"

#include "UserHumanRegistrationHook.h"
#include "UserRoleRegistrationHook.h"

#include "PSQLAuthorizationHook.h"

void PSQLRepositoryContextBuilder::build(void)
try
{
    std::shared_ptr<CriteriaValueStringConverter> converter = std::make_shared<PSQLCriteriaValueStringConverter>(this->converters);
    std::shared_ptr<CriteriaFieldMapper> mapper = std::make_shared<CriteriaFieldMapper>(this->map);
    std::shared_ptr<PSQLCriteriaVisitorBuilder> builder = std::make_shared<PSQLCriteriaVisitorBuilder>();
    builder->setFieldMapper(mapper);
    builder->setValueConverter(converter);

    std::shared_ptr<pqxx::connection> connection = this->getConnection();
    std::shared_ptr<RepositoryAbstractFactory> rfactory = std::make_shared<PSQLRepositoryAbstractFactory>(connection, builder);

    std::list<std::shared_ptr<RegistrationHook::Item>> registration_hooks =
    {
        std::make_shared<UserHumanRegistrationHook>(),
        std::make_shared<UserRoleRegistrationHook>()
    };

    std::list<std::shared_ptr<AuthorizationHook::Item>> authorization_hooks =
    {
        std::make_shared<PSQLAuthorizationHook>(connection)
    };

    this->context_result = std::make_shared<RepositoryContext>(rfactory);
    this->registration_hooks = registration_hooks;
    this->authorization_hooks = authorization_hooks;
    this->ready = true;
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationRepositoryContextException);
}

std::shared_ptr<RepositoryContext> PSQLRepositoryContextBuilder::result(void)
{
    if (!this->ready)
        throw CALL_EX(NotReadyRepositoryContextBuilderException);

    return this->context_result;
}

const std::list<std::shared_ptr<RegistrationHook::Item>> &PSQLRepositoryContextBuilder::registrationHooks(void)
{
    if (!this->ready)
        throw CALL_EX(NotReadyRepositoryContextBuilderException);

    return this->registration_hooks;
}

const std::list<std::shared_ptr<AuthorizationHook::Item>> &PSQLRepositoryContextBuilder::authorizationHooks(void)
{
    if (!this->ready)
        throw CALL_EX(NotReadyRepositoryContextBuilderException);

    return this->authorization_hooks;
}

void PSQLRepositoryContextBuilder::setConnectionString(std::string conn)
{
    this->connection_string = conn;
}

void PSQLRepositoryContextBuilder::setTimeZone(std::string tz)
{
    this->timezone = tz;
}

std::shared_ptr<pqxx::connection> PSQLRepositoryContextBuilder::getConnection(void) const
{
    if ("" == this->connection_string)
        throw CALL_EX(WrongDataRepositoryContextBuilderException);

    std::shared_ptr<pqxx::connection> out = std::make_shared<pqxx::connection>(this->connection_string);

    pqxx::nontransaction nt (*out);

    if ("" != this->timezone)
        nt.exec("set timezone='" + this->timezone + '\'');

    nt.exec("set role guest");
    nt.commit();

    return out;
}

const std::list<std::shared_ptr<CriteriaValueStringConverter::Item>> PSQLRepositoryContextBuilder::converters =
{
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<Country>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<Human>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<HumanAddress>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<HumanGeneral>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<HumanLanguage>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<HumanLivingDates>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<HumanSocial>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<Language>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<Place>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<PlaceCountry>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<PlaceResource>("validFrom")),
    std::make_shared<PSQLTimeConverter>(TypeName::getAttribute<Resource>("validFrom"))
};

const std::unordered_map<std::string, std::string> PSQLRepositoryContextBuilder::map =
{
    {TypeName::getAttribute<Country>("id"), "country.general.country_id"},
    {TypeName::getAttribute<Country>("type"), "country.general.type"},
    {TypeName::getAttribute<Country>("name"), "country.general.name"},
    {TypeName::getAttribute<Country>("gdp"), "country.general.gdp"},
    {TypeName::getAttribute<Country>("validFrom"), "country.general.valid_from"},
    {TypeName::getAttribute<HumanAddress>("id"), "human.address.human_id"},
    {TypeName::getAttribute<HumanAddress>("currentPlace.id"), "human.address.place_id"},
    {TypeName::getAttribute<HumanAddress>("validFrom"), "human.address.valid_from"},
    {TypeName::getAttribute<Human>("id"), "human.names.human_id"},
    {TypeName::getAttribute<Human>("firstName"), "human.names.first_name"},
    {TypeName::getAttribute<Human>("lastName"), "human.names.last_name"},
    {TypeName::getAttribute<Human>("patronymic"), "human.names.patronymic"},
    {TypeName::getAttribute<Human>("birthPlace.id"), "human.birth_place.place_id"},
    {TypeName::getAttribute<HumanGeneral>("id"), "human.general.human_id"},
    {TypeName::getAttribute<HumanGeneral>("bloodType"), "human.general.blood_type"},
    {TypeName::getAttribute<HumanGeneral>("gender"), "human.general.gender"},
    {TypeName::getAttribute<HumanGeneral>("race"), "human.general.race"},
    {TypeName::getAttribute<HumanGeneral>("validFrom"), "human.general.valid_from"},
    {TypeName::getAttribute<HumanLanguage>("id"), "human.language.human_id"},
    {TypeName::getAttribute<HumanLanguage>("validFrom"), "human.language.valid_from"},
    {TypeName::getAttribute<HumanLivingDates>("id"), "human.dates.human_id"},
    {TypeName::getAttribute<HumanLivingDates>("birthDate"), "human.dates.birth"},
    {TypeName::getAttribute<HumanLivingDates>("deathDate"), "human.dates.death"},
    {TypeName::getAttribute<HumanLivingDates>("validFrom"), "human.dates.valid_from"},
    {TypeName::getAttribute<HumanSocial>("id"), "human.social.human_id"},
    {TypeName::getAttribute<HumanSocial>("religion"), "human.social.religion"},
    {TypeName::getAttribute<HumanSocial>("wealth"), "human.social.wealth"},
    {TypeName::getAttribute<HumanSocial>("literacy"), "human.social.literacy"},
    {TypeName::getAttribute<HumanSocial>("busyness"), "human.social.busyness"},
    {TypeName::getAttribute<HumanSocial>("validFrom"), "human.social.valid_from"},
    {TypeName::getAttribute<Language>("id"), "language.general.language_id"},
    {TypeName::getAttribute<Language>("name"), "language.general.name"},
    {TypeName::getAttribute<Language>("family"), "language.general.family"},
    {TypeName::getAttribute<Language>("validFrom"), "language.general.valid_from"},
    {TypeName::getAttribute<MergeRequest>("id"), "authentication.merge_requests.id"},
    {TypeName::getAttribute<MergeRequest>("state"), "authentication.merge_requests.state"},
    {TypeName::getAttribute<MergeRequest>("user.id"), "authentication.merge_requests.user_id"},
    {TypeName::getAttribute<MergeRequest>("human.id"), "authentication.merge_requests.human_id"},
    {TypeName::getAttribute<PlaceCountry>("id"), "place.country.place_id"},
    {TypeName::getAttribute<PlaceCountry>("country.id"), "place.country.country_id"},
    {TypeName::getAttribute<PlaceCountry>("validFrom"), "place.country.valid_from"},
    {TypeName::getAttribute<Place>("id"), "place.general.place_id"},
    {TypeName::getAttribute<Place>("type"), "place.general.type"},
    {TypeName::getAttribute<Place>("name"), "place.general.name"},
    {TypeName::getAttribute<Place>("area"), "place.general.area"},
    {TypeName::getAttribute<Place>("continent"), "place.general.continent"},
    {TypeName::getAttribute<Place>("validFrom"), "place.general.valid_from"},
    {TypeName::getAttribute<PlaceResource>("id"), "place.resource.place_id"},
    {TypeName::getAttribute<PlaceResource>("validFrom"), "place.resource.valid_from"},
    {TypeName::getAttribute<Resource>("id"), "resource.general.resource_id"},
    {TypeName::getAttribute<Resource>("type"), "resource.general.type"},
    {TypeName::getAttribute<Resource>("name"), "resource.general.name"},
    {TypeName::getAttribute<Resource>("value"), "resource.general.value"},
    {TypeName::getAttribute<Resource>("rarity"), "resource.general.rarity"},
    {TypeName::getAttribute<Resource>("validFrom"), "resource.general.valid_from"},
    {TypeName::getAttribute<User>("id"), "authentication.users.id"},
    {TypeName::getAttribute<User>("name"),"authentication.users.name"},
    {TypeName::getAttribute<User>("password"),"authentication.users.password"},
    {TypeName::getAttribute<User>("email"),"authentication.users.email"},
    {TypeName::getAttribute<UserHuman>("id"), "authentication.user_human.user_id"},
    {TypeName::getAttribute<UserHuman>("human.id"), "authentication.user_human.human_id"},
    {TypeName::getAttribute<UserRole>("id"), "authentication.user_roles.id"},
    {TypeName::getAttribute<UserRole>("userId"), "authentication.user_roles.user_id"},
    {TypeName::getAttribute<UserRole>("role"), "authentication.user_roles.role"}
};

