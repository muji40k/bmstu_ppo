#ifndef _MERGEREQUEST_H_
#define _MERGEREQUEST_H_

#include <string>

#include "property.h"

#include "User.h"
#include "Human.h"

class MergeRequest
{
    public:
        MergeRequest(void);
        MergeRequest(unsigned long long id, const User &user,
                     const Human &human, const std::string &state);
        MergeRequest(const MergeRequest &rq);

        MergeRequest &operator = (const MergeRequest &rq);

        bool operator == (const MergeRequest &rq) const;
        bool operator != (const MergeRequest &rq) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(User, User, _user);
        DEFAULT_SG(Human, Human, _human);
        DEFAULT_SG(std::string, State, _state);

        Property<MergeRequest, unsigned long long> id;
        Property<MergeRequest, User> user;
        Property<MergeRequest, Human> human;
        Property<MergeRequest, std::string> state;

    private:
        unsigned long long _id;
        User _user;
        Human _human;
        std::string _state = "new";
};

#endif

