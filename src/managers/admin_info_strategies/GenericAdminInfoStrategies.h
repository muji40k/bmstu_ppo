#ifndef _GENERICADMININFOSTRATEGIES_H_
#define _GENERICADMININFOSTRATEGIES_H_

#define ADD_STRATEGY(type)                                                                                       \
class type##CreateAdminInfoStrategy : public CreateAdminInfoStrategy                                             \
{                                                                                                                \
    public:                                                                                                      \
        type##CreateAdminInfoStrategy(const type &value);                                                        \
        virtual ~type##CreateAdminInfoStrategy(void) override = default;                                         \
        virtual void apply(AppContext &context) override;                                                        \
                                                                                                                 \
    private:                                                                                                     \
        type value;                                                                                              \
};                                                                                                               \
                                                                                                                 \
class type##GetAdminInfoStrategy : public GetAdminInfoStrategy,                                                  \
                                   public GetStrategyResult<std::shared_ptr<ITimeChangeableRepositorySet<type>>> \
{                                                                                                                \
    public:                                                                                                      \
        type##GetAdminInfoStrategy(void) = default;                                                              \
        type##GetAdminInfoStrategy(const ICriteria &criteria);                                                   \
        virtual ~type##GetAdminInfoStrategy(void) override = default;                                            \
        virtual void apply(AppContext &context) override;                                                        \
        virtual std::shared_ptr<ITimeChangeableRepositorySet<type>> result(void) override;                       \
                                                                                                                 \
    private:                                                                                                     \
        const ICriteria *criteria = nullptr;                                                                     \
        std::shared_ptr<ITimeChangeableRepositorySet<type>> res = nullptr;                                       \
};                                                                                                               \
                                                                                                                 \
class type##UpdateAdminInfoStrategy : public UpdateAdminInfoStrategy                                             \
{                                                                                                                \
    public:                                                                                                      \
        type##UpdateAdminInfoStrategy(const type &value);                                                        \
        virtual ~type##UpdateAdminInfoStrategy(void) override = default;                                         \
        virtual void apply(AppContext &context) override;                                                        \
                                                                                                                 \
    private:                                                                                                     \
        type value;                                                                                              \
};                                                                                                               \
                                                                                                                 \
class type##EraseAdminInfoStrategy : public EraseAdminInfoStrategy                                               \
{                                                                                                                \
    public:                                                                                                      \
        type##EraseAdminInfoStrategy(const ICriteria &criteria);                                                 \
        virtual ~type##EraseAdminInfoStrategy(void) override = default;                                          \
        virtual void apply(AppContext &context) override;                                                        \
                                                                                                                 \
    private:                                                                                                     \
        const ICriteria &criteria;                                                                               \
};                                                                                                               \
                                                                                                                 \
class type##EraseSingleAdminInfoStrategy : public EraseAdminInfoStrategy                                         \
{                                                                                                                \
    public:                                                                                                      \
        type##EraseSingleAdminInfoStrategy(const type &value);                                                   \
        virtual ~type##EraseSingleAdminInfoStrategy(void) override = default;                                    \
        virtual void apply(AppContext &context) override;                                                        \
                                                                                                                 \
    private:                                                                                                     \
        type value;                                                                                              \
}

#endif

