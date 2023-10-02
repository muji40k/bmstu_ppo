#include "PSQLHumanLanguageRepository.h"

#include <utility>

#include "typestring.h"

#include "PSQLGenericTimeChangeableIterator.h"
#include "PSQLCriteriaInterpreter.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

#include "QueryableFilterGeneric.h"

#include "date_common.h"

namespace PSQLHumanLanguage
{
    class IteratorWrap : public ITimeChangeableRepositoryIterator<HumanLanguage>
    {
        public:
            IteratorWrap(std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> iter,
                         std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> end,
                         std::shared_ptr<ILanguageRepository> lrepo)
                : iter(iter), end(end), lrepo(lrepo)
            {
                if (nullptr == iter || nullptr == end || nullptr == lrepo)
                    throw CALL_EX(InitializaionTimeChangeableRepositoryIteratorException);
            }

            virtual ~IteratorWrap(void) override = default;

            virtual HumanLanguage get(void) override
            {
                static const AllFilter<Language> filter;

                if (this->adjusted)
                    return this->cache;

                this->adjusted = true;
                HumanLanguage out = this->iter->get();
                this->iter->next();

                Language l = out.get(filter).front();
                std::unordered_map<unsigned long long, std::string> levels = {{*l.id, out.getLevel(l)}};
                LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<Language>("validFrom"), "<=", std::to_string(out.validFrom)));
                builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<Language>("id"), "=", std::to_string(*l.id)));

                for (bool current = true; current && this->end->notEqual(this->iter);)
                {
                    HumanLanguage c = this->iter->get();

                    if (c.validFrom != out.validFrom)
                        current = false;
                    else
                    {
                        Language l = c.get(filter).front();
                        levels.emplace(std::make_pair(*l.id, c.getLevel(l)));
                        builder.addOR(std::make_shared<ValueCriteria>(TypeName::getAttribute<Language>("id"), "=", std::to_string(*l.id)));
                        this->iter->next();
                    }
                }

                auto set = this->lrepo->get(*builder.get());
                out.del(filter);

                for (auto id_iter = set->begin(), id_end  = set->end();
                     id_end->notEqual(id_iter);
                     id_iter->next())
                {
                    l = set->beginId(id_iter)->get();
                    out.add(set->beginId(id_iter)->get());
                    out.setLevel(l, levels[l.id]);
                }

                return this->cache = out;
            }

            virtual void next() override
            {
                if (!this->adjusted)
                    this->iter->next();

                this->adjusted = false;
            }

            virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> iter) override
            {
                std::shared_ptr<IteratorWrap> citer = std::dynamic_pointer_cast<IteratorWrap>(iter);

                if (nullptr == citer)
                    throw CALL_EX(IncompatibleTimeChangeableRepositoryIteratorException);

                return this->iter->notEqual(citer->iter);
            }

        private:
            std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> iter;
            std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> end;
            std::shared_ptr<ILanguageRepository> lrepo;
            bool adjusted = false;
            HumanLanguage cache;
    };

    class SetWrap : public ITimeChangeableRepositorySet<HumanLanguage>
    {
        public:
            SetWrap(std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> set,
                    std::shared_ptr<ILanguageRepository> lrepo)
                : set(set), lrepo(lrepo)
            {
                if (nullptr == set || nullptr == lrepo)
                    throw CALL_EX(InitializaionTimeChangeableRepositorySetException);
            }

            virtual ~SetWrap(void) override = default;

            virtual std::shared_ptr<IRepositoryIdIterator> begin(void) override
            {
                return this->set->begin();
            }

            virtual std::shared_ptr<IRepositoryIdIterator> end(void) override
            {
                return this->set->end();
            }

            virtual std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> beginId(std::shared_ptr<IRepositoryIdIterator> iter) override
            {
                return std::make_shared<IteratorWrap>(this->set->beginId(iter), this->set->endId(iter), this->lrepo);
            }

            virtual std::shared_ptr<ITimeChangeableRepositoryIterator<HumanLanguage>> endId(std::shared_ptr<IRepositoryIdIterator> iter) override
            {
                return std::make_shared<IteratorWrap>(this->set->endId(iter), this->set->endId(iter), this->lrepo);
            }

        private:
            std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> set;
            std::shared_ptr<ILanguageRepository> lrepo;
    };
}

PSQLHumanLanguageRepository::PSQLHumanLanguageRepository(std::shared_ptr<pqxx::connection> connection,
                                                         std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                                         std::shared_ptr<ILanguageRepository> lrepo)
    : connection(connection), builder(builder), lrepo(lrepo)
{
    if (nullptr == connection || nullptr == builder || nullptr == lrepo)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLHumanLanguageRepository::create(const HumanLanguage &item)
try
{
    static const std::string query_entity =
    "insert into "
    "entities.human (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query =
    "insert into "
    "human.language (human_id, language_id, level, valid_from, source) "
    "values         ($1,       $2,          $3,    $4,         'desktop')";

    unsigned long long id = item.id;
    pqxx::work work (*this->connection);

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    for (Language l : item.get(AllFilter<Language>()))
        work.exec_params(query, id, *l.id, item.getLevel(l),
                         DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLHumanLanguageRepository::update(const HumanLanguage &item)
try
{
    if (0 == item.id)
        throw CALL_EX(UpdateRepositoryException);

    static const std::string query =
    "insert into "
    "human.language (human_id, language_id, level, valid_from, source) "
    "values         ($1,       $2,          $3,    $4,         'desktop')";

    pqxx::work work (*this->connection);

    for (Language l : item.get(AllFilter<Language>()))
        work.exec_params(query, *item.id, *l.id, item.getLevel(l),
                         DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLHumanLanguageRepository::erase(const HumanLanguage &item)
try
{
    static const std::string query =
    "update human.language "
    "set deleted = true "
    "where human_id = $1 and valid_from = $2";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, DateCommon::getTime(item.validFrom));
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLHumanLanguageRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "update human.language "
    "set deleted = true "
    "where ";

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

std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> PSQLHumanLanguageRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLHumanLanguage::SetWrap>(std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanLanguage>>(this->connection, interpreter->result()),
                                                        this->lrepo);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> PSQLHumanLanguageRepository::getAll(void)
try
{
    return std::make_shared<PSQLHumanLanguage::SetWrap>(std::make_shared<PSQLGenericTimeChangeableRepositorySet<HumanLanguage>>(this->connection),
                                                        this->lrepo);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
HumanLanguage PSQLGenericTimeChangeableRepositoryIterator<HumanLanguage>::get(void)
{
    const pqxx::row &row = *this->iter;

    Language language;
    language.id = row["language_id"].as<unsigned long long>();

    return HumanLanguage (row["human_id"].as<unsigned long long>(),
                          {{language, row["level"].as<std::string>()}},
                          DateCommon::parseTime(row["valid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanLanguage>::makeIdResult(void)
{
    const std::string query =
    "select distinct human_id as id "
    "from human.language "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<HumanLanguage>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select *, max(modification_date) over (partition by language_id, valid_from) "
           "from human.language "
           "where deleted = false and human_id = $1 and " + this->query + ") as filtered "
    "where modification_date = max "
    "order by valid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

