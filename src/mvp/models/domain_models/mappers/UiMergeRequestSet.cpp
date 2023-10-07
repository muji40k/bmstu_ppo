#include "UiMergeRequestSet.h"

IAdminModel::Map UiMergeRequestMapper::mapRequest(const MergeRequest &mr)
{
    IAdminModel::Map out;

    out.emplace("id", std::to_string(*mr.id));
    out.emplace("state", *mr.state);
    out.emplace("user.id", std::to_string(*mr.user->id));
    out.emplace("user.email", *mr.user->email);
    out.emplace("user.name", *mr.user->name);
    out.emplace("human.id", std::to_string(*mr.human->id));
    out.emplace("human.firstName", *mr.human->firstName);
    out.emplace("human.lastName", *mr.human->lastName);
    out.emplace("human.validFrom", DateCommon::getTime(mr.human->validFrom));

    if (mr.human->isPatronymic())
        out.emplace("human.patronymic", *mr.human->patronymic);
    else
        out.emplace("human.patronymic", "");

    const Place &place = mr.human->birthPlace;
    out.emplace("human.birth_place.id", std::to_string(*place.id));
    out.emplace("human.birth_place.type", *place.type);
    out.emplace("human.birth_place.name", *place.name);
    out.emplace("human.birth_place.area", std::to_string(*place.area));
    out.emplace("human.birth_place.continent", *place.continent);
    out.emplace("human.birth_place.validFrom", DateCommon::getTime(place.validFrom));

    return out;
}

MergeRequest UiMergeRequestMapper::unmapRequest(IAdminModel::Map map)
{
    Place place;
    User user;
    Human human;

    place.id = std::stoull(map.at("human.birth_place.id"));
    place.type = map.at("human.birth_place.type");
    place.name = map.at("human.birth_place.name");
    place.area = std::stod(map.at("human.birth_place.area"));
    place.continent = map.at("human.birth_place.continent");
    place.validFrom = DateCommon::parseTime(map.at("human.birth_place.validFrom"),
                                              "%A %B %d %H:%M:%S %Y");

    human.id = std::stoull(map.at("human.id"));
    human.firstName = map.at("human.firstName");
    human.lastName = map.at("human.lastName");

    if ("" != map.at("human.patronymic"))
    {
        human.setIsPatronymic(true);
        human.patronymic = map.at("human.patronymic");
    }

    human.validFrom = DateCommon::parseTime(map.at("human.validFrom"),
                                              "%A %B %d %H:%M:%S %Y");
    human.birthPlace = place;

    user.id = std::stoull(map.at("user.id"));
    user.email = map.at("user.email");
    user.name = map.at("user.name");

    return MergeRequest (std::stoull(map["id"]), user, human, map["state"]);
}

UiMergeRequestIterator::UiMergeRequestIterator(RequestSetIterator iter)
    : iter(iter)
{}

void UiMergeRequestIterator::next(void)
{
    ++this->iter;
}

IAdminModel::Map UiMergeRequestIterator::get(void) const
{
    return UiMergeRequestMapper::mapRequest(*iter);
}

bool UiMergeRequestIterator::notEqual(std::shared_ptr<const InnerIter> iter) const
{
    std::shared_ptr<const UiMergeRequestIterator> citer = std::dynamic_pointer_cast<const UiMergeRequestIterator>(iter);

    if (nullptr == citer)
        throw;

    return this->iter != citer->iter;
}

UiMergeRequestSet::UiMergeRequestSet(RequestSet set)
    : set(set)
{}

std::shared_ptr<IAdminModel::InnerIter> UiMergeRequestSet::begin(void)
{
    return std::make_shared<UiMergeRequestIterator>(this->set.begin());
}

std::shared_ptr<IAdminModel::InnerIter> UiMergeRequestSet::end(void)
{
    return std::make_shared<UiMergeRequestIterator>(this->set.end());
}

