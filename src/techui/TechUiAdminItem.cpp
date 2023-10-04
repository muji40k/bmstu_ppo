#include "TechUiAdminItem.h"

#include <iostream>
#include <iomanip>

TechUiAdminItem::TechUiAdminItem(void)
    : handlers({
                 {"is_admin", &TechUiAdminItem::isAdmin},
                 {"get_requests", &TechUiAdminItem::getRequests},
                 {"set_request", &TechUiAdminItem::setRequest},
                 {"create", &TechUiAdminItem::create},
                 {"update", &TechUiAdminItem::update},
                 {"remove", &TechUiAdminItem::remove},
                 {"get_entity", &TechUiAdminItem::get}
               })
{}

bool TechUiAdminItem::check(std::string command)
{
    auto iter = this->handlers.find(command);

    return this->handlers.end() != iter;
}

int TechUiAdminItem::perform(std::string command, std::string &hash)
{
    auto iter = this->handlers.find(command);

    if (this->handlers.end() == iter)
        return 1;

    (this->*(*iter).second)(hash);

    return 0;
}

void TechUiAdminItem::onIsAdmin(bool result)
{
    if (!this->presenter)
        return;

    if (result)
        std::cout << "Пользователь - администратор" << std::endl;
    else
        std::cout << "Пользователь - не администратор" << std::endl;
}

void TechUiAdminItem::onGetRequests(IAdminModel::Set result)
{
    if (!this->presenter)
        return;

    auto iter = this->sets.find("MergeRequest");

    if (this->sets.end() == iter)
        this->sets.emplace("MergeRequest", result);
    else
        (*iter).second = result;

    std::cout << "Результат: " << std::endl;

    for (auto item : result)
    {
        for (auto pair : item)
            std::cout << std::setfill(' ') << std::setw(30)
                      << pair.first << ": " << pair.second << std::endl;

        std::cout << std::endl;
    }
}

void TechUiAdminItem::onGet(std::string name, IAdminModel::Set result)
{
    if (!this->presenter)
        return;

    auto iter = this->sets.find(name);

    if (this->sets.end() == iter)
        this->sets.emplace(name, result);
    else
        (*iter).second = result;

    std::cout << "Результат: " << std::endl;

    for (auto item : result)
    {
        for (auto pair : item)
            std::cout << std::setfill(' ') << std::setw(20)
                      << pair.first << ": " << pair.second << std::endl;

        std::cout << std::endl;
    }
}

void TechUiAdminItem::onNotAuthenticated(void)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: не был произведен вход" << std::endl;
}

void TechUiAdminItem::onNotAuthorized(void)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: пользователь не является администратором" << std::endl;
}

void TechUiAdminItem::onError(std::string message)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: " << message << std::endl;
}

void TechUiAdminItem::isAdmin(std::string hash)
{
    if (!this->presenter)
        return;

    this->presenter->isAdmin(hash);
}

void TechUiAdminItem::getRequests(std::string hash)
{
    if (!this->presenter)
        return;

    this->presenter->getRequests(hash);
}

void TechUiAdminItem::setRequest(std::string hash)
{
    if (!this->presenter)
        return;

    auto iter = this->sets.find("MergeRequest");

    if (this->sets.end() == iter)
    {
        std::cout << "Запросы не найдены" << std::endl;
        return;
    }

    std::string id;

    std::cout << "Выберите id запроса: ";
    std::getline(std::cin, id);

    IAdminModel::Set &set = (*iter).second;
    auto map_iter = set.begin();

    for (; set.end() != map_iter && (*map_iter)["id"] != id; ++map_iter);

    if (!(set.end() != map_iter))
    {
        std::cout << "Запрос с заданным id не найден" << std::endl;
        return;
    }

    IAdminModel::Map copy = *map_iter;
    std::cout << "Задайте состояние: ";
    std::getline(std::cin, copy.at("state"));

    this->presenter->setRequest(hash, copy);
}

void TechUiAdminItem::create(std::string hash)
{
    if (!this->presenter)
        return;

    std::string name;
    std::cout << "Введите имя сущности: ";
    std::getline(std::cin, name);

    IAdminModel::Map map = this->presenter->getEmptyMap(name);

    for (auto &pair : map)
        if (pair.first != "id")
        {
            std::cout << pair.first << ": ";
            std::getline(std::cin, pair.second);
        }

    this->presenter->create(hash, name, map);
}

void TechUiAdminItem::update(std::string hash)
{
    if (!this->presenter)
        return;

    std::string name;
    std::cout << "Введите имя сущности: ";
    std::getline(std::cin, name);

    auto iter = this->sets.find(name);

    if (this->sets.end() == iter)
    {
        std::cout << "Сущности не найдены" << std::endl;
        return;
    }

    std::string id;

    std::cout << "Выберите id сущности: ";
    std::getline(std::cin, id);

    IAdminModel::Set &set = (*iter).second;
    auto map_iter = set.begin();

    for (; set.end() != map_iter && (*map_iter)["id"] != id; ++map_iter);

    if (!(set.end() != map_iter))
    {
        std::cout << "Сущность с заданным id не найдена" << std::endl;
        return;
    }

    IAdminModel::Map copy = *map_iter;

    for (auto &pair : copy)
        if ("id" != pair.first)
        {
            std::string tmp;
            std::cout << pair.first << ": ";
            std::getline(std::cin, tmp);

            if ("" != tmp)
                pair.second = tmp;
        }

    this->presenter->update(hash, name, copy);
}

void TechUiAdminItem::remove(std::string hash)
{
    if (!this->presenter)
        return;

    std::string name;
    std::cout << "Введите имя сущности: ";
    std::getline(std::cin, name);

    auto iter = this->sets.find(name);

    if (this->sets.end() == iter)
    {
        std::cout << "Сущности не найдены" << std::endl;
        return;
    }

    std::string id;

    std::cout << "Выберите id сущности: ";
    std::getline(std::cin, id);

    IAdminModel::Set &set = (*iter).second;
    auto map_iter = set.begin();

    for (; set.end() != map_iter && (*map_iter)["id"] != id; ++map_iter);

    if (!(set.end() != map_iter))
    {
        std::cout << "Сущность с заданным id не найдена" << std::endl;
        return;
    }

    this->presenter->update(hash, name, *map_iter);
}

void TechUiAdminItem::get(std::string hash)
{
    if (!this->presenter)
        return;

    std::string name;
    std::cout << "Введите имя сущности: ";
    std::getline(std::cin, name);

    this->presenter->get(hash, name);
}

