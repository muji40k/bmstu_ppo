#include "IAdminModel.h"

#include <utility>

IAdminModel::Iterator::Iterator (std::shared_ptr<InnerIter> iter)
    : iter(iter)
{}

IAdminModel::Map IAdminModel::Iterator::operator * (void) const
{
    return this->iter->get();
}

IAdminModel::Iterator &IAdminModel::Iterator::operator ++ (void)
{
    this->iter->next();

    return *this;
}

bool IAdminModel::Iterator::operator != (const Iterator &iter) const
{
    return this->iter->notEqual(iter.iter);
}

IAdminModel::Set::Set(std::shared_ptr<InnerSet> set)
    : set(set)
{}

IAdminModel::Iterator IAdminModel::Set::begin(void)
{
    return Iterator(this->set->begin());
}

IAdminModel::Iterator IAdminModel::Set::end(void)
{
    return Iterator(this->set->end());
}

void IAdminModel::create(std::string hash, std::string name, Map map)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        return;

    return (*iter).second->create(hash, map);
}

void IAdminModel::update(std::string hash, std::string name, Map map)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        return;

    return (*iter).second->update(hash, map);
}

void IAdminModel::remove(std::string hash, std::string name, Map map)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        return;

    return (*iter).second->remove(hash, map);
}

void IAdminModel::remove(std::string hash, std::string name, std::list<CriteriaMap> criterias)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        return;

    return (*iter).second->remove(hash, criterias);
}

IAdminModel::Set IAdminModel::get(std::string hash, std::string name, std::list<CriteriaMap> criterias)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        throw CALL_EX(NoHandlerAdminModelException);

    return (*iter).second->get(hash, criterias);
}

IAdminModel::Map IAdminModel::getEmptyMap(std::string name)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        throw CALL_EX(NoHandlerAdminModelException);

    return (*iter).second->getEmptyMap();
}

void IAdminModel::add(std::string name, std::shared_ptr<Mapper> mapper)
{
    auto iter = this->mappers.find(name);

    if (this->mappers.end() == iter)
        this->mappers.emplace(std::make_pair(name, mapper));
    else
        (*iter).second = mapper;
}

