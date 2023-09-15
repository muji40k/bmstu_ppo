#ifndef _HUMANADDRESS_H_
#define _HUMANADDRESS_H_

#include "property.h"
#include "entity_exceptions.h"

#include "TimeChangeable.h"

#include "Place.h"

class HumanAddress : public TimeChangeable
{
    public:
        HumanAddress(void);
        HumanAddress(unsigned long long id, Place address, time_t valid_from);
        HumanAddress(const HumanAddress &ha);
        virtual ~HumanAddress(void) = default;

        HumanAddress &operator = (const HumanAddress &ha);

        bool operator == (const HumanAddress &ha) const;
        bool operator != (const HumanAddress &ha) const;

        virtual void setTime(const std::time_t &time) override;
        const std::time_t &getTime(void) const;

        DEFAULT_SG(unsigned long long, Id, _id);
        void setCurrentPlace(const Place &place);
        DEFAULT_GETTER(Place, CurrentPlace, _address);

        Property<HumanAddress, unsigned long long> id;
        Property<HumanAddress, Place> currentPlace;

    private:
        unsigned long long _id      = 0;
        Place              _address = Place();
};

#endif

