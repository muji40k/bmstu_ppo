#include "HumanLanguage.h"

HumanLanguage::HumanLanguage(void)
    : TimeChangeable(),
      id(this, &HumanLanguage::setId, &HumanLanguage::getId)
{}

HumanLanguage::HumanLanguage(unsigned long long id,
                             std::initializer_list<std::pair<Language, std::string>> lst,
                             std::time_t valid_from)
    : HumanLanguage()
{
    this->_id = id;
    this->validFrom = valid_from;

    for (const std::pair<Language, std::string> &item : lst)
    {
        if (this->_map.end() != this->_map.find(item.first))
            throw CALL_EX(DuplicateHumanLanguageException);

        if (this->validFrom < item.first.validFrom)
            throw CALL_EX(ChronologicalException);

        this->_map.emplace(item);
    }
}

HumanLanguage::HumanLanguage(const HumanLanguage &hl) : HumanLanguage()
{
    this->_id = hl._id;
    this->_map = hl._map;
    this->validFrom = hl.validFrom;
}

HumanLanguage &HumanLanguage::operator = (const HumanLanguage &hl)
{
    this->_id = hl._id;
    this->_map = hl._map;
    this->validFrom = hl.validFrom;

    return *this;
}

void HumanLanguage::setTime(const std::time_t &time)
{
    for (auto item : this->_map)
        if (item.first.validFrom > time)
            throw CALL_EX(ChronologicalException);

    this->TimeChangeable::setTime(time);
}

void HumanLanguage::add(const Language &item)
{
    if (this->_map.end() != this->_map.find(item))
        throw CALL_EX(DuplicateHumanLanguageException);

    if (this->validFrom < item.validFrom)
        throw CALL_EX(ChronologicalException);

    this->_map.emplace(std::pair(item, "unset"));
}

void HumanLanguage::update(const Language &item)
{
    if (this->validFrom < item.validFrom)
        throw CALL_EX(ChronologicalException);

    auto iter = this->_map.find(item);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundHumanLanguageException);

    if ((*iter).first.validFrom > item.validFrom)
        throw CALL_EX(ChronologicalException);

    std::pair<Language, std::string> save = *iter;
    save.first = item;
    this->_map.erase(iter);
    this->_map.emplace(save);
}

void HumanLanguage::del(const Language &item)
{
    auto iter = this->_map.find(item);

    if (this->_map.end() != iter)
        throw CALL_EX(NotFoundHumanLanguageException);

    this->_map.erase(iter);
}

std::list<Language> HumanLanguage::get(const IQueryableFilter<Language> &filter) const
{
    std::list<Language> out;

    for (auto item : this->_map)
        if (filter.check(item.first))
            out.push_back(item.first);

    return out;
}

void HumanLanguage::del(const IQueryableFilter<Language> &filter)
{
    for (auto iter = this->_map.begin(); this->_map.end() != iter;)
        if (filter.check((*iter).first))
            iter = this->_map.erase(iter);
        else
            ++iter;
}

const std::string &HumanLanguage::getLevel(const Language &language) const
{
    auto iter = this->_map.find(language);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundHumanLanguageException);

    return (*iter).second;
}

void HumanLanguage::setLevel(const Language &language, const std::string &level)
{
    std::map<Language, std::string>::iterator iter = this->_map.find(language);

    if (this->_map.end() == iter)
        throw CALL_EX(NotFoundHumanLanguageException);

    (*iter).second = level;
}

