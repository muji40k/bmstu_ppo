#ifndef _USERHUMAN_H_
#define _USERHUMAN_H_

#include <string>

#include "property.h"
#include "user_exceptions.h"

#include "Human.h"

class UserHuman
{
    public:
        UserHuman(void);
        UserHuman(unsigned long long id);
        UserHuman(unsigned long long id, const Human &human);
        UserHuman(const UserHuman &uh);

        UserHuman &operator = (const UserHuman &ur);

        bool isHuman(void) const;
        void setIsHuman(bool state);

        DEFAULT_SG(unsigned long long, Id, _id);
        void setHuman(const Human &human);
        const Human &getHuman(void) const;

        Property<UserHuman, unsigned long long> id;
        Property<UserHuman, Human> human;

    private:
        unsigned long long _id;
        bool _is_human;
        Human _human;
};

DEF_EX(CommonUserHumanException, UserException, "Common UserHuman exception");
DEF_EX(HumanUnsetException, CommonUserHumanException, "Human for user is unset");
DEF_EX(ChronologyException, CommonUserHumanException, "Newer instatnce of Human is set");

#endif

