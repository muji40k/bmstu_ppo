#ifndef _RESOURCE_H_
#define _RESOURCE_H_

#include <string>

#include "property.h"

#include "TimeChangeable.h"

class Resource : public TimeChangeable
{
    public:
        Resource(void);
        Resource(unsigned long long id, std::string type, std::string name,
                 double value, std::string rarity, std::time_t valid_from);
        Resource(const Resource &resource);
        virtual ~Resource(void) = default;

        Resource &operator = (const Resource &resource);
        bool operator < (const Resource &resource) const;
        bool operator == (const Resource &resource) const;
        bool operator != (const Resource &resource) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        DEFAULT_SG(std::string, Type, _type);
        DEFAULT_SG(std::string, Name, _name);
        DEFAULT_SG(double, Value, _value);
        DEFAULT_SG(std::string, Rarity, _rarity);

        const std::time_t &getTime(void) const;

        Property<Resource, unsigned long long> id;
        Property<Resource, std::string> type;
        Property<Resource, std::string> name;
        Property<Resource, double> value;
        Property<Resource, std::string> rarity;

    private:
        unsigned long long _id     = 0;
        std::string        _type   = "none";
        std::string        _name   = "none";
        double             _value  = 0;
        std::string        _rarity = "none";
};

#endif

