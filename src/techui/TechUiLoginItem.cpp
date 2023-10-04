#include "TechUiLoginItem.h"

#include <iostream>
#include <iomanip>

#include "TechUiLoginItem.h"

#include <iostream>
#include <iomanip>

TechUiLoginItem::TechUiLoginItem(std::string &hash)
    : hash(hash),
      handlers({
                 {"login", &TechUiLoginItem::login},
                 {"update", &TechUiLoginItem::update},
                 {"register", &TechUiLoginItem::registerUser},
                 {"exit", &TechUiLoginItem::exit}
               })
{}

bool TechUiLoginItem::check(std::string command)
{
    auto iter = this->handlers.find(command);

    return this->handlers.end() != iter;
}

int TechUiLoginItem::perform(std::string command, std::string &)
{
    auto iter = this->handlers.find(command);

    if (this->handlers.end() == iter)
        return 1;

    (this->*(*iter).second)();

    return 0;
}

void TechUiLoginItem::onLoginSuccess(std::string hash)
{
    if (nullptr == presenter)
        return;

    std::cout << "Вход выполнен успешно" << std::endl;
    this->hash = hash;
}

void TechUiLoginItem::onLoginFailure(std::string message)
{
    if (nullptr == presenter)
        return;

    std::cout << "Ошибка входа: " << message << std::endl;
}

void TechUiLoginItem::onUpdateSuccess(std::string hash)
{
    if (nullptr == presenter)
        return;

    std::cout << "Вход обновлен" << std::endl;
    this->hash = hash;
}

void TechUiLoginItem::onUpdateFailure(std::string message)
{
    if (nullptr == presenter)
        return;

    std::cout << "Ошибка обновления: " << message << std::endl;
}

void TechUiLoginItem::onRegisterSuccess(void)
{
    if (nullptr == presenter)
        return;

    std::cout << "Регистрация выполнена успешно" << std::endl;
}

void TechUiLoginItem::onRegisterFailure(std::string message)
{
    if (nullptr == presenter)
        return;

    std::cout << "Ошибка регистрации: " << message << std::endl;
}

void TechUiLoginItem::onExit(void)
{
    if (nullptr == presenter)
        return;

    std::cout << "Выполнен выход" << std::endl;
}

void TechUiLoginItem::onError(std::string message)
{
    if (nullptr == presenter)
        return;

    std::cout << "Ошибка: " << message << std::endl;
}

void TechUiLoginItem::login(void)
{
    std::string email, password;

    std::cout << "Введите email: ";
    std::getline(std::cin, email);
    std::cout << "Введите пароль: ";
    std::getline(std::cin, password);

    this->presenter->login(email, password);
}

void TechUiLoginItem::update(void)
{
    this->presenter->update(this->hash);
}

void TechUiLoginItem::registerUser(void)
{
    std::string email, password, name;

    std::cout << "Введите название: ";
    std::getline(std::cin, name);
    std::cout << "Введите email: ";
    std::getline(std::cin, email);
    std::cout << "Введите пароль: ";
    std::getline(std::cin, password);

    this->presenter->registerUser(email, password, name);
}

void TechUiLoginItem::exit(void)
{
    this->presenter->exit(this->hash);
}

