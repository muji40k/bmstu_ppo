#ifndef _GENERICUICRITERIAPARSER_H_
#define _GENERICUICRITERIAPARSER_H_

#include <memory>

#include "IAdminModel.h"
#include "ICriteriaBuilder.h"

template <typename Type>
static std::shared_ptr<ICriteriaBuilder> buildCriteria(const std::list<IAdminModel::CriteriaMap> &list);

#include "GenericUiCriteriaParser.hpp"

#endif

