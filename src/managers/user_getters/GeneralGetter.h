#ifndef _GENERALGETTER_H_
#define _GENERALGETTER_H_

#include "UserMapper.h"

class GeneralGetter : public UserMapper::Getter
{
    public:
        virtual ~GeneralGetter(void) override = default;
        virtual const std::string &type(void) override;
        virtual void map(AppContext &context, const std::string &id, UserMapper::Map &map) override;
};

#endif

