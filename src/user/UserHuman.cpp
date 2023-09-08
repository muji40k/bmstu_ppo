#include "UserHuman.h"

UserHuman::UserHuman(void)
    : id(this, &UserHuman::setId, &UserHuman::getId),
      human(this, &UserHuman::setHuman, &UserHuman::getHuman)
{}

UserHuman::UserHuman(unsigned long long id) : UserHuman()
{
    this->_id = id;
    this->_is_human = false;
}

UserHuman::UserHuman(unsigned long long id, const Human &human) : UserHuman()
{
    this->_id = id;
    this->_is_human = true;
    this->_human = human;
}

UserHuman::UserHuman(const UserHuman &uh) : UserHuman()
{
    this->_id = uh._id;
    this->_is_human = uh._is_human;
    this->_human = uh._human;
}

UserHuman &UserHuman::operator = (const UserHuman &uh)
{
    this->_id = uh._id;
    this->_is_human = uh._is_human;
    this->_human = uh._human;

    return *this;
}

bool UserHuman::isHuman(void) const { return this->_is_human; }
void UserHuman::setIsHuman(bool state) { this->_is_human = state; }

void UserHuman::setHuman(const Human &human)
{
    if (!this->_is_human)
        throw CALL_EX(HumanUnsetException);

    if (human.validFrom < this->_human.validFrom)
        throw CALL_EX(ChronologyException);

    this->_human = human;
}

const Human &UserHuman::getHuman(void) const
{
    if (!this->_is_human)
        throw CALL_EX(HumanUnsetException);

    return this->_human;
}

