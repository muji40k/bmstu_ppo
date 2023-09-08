#ifndef _USERADMININFOSTRATEGIES_H_
#define _USERADMININFOSTRATEGIES_H_

#include <memory>

#include "IReadRepository.h"
#include "ICriteria.h"

#include "CreateAdminInfoStrategy.h"
#include "GetAdminInfoStrategy.h"
#include "UpdateAdminInfoStrategy.h"
#include "EraseAdminInfoStrategy.h"

#include "User.h"

class UserCreateAdminInfoStrategy : public CreateAdminInfoStrategy
{
    public:
        UserCreateAdminInfoStrategy(const User &user);
        virtual ~UserCreateAdminInfoStrategy(void) override = default;
        virtual void apply(AppContext &context) override;

    private:
        User user;
};

class UserGetAdminInfoStrategy : public GetAdminInfoStrategy,
                                 public GetStrategyResult<std::shared_ptr<IRepositorySet<User>>>
{
    public:
        UserGetAdminInfoStrategy(void) = default;
        UserGetAdminInfoStrategy(const ICriteria &criteria);
        virtual ~UserGetAdminInfoStrategy(void) override = default;
        virtual void apply(AppContext &context) override;
        virtual std::shared_ptr<IRepositorySet<User>> result(void) override;

    private:
        const ICriteria *criteria = nullptr;
        std::shared_ptr<IRepositorySet<User>> res = nullptr;
};

class UserUpdateAdminInfoStrategy : public UpdateAdminInfoStrategy
{
    public:
        UserUpdateAdminInfoStrategy(const User &user);
        virtual ~UserUpdateAdminInfoStrategy(void) override = default;
        virtual void apply(AppContext &context) override;

    private:
        User user;
};

class UserEraseAdminInfoStrategy : public EraseAdminInfoStrategy
{
    public:
        UserEraseAdminInfoStrategy(const ICriteria &criteria);
        virtual ~UserEraseAdminInfoStrategy(void) override = default;
        virtual void apply(AppContext &context) override;

    private:
        const ICriteria &criteria;
};

class UserEraseSingleAdminInfoStrategy : public EraseAdminInfoStrategy
{
    public:
        UserEraseSingleAdminInfoStrategy(const User &user);
        virtual ~UserEraseSingleAdminInfoStrategy(void) override = default;
        virtual void apply(AppContext &context) override;

    private:
        User user;
};

#endif

