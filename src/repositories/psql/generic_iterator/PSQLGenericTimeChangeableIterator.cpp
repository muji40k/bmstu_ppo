#include "PSQLGenericTimeChangeableIterator.h"

PSQLGenericRepositoryIdIterator::PSQLGenericRepositoryIdIterator(pqxx::result::const_iterator iter)
    : iter(iter)
{}

unsigned long long PSQLGenericRepositoryIdIterator::get(void)
{
    return (*this->iter)["id"].as<unsigned long long>();
}

void PSQLGenericRepositoryIdIterator::next()
{
    ++this->iter;
}

bool PSQLGenericRepositoryIdIterator::notEqual(std::shared_ptr<IRepositoryIdIterator> iter)
{
    std::shared_ptr<PSQLGenericRepositoryIdIterator> citer = std::dynamic_pointer_cast<PSQLGenericRepositoryIdIterator>(iter);

    if (nullptr == citer)
        throw CALL_EX(IncompatibleRepositoryIdIteratorException);

    return this->iter != citer->iter;
}

