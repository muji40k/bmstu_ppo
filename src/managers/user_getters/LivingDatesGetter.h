#ifndef _LIVINGDATESGETTER_H_
#define _LIVINGDATESGETTER_H_

#include "UserMapper.h"

class LivingDatesGetter : public UserMapper::Getter
{
    public:
        virtual ~LivingDatesGetter(void) override = default;
        virtual const std::string &type(void) override;
        virtual void map(AppContext &context, const std::string &id, UserMapper::Map &map) override;
};

#endif

