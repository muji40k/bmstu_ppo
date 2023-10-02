#include "PSQLMergeRequestRepository.h"

#include "typestring.h"

#include "PSQLCriteriaInterpreter.h"
#include "PSQLGenericIterator.h"

#include "ValueCriteria.h"

namespace PSQLMergeRequest
{
    class IteratorWrap : public IRepositoryIterator<MergeRequest>
    {
        public:
            IteratorWrap(std::shared_ptr<IRepositoryIterator<MergeRequest>> iter,
                         std::shared_ptr<IUserRepository> urepo,
                         std::shared_ptr<IHumanRepository> hrepo)
                : iter(iter), urepo(urepo), hrepo(hrepo)
            {
                if (nullptr == iter || nullptr == urepo || nullptr == hrepo)
                    throw CALL_EX(InitializationRepositoryIteratorException);
            }

            virtual ~IteratorWrap(void) override = default;

            virtual MergeRequest get(void) override
            {
                MergeRequest out = this->iter->get();

                ValueCriteria id_hcriteria (TypeName::getAttribute<Human>("id"), "=", std::to_string(out.human->id));
                auto hset = this->hrepo->get(id_hcriteria);

                auto id_hiter = hset->begin(),
                     id_hend  = hset->end();

                if (!id_hend->notEqual(id_hiter))
                    throw CALL_EX(CommonRepositorySetException);

                out.human = hset->beginId(id_hiter)->get();

                ValueCriteria id_ucriteria (TypeName::getAttribute<User>("id"), "=", std::to_string(out.user->id));
                auto uset = this->urepo->get(id_ucriteria);

                auto uiter = uset->begin(),
                     uend  = uset->end();

                if (!uend->notEqual(uiter))
                    throw CALL_EX(CommonRepositorySetException);

                out.user = uiter->get();

                return out;
            }

            virtual void next() override
            {
                this->iter->next();
            }

            virtual bool notEqual(std::shared_ptr<IRepositoryIterator<MergeRequest>> iter) override
            {
                std::shared_ptr<IteratorWrap> citer = std::dynamic_pointer_cast<IteratorWrap>(iter);

                if (nullptr == citer)
                    throw CALL_EX(IncompatibleRepositoryIteratorException);

                return this->iter->notEqual(citer->iter);
            }

        private:
            std::shared_ptr<IRepositoryIterator<MergeRequest>> iter;
            std::shared_ptr<IUserRepository> urepo;
            std::shared_ptr<IHumanRepository> hrepo;
    };

    class SetWrap : public IRepositorySet<MergeRequest>
    {
        public:
            SetWrap(std::shared_ptr<IRepositorySet<MergeRequest>> set,
                    std::shared_ptr<IUserRepository> urepo,
                    std::shared_ptr<IHumanRepository> hrepo)
                : set(set), urepo(urepo), hrepo(hrepo)
            {
                if (nullptr == set || nullptr == urepo || nullptr == hrepo)
                    throw CALL_EX(InitializationRepositoryIteratorException);
            }

            virtual ~SetWrap(void) override = default;

            virtual std::shared_ptr<IRepositoryIterator<MergeRequest>> begin(void) override
            try
            {
                return std::make_shared<IteratorWrap>(this->set->begin(),
                                                      this->urepo,
                                                      this->hrepo);
            }
            catch (std::bad_alloc &)
            {
                throw CALL_EX(AllocationRepositorySetException);
            }

            virtual std::shared_ptr<IRepositoryIterator<MergeRequest>> end(void) override
            try
            {
                return std::make_shared<IteratorWrap>(this->set->end(),
                                                      this->urepo,
                                                      this->hrepo);
            }
            catch (std::bad_alloc &)
            {
                throw CALL_EX(AllocationRepositorySetException);
            }

        private:
            std::shared_ptr<IRepositorySet<MergeRequest>> set;
            std::shared_ptr<IUserRepository> urepo;
            std::shared_ptr<IHumanRepository> hrepo;
    };
}

PSQLMergeRequestRepository::PSQLMergeRequestRepository(std::shared_ptr<pqxx::connection> connection,
                                                       std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                                       std::shared_ptr<IUserRepository> urepo,
                                                       std::shared_ptr<IHumanRepository> hrepo)
    : connection(connection), builder(builder), urepo(urepo), hrepo(hrepo)
{
    if (nullptr == connection || nullptr == builder || nullptr == urepo || nullptr == hrepo)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLMergeRequestRepository::create(const MergeRequest &item)
try
{
    static const std::string query =
    "insert into "
    "authentication.merge_requests (user_id, human_id, state) "
    "values                        ($1,      $2,       $3)";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.user->id, *item.human->id, *item.state);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLMergeRequestRepository::update(const MergeRequest &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectUpdateRepositoryException);

    static const std::string query =
    "update authentication.merge_requests "
    "set user_id = $2, human_id = $3, state = $4 "
    "where id = $1";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.user->id, *item.human->id, *item.state);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLMergeRequestRepository::erase(const MergeRequest &item)
try
{
    if (0 == item.id)
        throw CALL_EX(NoObjectEraseRepositoryException);

    static const std::string query =
    "delete from authentication.merge_requests "
    "where id = $1 and user_id = $2 and human_id = $3 and state = $4";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, *item.user->id, *item.human->id, *item.state);
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLMergeRequestRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "delete from authentication.merge_requests where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::work work (*this->connection);
    work.exec_params(query + interpreter->result());
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaWriteRepositoryException, er.what());
}

std::shared_ptr<IRepositorySet<MergeRequest>> PSQLMergeRequestRepository::get(const ICriteria &criteria)
try
{
    static const std::string query =
    "select * from authentication.merge_requests where ";

    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query + interpreter->result());
    nt.commit();

    return std::make_shared<PSQLMergeRequest::SetWrap>(std::make_shared<PSQLGenericRepositorySet<MergeRequest>>(std::make_shared<pqxx::result>(result)),
                                                       this->urepo,
                                                       this->hrepo);
}
catch (std::bad_alloc &er)
{
    throw CALL_EX(AllocationReadRepositoryException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaReadRepositoryException, er.what());
}

std::shared_ptr<IRepositorySet<MergeRequest>> PSQLMergeRequestRepository::getAll(void)
try
{
    static const std::string query = "select * from authentication.merge_requests";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result result = nt.exec_params(query);
    nt.commit();

    return std::make_shared<PSQLMergeRequest::SetWrap>(std::make_shared<PSQLGenericRepositorySet<MergeRequest>>(std::make_shared<pqxx::result>(result)),
                                                       this->urepo,
                                                       this->hrepo);
}
catch (std::bad_alloc &er)
{
    throw CALL_EX(AllocationReadRepositoryException);
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonReadRepositoryException, er.what());
}

template <>
MergeRequest PSQLGenericRepositoryIterator<MergeRequest>::get(void)
try
{
    const pqxx::row &row = *this->iter;

    Human human;
    human.id = row["human_id"].as<unsigned long long>();

    User user;
    user.id = row["user_id"].as<unsigned long long>();

    return MergeRequest (row["id"].as<unsigned long long>(),
                         user, human,
                         row["state"].as<std::string>());
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CommonRepositoryIteratorException, er.what());
}

