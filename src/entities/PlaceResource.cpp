#include "PlaceResource.h"

PlaceResource::PlaceResource(void)
    : TimeChangeable(),
      id(this, &PlaceResource::setId, &PlaceResource::getId)
{}

PlaceResource::PlaceResource(unsigned long long id,
                             std::initializer_list<std::pair<Resource, double>> lst,
                             std::time_t valid_from)
    : PlaceResource()
{
    this->_id = id;
    this->validFrom = valid_from;

    for (const std::pair<Resource, double> &item : lst)
    {
        if (this->_map.end() != this->_map.find(item.first))
            throw CALL_EX(DuplicatePlaceResourceException);

        if (this->validFrom < item.first.validFrom)
            throw CALL_EX(ChronologicalException);

        this->_map.emplace(item);
    }
}

PlaceResource::PlaceResource(const PlaceResource &pr) : PlaceResource()
{
    this->_id = pr._id;
    this->_map = pr._map;
    this->validFrom = pr.validFrom;
}

PlaceResource &PlaceResource::operator = (const PlaceResource &pr)
{
    this->_id = pr._id;
    this->_map = pr._map;
    this->validFrom = pr.validFrom;

    return *this;
}

void PlaceResource::setTime(const std::time_t &time)
{
    for (auto item : this->_map)
        if (item.first.validFrom > time)
            throw CALL_EX(ChronologicalException);

    this->TimeChangeable::setTime(time);
}

void PlaceResource::add(const Resource &item)
{
    if (this->_map.end() != this->_map.find(item))
        throw CALL_EX(DuplicatePlaceResourceException);

    if (this->validFrom < item.validFrom)
        throw CALL_EX(ChronologicalException);

    this->_map.emplace(std::pair(item, 0));
}

void PlaceResource::update(const Resource &item)
{
    if (this->validFrom < item.validFrom)
        throw CALL_EX(ChronologicalException);

    auto iter = this->_map.find(item);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundPlaceResourceException);

    if ((*iter).first.validFrom > item.validFrom)
        throw CALL_EX(ChronologicalException);

    std::pair<Resource, double> save = *iter;
    save.first = item;
    this->_map.erase(iter);
    this->_map.emplace(save);
}

void PlaceResource::del(const Resource &item)
{
    auto iter = this->_map.find(item);

    if (this->_map.end() != iter)
        throw CALL_EX(NotFoundPlaceResourceException);

    this->_map.erase(iter);
}

std::list<Resource> PlaceResource::get(const IQueryableFilter<Resource> &filter) const
{
    std::list<Resource> out;

    for (auto item : this->_map)
        if (filter.check(item.first))
            out.push_back(item.first);

    return out;
}

void PlaceResource::del(const IQueryableFilter<Resource> &filter)
{
    for (auto iter = this->_map.begin(); this->_map.end() != iter;)
        if (filter.check((*iter).first))
            iter = this->_map.erase(iter);
        else
            ++iter;
}

const double &PlaceResource::getVolume(const Resource &resource) const
{
    auto iter = this->_map.find(resource);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundPlaceResourceException);

    return (*iter).second;
}

void PlaceResource::setVolume(const Resource &resource, const double &volume)
{
    std::map<Resource, double>::iterator iter = this->_map.find(resource);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundPlaceResourceException);

    (*iter).second = volume;
}

