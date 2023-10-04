#include "typestring.h"

#include "facade.h"

#include "AppContext.h"
#include "RepositoryContext.h"

#include "MD5LoginManager.h"

#include "AddressGetter.h"
#include "LanguageGetter.h"
#include "SocialGetter.h"
#include "GeneralGetter.h"
#include "LivingDatesGetter.h"

#include "ApproveHandler.h"
#include "DeclineHandler.h"

#include "UserHumanRegistrationHook.h"
#include "UserRoleRegistrationHook.h"

#include "PSQLAuthorizationHook.h"

#include "PlainManagerAbstractFactory.h"

#include "PSQLRepositoryAbstractFactory.h"
#include "PSQLCriteriaVisitorBuilder.h"
#include "PSQLCriteriaValueStringConverter.h"
#include "PSQLTimeConverter.h"

#include "TechUi.h"
#include "DomainAdminModel.h"
#include "DomainUserModel.h"
#include "DomainLoginModel.h"

#include "UiCountryMapper.h"
#include "UiHumanAddressMapper.h"
#include "UiHumanGeneralMapper.h"
#include "UiHumanLanguageMapper.h"
#include "UiHumanLivingDatesMapper.h"
#include "UiHumanMapper.h"
#include "UiHumanSocialMapper.h"
#include "UiMergeRequestSet.h"
#include "UiPlaceCountryMapper.h"
#include "UiPlaceMapper.h"
#include "UiPlaceResourceMapper.h"
#include "UiUserMapper.h"


std::shared_ptr<App> setupApp(void);
const std::unordered_map<std::string, std::string> &getMap(void);
std::shared_ptr<pqxx::connection> setupConnection(std::string conn);
std::shared_ptr<Facade> setupAppContext(void);

int main(int , char **)
{
    auto app = setupApp();

    return app->run();
}

std::shared_ptr<App> setupApp(void)
{
    auto facade = setupAppContext();
    auto amodel = std::make_shared<DomainAdminModel>(facade);
    auto umodel = std::make_shared<DomainUserModel>(facade);
    auto lmodel = std::make_shared<DomainLoginModel>(facade);
    amodel->add("Human", std::make_shared<UiHumanMapper>(facade));
    amodel->add("HumanAddress", std::make_shared<UiHumanAddressMapper>(facade));
    amodel->add("HumanLivingDates", std::make_shared<UiHumanLivingDatesMapper>(facade));
    amodel->add("HumanSocial", std::make_shared<UiHumanSocialMapper>(facade));
    amodel->add("HumanGeneral", std::make_shared<UiHumanGeneralMapper>(facade));
    amodel->add("HumanLanguage", std::make_shared<UiHumanLanguageMapper>(facade));
    amodel->add("Place", std::make_shared<UiPlaceMapper>(facade));
    amodel->add("PlaceResource", std::make_shared<UiPlaceResourceMapper>(facade));
    amodel->add("PlaceCountry", std::make_shared<UiPlaceCountryMapper>(facade));
    amodel->add("Country", std::make_shared<UiCountryMapper>(facade));
    amodel->add("User", std::make_shared<UiUserMapper>(facade));

    return std::make_shared<TechUi>(amodel, umodel, lmodel);
}

std::shared_ptr<Facade> setupAppContext(void)
{
    const std::unordered_map<std::string, std::string> &map = getMap();
    std::list<std::shared_ptr<CriteriaValueStringConverter::Item>> converters =
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
    std::shared_ptr<CriteriaValueStringConverter> converter = std::make_shared<PSQLCriteriaValueStringConverter>(converters);
    std::shared_ptr<CriteriaFieldMapper> mapper = std::make_shared<CriteriaFieldMapper>(map);
    std::shared_ptr<PSQLCriteriaVisitorBuilder> builder = std::make_shared<PSQLCriteriaVisitorBuilder>();
    builder->setFieldMapper(mapper);
    builder->setValueConverter(converter);
    std::string conn = "user=postgres " "host=localhost " "password=postgres " "dbname=humankind " "port=5432";

    std::shared_ptr<pqxx::connection> connection = setupConnection(conn);
    std::shared_ptr<RepositoryAbstractFactory> rfactory = std::make_shared<PSQLRepositoryAbstractFactory>(connection, builder);
    std::shared_ptr<RepositoryContext> rcontext = std::make_shared<RepositoryContext>(rfactory);

    std::shared_ptr<AppContext> acontext = std::make_shared<AppContext>(rcontext);
    std::shared_ptr<UserMapper> umapper = std::make_shared<UserMapper>();
    umapper->add(std::make_shared<AddressGetter>());
    umapper->add(std::make_shared<LanguageGetter>());
    umapper->add(std::make_shared<SocialGetter>());
    umapper->add(std::make_shared<GeneralGetter>());
    umapper->add(std::make_shared<LivingDatesGetter>());
    std::shared_ptr<RequestHandlerSet> rqhandler = std::make_shared<RequestHandlerSet>();
    rqhandler->add(std::make_shared<ApproveHandler>());
    rqhandler->add(std::make_shared<DeclineHandler>());
    std::shared_ptr<RegistrationHook> rhook = std::make_shared<RegistrationHook>();
    rhook->add(std::make_shared<UserHumanRegistrationHook>());
    rhook->add(std::make_shared<UserRoleRegistrationHook>());
    std::shared_ptr<AuthorizationHook> ahook = std::make_shared<AuthorizationHook>();
    ahook->add(std::make_shared<PSQLAuthorizationHook>(connection));
    auto afactory = std::make_shared<PlainManagerAbstractFactory>(*acontext, MD5LoginManager::hash, umapper, rqhandler, rhook, ahook);
    acontext->setManagerAbstractFactory(afactory);

    std::shared_ptr<Facade> facade = std::make_shared<Facade>(acontext);

    return facade;
}

const std::unordered_map<std::string, std::string> &getMap(void)
{
    static const std::unordered_map<std::string, std::string> map =
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

    return map;
}

std::shared_ptr<pqxx::connection> setupConnection(std::string conn)
{
    std::shared_ptr<pqxx::connection> out = std::make_shared<pqxx::connection>(conn);

    pqxx::nontransaction nt (*out);
    nt.exec("set timezone='Europe/Moscow'");
    nt.exec("set role guest");
    nt.commit();

    return out;
}

