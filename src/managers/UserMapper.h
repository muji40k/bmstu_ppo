#ifndef _USERMAPPER_H_
#define _USERMAPPER_H_

#include <memory>
#include <unordered_map>
#include <initializer_list>
#include <list>
#include <string>

#include "manager_exceptions.h"

#include "AppContext.h"

class UserMapper
{
    public:
        using Map = std::unordered_map<std::string, std::string>;

        class Getter
        {
            public:
                virtual ~Getter(void) = default;
                virtual const std::string &type(void) = 0;
                virtual void map(AppContext &, const std::string &, Map &) = 0;
        };

    public:
        UserMapper(void) = default;
        UserMapper(std::initializer_list<std::shared_ptr<Getter>> getters);

        void add(std::shared_ptr<Getter> getter);
        void map(AppContext &context, const Human &human, Map &map) const;

    private:
        bool checkDuplicate(Getter &getter) const;
        void getMain(const Human &human, UserMapper::Map &map) const;

        std::list<std::shared_ptr<Getter>> getters;
};

DEF_EX(CommonUserMapperException, ManagerException, "Common UserMapper exception");
DEF_EX(NullptrUserMapperException, CommonUserMapperException,
       "Nullptr occured");
DEF_EX(DuplicateUserMapperException, CommonUserMapperException,
       "Gettter duplicate");

#endif

