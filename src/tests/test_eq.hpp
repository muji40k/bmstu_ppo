#include "test_eq.h"

#include <cmath>

#include "User.h"
#include "UserRole.h"
#include "UserHuman.h"
#include "MergeRequest.h"
#include "Human.h"
#include "HumanLivingDates.h"
#include "HumanSocial.h"
#include "HumanGeneral.h"
#include "HumanAddress.h"
#include "Place.h"
#include "PlaceCountry.h"
#include "Country.h"
#include "Resource.h"
#include "Language.h"

template <>
bool test_eq(const User &a, const User &b)
{
    return a.id == b.id
           && a.name == b.name
           && a.password == b.password
           && a.email == b.email;
}

template <>
bool test_eq(const UserRole &a, const UserRole &b)
{
    return a.id == b.id
           && a.userId == b.userId
           && a.role == b.role;
}

template <>
bool test_eq(const Country &a, const Country &b)
{
    return a.id == b.id
           && a.type == b.type
           && a.name == b.name
           && a.gdp == b.gdp
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const Place &a, const Place &b)
{
    return a.id == b.id
           && a.type == b.type
           && a.name == b.name
           && 1e-8 > fabs(a.area - b.area)
           && a.continent == b.continent
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const PlaceCountry &a, const PlaceCountry &b)
{
    return a.id == b.id
           && test_eq(*a.country, *b.country)
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const Human &a, const Human &b)
{
    return a.id == b.id
           && a.firstName == b.firstName
           && a.lastName == b.lastName
           && a.isPatronymic() == b.isPatronymic()
           && ((a.isPatronymic() && a.patronymic == b.patronymic) || !a.isPatronymic())
           && test_eq(*a.birthPlace, *b.birthPlace)
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const HumanLivingDates &a, const HumanLivingDates &b)
{
    std::time_t time = std::time(nullptr);
    return a.id == b.id
           && a.birthDate == b.birthDate
           && ((a.isAlive(time) && b.isAlive(time) && a.deathDate == b.deathDate)
               || (!a.isAlive(time) && !b.isAlive(time)))
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const HumanSocial &a, const HumanSocial &b)
{
    return a.id == b.id
           && a.wealth == b.wealth
           && a.religion == b.religion
           && a.busyness == b.busyness
           && a.literacy == b.literacy
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const HumanGeneral &a, const HumanGeneral &b)
{
    return a.id == b.id
           && a.bloodType == b.bloodType
           && a.gender == b.gender
           && a.race == b.race
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const HumanAddress &a, const HumanAddress &b)
{
    return a.id == b.id
           && test_eq(*a.currentPlace, *b.currentPlace)
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const UserHuman &a, const UserHuman &b)
{
    return a.id == b.id
           && ((a.isHuman() && b.isHuman() && test_eq<Human>(a.human, b.human))
               || (!a.isHuman() && !b.isHuman()));
}

template <>
bool test_eq(const MergeRequest &a, const MergeRequest &b)
{
    return a.id == b.id
           && test_eq(*a.user, *b.user)
           && test_eq(*a.human, *b.human)
           && a.state == b.state;
}

template <>
bool test_eq(const Resource &a, const Resource &b)
{
    return a.id == b.id
           && a.type == b.type
           && a.name == b.name
           && a.rarity == b.rarity
           && a.value == b.value
           && a.validFrom == b.validFrom;
}

template <>
bool test_eq(const Language &a, const Language &b)
{
    return a.id == b.id
           && a.name == b.name
           && a.family == b.family
           && a.validFrom == b.validFrom;
}

