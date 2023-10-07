#ifndef _GENERICADMININFOSTRATEGIESIMPLEMENTATION_H_
#define _GENERICADMININFOSTRATEGIESIMPLEMENTATION_H_

#define ADD_STRATEGY_IMPL(type)                                                              \
type##CreateAdminInfoStrategy::type##CreateAdminInfoStrategy(const type &value)              \
    : value(value)                                                                           \
{}                                                                                           \
                                                                                             \
void type##CreateAdminInfoStrategy::apply(AppContext &context)                               \
{                                                                                            \
    auto repo = context.getRepositoryContext().get##type##Repository();                      \
    repo->create(this->value);                                                               \
}                                                                                            \
                                                                                             \
type##GetAdminInfoStrategy::type##GetAdminInfoStrategy(const ICriteria &criteria)            \
    : criteria(&criteria)                                                                    \
{}                                                                                           \
                                                                                             \
void type##GetAdminInfoStrategy::apply(AppContext &context)                                  \
{                                                                                            \
    auto repo = context.getRepositoryContext().get##type##Repository();                      \
                                                                                             \
    if (this->criteria)                                                                      \
        this->res = repo->get(*this->criteria);                                              \
    else                                                                                     \
        this->res = repo->getAll();                                                          \
}                                                                                            \
                                                                                             \
std::shared_ptr<ITimeChangeableRepositorySet<type>> type##GetAdminInfoStrategy::result(void) \
{                                                                                            \
    return this->res;                                                                        \
}                                                                                            \
                                                                                             \
type##UpdateAdminInfoStrategy::type##UpdateAdminInfoStrategy(const type &value)              \
    : value(value)                                                                           \
{}                                                                                           \
                                                                                             \
void type##UpdateAdminInfoStrategy::apply(AppContext &context)                               \
{                                                                                            \
    auto repo = context.getRepositoryContext().get##type##Repository();                      \
    repo->update(this->value);                                                               \
}                                                                                            \
                                                                                             \
type##EraseAdminInfoStrategy::type##EraseAdminInfoStrategy(const ICriteria &criteria)        \
    : criteria(criteria)                                                                     \
{}                                                                                           \
                                                                                             \
void type##EraseAdminInfoStrategy::apply(AppContext &context)                                \
{                                                                                            \
    auto repo = context.getRepositoryContext().get##type##Repository();                      \
    repo->erase(this->criteria);                                                             \
}                                                                                            \
                                                                                             \
type##EraseSingleAdminInfoStrategy::type##EraseSingleAdminInfoStrategy(const type &value)    \
    : value(value)                                                                           \
{}                                                                                           \
                                                                                             \
void type##EraseSingleAdminInfoStrategy::apply(AppContext &context)                          \
{                                                                                            \
    auto repo = context.getRepositoryContext().get##type##Repository();                      \
    repo->erase(this->value);                                                                \
}

#endif

