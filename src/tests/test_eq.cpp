#include "test_eq.h"

#include <cmath>

#include "User.h"
#include "Human.h"
#include "Place.h"
#include "MergeRequest.h"

template <>
bool test_eq(const User &a, const User &b)
{
    return a.id == b.id
           && a.name == b.name
           && a.password == b.password
           && a.email == b.email;
}

template <>
bool test_eq(const Place &a, const Place &b)
{
    return a.id == b.id
           && a.type == b.type
           && a.name == b.name
           && 1e-8 > fabs(a.area - b.area)
           && a.continent == b.continent;
}

template <>
bool test_eq(const Human &a, const Human &b)
{
    return a.id == b.id
           && a.firstName == b.firstName
           && a.lastName == b.lastName
           && a.isPatronymic() == b.isPatronymic()
           && ((a.isPatronymic() && a.patronymic == b.patronymic) || !a.isPatronymic())
           && test_eq(*a.birthPlace, *b.birthPlace);
}

template <>
bool test_eq(const MergeRequest &a, const MergeRequest &b)
{
    return a.id == b.id
           && test_eq(*a.user, *b.user)
           && test_eq(*a.human, *b.human)
           && a.state == b.state;
}

