#ifndef _GENERICEXCEPTIONWRAP_H_
#define _GENERICEXCEPTIONWRAP_H_

#define WRAP_ADMIN_CRUD(method, body)                          \
method                                                         \
try                                                            \
body                                                           \
catch (NotAuthenticatedAdminInfoManagerException &)            \
{                                                              \
    throw CALL_EX(NotAuthenticatedAdminModelException);        \
}                                                              \
catch (NotAuthorizedAdminInfoManagerException &)               \
{                                                              \
    throw CALL_EX(NotAuthorizedAdminModelException);           \
}                                                              \
catch (CommonCRUDAdminCommandException &er)                    \
{                                                              \
    throw CALL_EX_MSG(RedirectAdminModelException, er.what()); \
}

#endif

