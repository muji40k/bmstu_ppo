#include "UserMapper.h"

UserMapper::UserMapper(std::initializer_list<std::shared_ptr<Getter>> getters)
{
    for (auto getter : getters)
        this->add(getter);
}

void UserMapper::add(std::shared_ptr<Getter> getter)
{
    if (nullptr == getter)
        throw CALL_EX(NullptrUserMapperException);

    if (this->checkDuplicate(*getter))
        throw CALL_EX(DuplicateUserMapperException);

    this->getters.push_back(getter);
}

void UserMapper::map(AppContext &context, const Human &human, UserMapper::Map &map) const
{
    std::string id = std::to_string(human.id);

    this->getMain(human, map);

    for (std::shared_ptr<Getter> getter : this->getters)
        getter->map(context, id, map);
}

bool UserMapper::checkDuplicate(Getter &getter) const
{
    for (auto ptr : this->getters)
        if (ptr->type() == getter.type())
            return true;

    return false;
}

void UserMapper::getMain(const Human &human, UserMapper::Map &map) const
{
    map.emplace(std::pair<std::string, std::string>("first_name", human.firstName));
    map.emplace(std::pair<std::string, std::string>("last_name", human.lastName));

    if (human.isPatronymic())
        map.emplace(std::pair<std::string, std::string>("patronymic", human.patronymic));

    map.emplace(std::pair<std::string, std::string>("birth_place", human.birthPlace->name));
}

