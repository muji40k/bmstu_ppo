#ifndef _LANGUAGEGETTER_H_
#define _LANGUAGEGETTER_H_

#include "UserMapper.h"

class LanguageGetter : public UserMapper::Getter
{
    public:
        virtual ~LanguageGetter(void) override = default;
        virtual const std::string &type(void) override;
        virtual void map(AppContext &context, const std::string &id, UserMapper::Map &map) override;
};

#endif

