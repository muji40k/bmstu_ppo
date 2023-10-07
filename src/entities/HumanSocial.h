#ifndef _HUMANSOCIAL_H_
#define _HUMANSOCIAL_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class HumanSocial : public TimeChangeable
{
    public:
        HumanSocial(void);
        HumanSocial(unsigned long long id, std::string religion,
                    std::string wealth, std::string literacy,
                    std::string busyness, std::time_t valid_from);
        HumanSocial(const HumanSocial &hc);
        virtual ~HumanSocial(void) = default;

        HumanSocial &operator = (const HumanSocial &hc);

        bool operator == (const HumanSocial &hc) const;
        bool operator != (const HumanSocial &hc) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Religion, _religion);
        DEFAULT_SG(std::string, Wealth, _wealth);
        DEFAULT_SG(std::string, Literacy, _literacy);
        DEFAULT_SG(std::string, Busyness, _busyness);

        const std::time_t &getTime(void) const;

        Property<HumanSocial, unsigned long long> id;
        Property<HumanSocial, std::string> religion;
        Property<HumanSocial, std::string> wealth;
        Property<HumanSocial, std::string> literacy;
        Property<HumanSocial, std::string> busyness;

    private:
        unsigned long long _id        = 0;
        std::string        _religion  = "none";
        std::string        _wealth    = "none";
        std::string        _literacy  = "none";
        std::string        _busyness  = "none";
};

#endif

