#include "TechUiUserItem.h"

#include <iostream>
#include <iomanip>

TechUiUserItem::TechUiUserItem(void)
    : handlers({
                 {"get_info", &TechUiUserItem::getInfo},
                 {"set_info", &TechUiUserItem::setInfo},
                 {"is_human", &TechUiUserItem::isHuman},
                 {"get_human", &TechUiUserItem::getHuman},
                 {"find_human", &TechUiUserItem::findHuman},
                 {"set_human", &TechUiUserItem::setHuman}
               })
{}

bool TechUiUserItem::check(std::string command)
{
    auto iter = this->handlers.find(command);

    return this->handlers.end() != iter;
}

int TechUiUserItem::perform(std::string command, std::string &hash)
{
    auto iter = this->handlers.find(command);

    if (this->handlers.end() == iter)
        return 1;

    (this->*(*iter).second)(hash);

    return 0;
}

void TechUiUserItem::onGetInfo(IUserModel::Data data)
{
    if (!this->presenter)
        return;

    for (auto pair : data)
        std::cout << std::setfill(' ') << std::setw(20)
                  << pair.first << ": " << pair.second << std::endl;

    std::cout << std::endl;
}

void TechUiUserItem::onIsHuman(bool mark)
{
    if (!this->presenter)
        return;

    if (mark)
        std::cout << "Пользователь для человека установлен" << std::endl;
    else
        std::cout << "Пользователь для человека не установлен" << std::endl;

}

void TechUiUserItem::onGetHuman(IUserModel::Data data)
{
    if (!this->presenter)
        return;

    for (auto pair : data)
        std::cout << std::setfill(' ') << std::setw(20)
                  << pair.first << ": " << pair.second << std::endl;

    std::cout << std::endl;
}

void TechUiUserItem::onFindHuman(std::list<IUserModel::Data> result)
{
    if (!this->presenter)
        return;

    this->sets = result;

    for (auto item : result)
    {
        for (auto pair : item)
            std::cout << std::setfill(' ') << std::setw(20)
                      << pair.first << ": " << pair.second << std::endl;

        std::cout << std::endl;
    }
}

void TechUiUserItem::onNotAuthenticated(void)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: не был произведен вход" << std::endl;
}

void TechUiUserItem::onNotAuthorized(void)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: пользователь не авторизован" << std::endl;
}

void TechUiUserItem::onError(std::string message)
{
    if (!this->presenter)
        return;

    std::cout << "Ошибка: " << message << std::endl;
}

void TechUiUserItem::getInfo(std::string hash)
{
    if (!this->presenter)
        return;

    this->presenter->getInfo(hash);
}

void TechUiUserItem::setInfo(std::string hash)
{
    if (!this->presenter)
        return;

    IUserModel::Data out =
    {
        {"email", ""},
        {"name", ""},
        {"password", ""}
    };

    for (auto iter = out.begin(); out.end() != iter;)
    {
        std::string tmp;
        std::cout << (*iter).first << ": ";
        std::getline(std::cin, tmp);

        if ("" == tmp)
            iter = out.erase(iter);
        else
        {
            (*iter).second = tmp;
            ++iter;
        }
    }

    this->presenter->setInfo(hash, out);
}

void TechUiUserItem::isHuman(std::string hash)
{
    if (!this->presenter)
        return;

    this->presenter->isHuman(hash);
}

void TechUiUserItem::getHuman(std::string hash)
{
    if (!this->presenter)
        return;

    this->presenter->getHuman(hash);
}

void TechUiUserItem::findHuman(std::string hash)
{
    if (!this->presenter)
        return;

    IUserModel::Data out =
    {
        {"first_name", ""},
        {"last_name", ""},
        {"patronymic", ""}
    };

    for (auto iter = out.begin(); out.end() != iter;)
    {
        std::string tmp;
        std::cout << (*iter).first << ": ";
        std::getline(std::cin, tmp);

        if ("" == tmp)
            iter = out.erase(iter);
        else
        {
            (*iter).second = tmp;
            ++iter;
        }
    }

    this->presenter->findHuman(hash, out);
}

void TechUiUserItem::setHuman(std::string hash)
{
    if (!this->presenter)
        return;

    std::string id;
    std::cout << "Выберите id сущности: ";
    std::getline(std::cin, id);

    auto iter = this->sets.begin();

    for (; this->sets.end() != iter && (*iter)["id"] != id; ++iter);

    if (this->sets.end() == iter)
    {
        std::cout << "Человек не найден" << std::endl;
        return;
    }

    this->presenter->setHuman(hash, *iter);
}

