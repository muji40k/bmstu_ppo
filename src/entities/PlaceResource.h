#ifndef _PLACERESOURCE_H_
#define _PLACERESOURCE_H_

#include <map>
#include <utility>
#include <initializer_list>

#include "property.h"

#include "TimeChangeable.h"
#include "IQueryable.h"

#include "Resource.h"

class PlaceResource : public TimeChangeable, public IQueryable<Resource>
{
    public:
        PlaceResource(void);
        PlaceResource(unsigned long long id,
                      std::initializer_list<std::pair<Resource, double>> lst,
                      std::time_t valid_from);
        PlaceResource(const PlaceResource &pr);
        virtual ~PlaceResource(void) = default;

        PlaceResource &operator = (const PlaceResource &pr);

        DEFAULT_SG(unsigned long long, Id, _id);

        Property<PlaceResource, unsigned long long> id;

        virtual void setTime(const std::time_t &time) override;

        virtual void add(const Resource &item) override;
        virtual void update(const Resource &item) override;
        virtual void del(const Resource &item) override;
        virtual std::list<Resource> get(const IQueryableFilter<Resource> &filter) const override;
        virtual void del(const IQueryableFilter<Resource> &filter) override;

        const double &getVolume(const Resource &resource) const;
        void setVolume(const Resource &resource, const double &volume);

    private:
        unsigned long long _id = 0;
        std::map<Resource, double> _map;
};

DEF_EX(CommonPlaceResourceException, EntityException,
       "Common PlaceResource exception");
DEF_EX(DuplicatePlaceResourceException, CommonPlaceResourceException,
       "Duplication of Resource in set");
DEF_EX(NotFoundPlaceResourceException, CommonPlaceResourceException,
       "Resource isn't presented in set");

#endif

