#ifndef _IWRITEREPOSITORY_H_
#define _IWRITEREPOSITORY_H_

#include "repository_exceptions.h"

#include "ICriteria.h"

template <typename T>
class IWriteRepository
{
    public:
        virtual ~IWriteRepository(void) = default;
        virtual void create(const T &item) = 0;
        virtual void update(const T &item) = 0;
        virtual void erase(const T &item) = 0;
        virtual void erase(const ICriteria &criteria) = 0;
};

DEF_EX(CommonWriteRepositoryException, RepositoryException,
       "Common Repository exception");
DEF_EX(NullptrRepositoryException, CommonWriteRepositoryException,
       "Nullptr occured");
DEF_EX(CreateRepositoryException, CommonWriteRepositoryException,
       "Unable to create object");
DEF_EX(UpdateRepositoryException, CommonWriteRepositoryException,
       "Unable to update object");
DEF_EX(NoObjectUpdateRepositoryException, CommonWriteRepositoryException,
       "Updated object doesn't exist");
DEF_EX(EraseRepositoryException, CommonWriteRepositoryException,
       "Unable to erase object");
DEF_EX(NoObjectEraseRepositoryException, CommonWriteRepositoryException,
       "Eraseable object doesn't exist");
DEF_EX(WrongCriteriaWriteRepositoryException, CommonWriteRepositoryException,
       "Incorrect criteria passed");

#endif

