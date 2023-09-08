#include "MergeRequest.h"

MergeRequest::MergeRequest(void)
    : id(this, &MergeRequest::setId, &MergeRequest::getId),
      user(this, &MergeRequest::setUser, &MergeRequest::getUser),
      human(this, &MergeRequest::setHuman, &MergeRequest::getHuman),
      state(this, &MergeRequest::setState, &MergeRequest::getState)
{}

MergeRequest::MergeRequest(unsigned long long id, const User &user,
                           const Human &human, const std::string &state)
    : MergeRequest()
{
    this->_id = id;
    this->_user = user;
    this->_human = human;
    this->_state = state;
}

MergeRequest::MergeRequest(const MergeRequest &rq) : MergeRequest()
{
    this->_id = rq._id;
    this->_user = rq._user;
    this->_human = rq._human;
    this->_state = rq._state;
}

MergeRequest &MergeRequest::operator = (const MergeRequest &rq)
{
    this->_id = rq._id;
    this->_user = rq._user;
    this->_human = rq._human;
    this->_state = rq._state;

    return *this;
}

