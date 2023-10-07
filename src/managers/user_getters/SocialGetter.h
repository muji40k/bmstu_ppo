#ifndef _SOCIALGETTER_H_
#define _SOCIALGETTER_H_

#include "UserMapper.h"

class SocialGetter : public UserMapper::Getter
{
    public:
        virtual ~SocialGetter(void) override = default;
        virtual const std::string &type(void) override;
        virtual void map(AppContext &context, const std::string &id, UserMapper::Map &map) override;
};

#endif

