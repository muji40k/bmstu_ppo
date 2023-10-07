#ifndef _HUMANLANGUAGE_H_
#define _HUMANLANGUAGE_H_

#include <string>
#include <map>
#include <utility>
#include <initializer_list>

#include "property.h"

#include "TimeChangeable.h"
#include "IQueryable.h"

#include "Language.h"

class HumanLanguage : public TimeChangeable, public IQueryable<Language>
{
    public:
        HumanLanguage(void);
        HumanLanguage(unsigned long long id,
                      std::initializer_list<std::pair<Language, std::string>> lst,
                      std::time_t valid_from);
        HumanLanguage(const HumanLanguage &hl);
        virtual ~HumanLanguage(void) = default;

        HumanLanguage &operator = (const HumanLanguage &hc);

        bool operator == (const HumanLanguage &hl) const;
        bool operator != (const HumanLanguage &hl) const;

        DEFAULT_SG(unsigned long long, Id, _id);

        Property<HumanLanguage, unsigned long long> id;

        virtual void setTime(const std::time_t &time) override;
        const std::time_t &getTime(void) const;

        virtual void add(const Language &item) override;
        virtual void update(const Language &item) override;
        virtual void del(const Language &item) override;
        virtual std::list<Language> get(const IQueryableFilter<Language> &filter) const override;
        virtual void del(const IQueryableFilter<Language> &filter) override;

        const std::string &getLevel(const Language &language) const;
        void setLevel(const Language &language, const std::string &level);

    private:
        unsigned long long _id = 0;
        std::map<Language, std::string> _map;
};

DEF_EX(CommonHumanLanguageException, EntityException,
       "Common HumanLanguage exception");
DEF_EX(DuplicateHumanLanguageException, CommonHumanLanguageException,
       "Duplication of Language in set");
DEF_EX(NotFoundHumanLanguageException, CommonHumanLanguageException,
       "Language isn't presented in set");

#endif

