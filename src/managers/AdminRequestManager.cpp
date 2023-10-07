#include "AdminRequestManager.h"

RequestSetIterator::RequestSetIterator(std::shared_ptr<IRepositoryIterator<MergeRequest>> iter)
    : iter(iter)
{
    if (nullptr == iter)
        throw CALL_EX(NullptrRequestSetIteratorException);
}

MergeRequest RequestSetIterator::operator * (void) const
{
    return this->iter->get();
}

RequestSetIterator &RequestSetIterator::operator ++ (void)
{
    this->iter->next();

    return *this;
}

bool RequestSetIterator::operator != (const RequestSetIterator &iter) const
{
    return this->iter->notEqual(iter.iter);
}

RequestSet::RequestSet(std::shared_ptr<IRepositorySet<MergeRequest>> set)
    : valid(true), requests(set)
{
    if (nullptr == set)
        throw CALL_EX(NullptrRequestSetException);
}

RequestSetIterator RequestSet::begin(void)
{
    if (!this->valid)
        throw CALL_EX(InvalidRequestSetExcpetion);

    return RequestSetIterator(this->requests->begin());
}

RequestSetIterator RequestSet::end(void)
{
    if (!this->valid)
        throw CALL_EX(InvalidRequestSetExcpetion);

    if (nullptr == this->e)
        this->e = this->requests->end();

    return RequestSetIterator(this->e);
}

