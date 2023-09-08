#ifndef _ADDRESSGETTER_H_
#define _ADDRESSGETTER_H_

#include "UserMapper.h"

class AddressGetter : public UserMapper::Getter
{
    public:
        virtual ~AddressGetter(void) override = default;
        virtual const std::string &type(void) override;
        virtual void map(AppContext &context, const std::string &id, UserMapper::Map &map) override;
};

#endif

