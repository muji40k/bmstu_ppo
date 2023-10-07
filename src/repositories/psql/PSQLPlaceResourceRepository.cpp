#include "PSQLPlaceResourceRepository.h"

#include <utility>

#include "typestring.h"

#include "PSQLGenericTimeChangeableIterator.h"
#include "PSQLCriteriaInterpreter.h"
#include "ValueCriteria.h"
#include "LogicCriteriaBuilder.h"

#include "QueryableFilterGeneric.h"

#include "date_common.h"

namespace PSQLPlaceResource
{
    class IteratorWrap : public ITimeChangeableRepositoryIterator<PlaceResource>
    {
        public:
            IteratorWrap(std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> iter,
                         std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> end,
                         std::shared_ptr<IResourceRepository> rrepo)
                : iter(iter), end(end), rrepo(rrepo)
            {
                if (nullptr == iter || nullptr == end || nullptr == rrepo)
                    throw CALL_EX(InitializaionTimeChangeableRepositoryIteratorException);
            }

            virtual ~IteratorWrap(void) override = default;

            virtual PlaceResource get(void) override
            {
                static const AllFilter<Resource> filter;

                if (this->adjusted)
                    return this->cache;

                this->adjusted = true;
                PlaceResource out = this->iter->get();
                this->iter->next();

                Resource r = out.get(filter).front();
                std::unordered_map<unsigned long long, double> volumes = {{*r.id, out.getVolume(r)}};
                LogicCriteriaBuilder builder (std::make_shared<ValueCriteria>(TypeName::getAttribute<Resource>("validFrom"), "<=", std::to_string(out.validFrom)));
                builder.addAND(std::make_shared<ValueCriteria>(TypeName::getAttribute<Resource>("id"), "=", std::to_string(*r.id)));

                for (bool current = true; current && this->end->notEqual(this->iter);)
                {
                    PlaceResource c = this->iter->get();

                    if (c.validFrom != out.validFrom)
                        current = false;
                    else
                    {
                        Resource r = c.get(filter).front();
                        volumes.emplace(std::make_pair(*r.id, c.getVolume(r)));
                        builder.addOR(std::make_shared<ValueCriteria>(TypeName::getAttribute<Resource>("id"), "=", std::to_string(*r.id)));
                        this->iter->next();
                    }
                }

                auto set = this->rrepo->get(*builder.get());
                out.del(filter);

                for (auto id_iter = set->begin(), id_end  = set->end();
                     id_end->notEqual(id_iter);
                     id_iter->next())
                {
                    r = set->beginId(id_iter)->get();
                    out.add(r);
                    out.setVolume(r, volumes[r.id]);
                }

                return this->cache = out;
            }

            virtual void next() override
            {
                if (!this->adjusted)
                    this->iter->next();

                this->adjusted = false;
            }

            virtual bool notEqual(std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> iter) override
            {
                std::shared_ptr<IteratorWrap> citer = std::dynamic_pointer_cast<IteratorWrap>(iter);

                if (nullptr == citer)
                    throw CALL_EX(IncompatibleTimeChangeableRepositoryIteratorException);

                return this->iter->notEqual(citer->iter);
            }

        private:
            std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> iter;
            std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> end;
            std::shared_ptr<IResourceRepository> rrepo;
            bool adjusted = false;
            PlaceResource cache;
    };

    class SetWrap : public ITimeChangeableRepositorySet<PlaceResource>
    {
        public:
            SetWrap(std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> set,
                    std::shared_ptr<IResourceRepository> rrepo)
                : set(set), rrepo(rrepo)
            {
                if (nullptr == set || nullptr == rrepo)
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

            virtual std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> beginId(std::shared_ptr<IRepositoryIdIterator> iter) override
            {
                return std::make_shared<IteratorWrap>(this->set->beginId(iter), this->set->endId(iter), this->rrepo);
            }

            virtual std::shared_ptr<ITimeChangeableRepositoryIterator<PlaceResource>> endId(std::shared_ptr<IRepositoryIdIterator> iter) override
            {
                return std::make_shared<IteratorWrap>(this->set->endId(iter), this->set->endId(iter), this->rrepo);
            }

        private:
            std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> set;
            std::shared_ptr<IResourceRepository> rrepo;
    };
}

PSQLPlaceResourceRepository::PSQLPlaceResourceRepository(std::shared_ptr<pqxx::connection> connection,
                                                         std::shared_ptr<ICriteriaVisitorResultBuilder<std::string>> builder,
                                                         std::shared_ptr<IResourceRepository> rrepo)
    : connection(connection), builder(builder), rrepo(rrepo)
{
    if (nullptr == connection || nullptr == builder || nullptr == rrepo)
        throw CALL_EX(NullptrRepositoryException);
}

void PSQLPlaceResourceRepository::create(const PlaceResource &item)
try
{
    static const std::string query_entity =
    "insert into "
    "entities.place (source) "
    "values ('desktop') "
    "returning id";

    static const std::string query =
    "insert into "
    "place.resource (place_id, resource_id, volume, valid_from, source) "
    "values         ($1,       $2,         $3,     $4,         'desktop')";

    unsigned long long id = item.id;
    pqxx::work work (*this->connection);

    if (0 == id)
    {
        pqxx::row row = work.exec1(query_entity);
        id = row[0].as<unsigned long long>();
    }

    for (Resource r : item.get(AllFilter<Resource>()))
        work.exec_params(query, id, *r.id, item.getVolume(r),
                         DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(CreateRepositoryException, er.what());
}

void PSQLPlaceResourceRepository::update(const PlaceResource &item)
try
{
    if (0 == item.id)
        throw CALL_EX(UpdateRepositoryException);

    static const std::string query =
    "insert into "
    "place.resource (place_id, resource_id, volume, valid_from, source) "
    "values         ($1,       $2,         $3,     $4,         'desktop')";

    pqxx::work work (*this->connection);

    for (Resource r : item.get(AllFilter<Resource>()))
        work.exec_params(query, *item.id, *r.id, item.getVolume(r),
                         DateCommon::getTime(item.validFrom));

    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(UpdateRepositoryException, er.what());
}

void PSQLPlaceResourceRepository::erase(const PlaceResource &item)
try
{
    static const std::string query =
    "update place.resource "
    "set deleted = true "
    "where place_id = $1 and valid_from = $2";

    pqxx::work work (*this->connection);
    work.exec_params(query, *item.id, DateCommon::getTime(item.validFrom));
    work.commit();
}
catch (pqxx::sql_error &er)
{
    throw CALL_EX_MSG(EraseRepositoryException, er.what());
}

void PSQLPlaceResourceRepository::erase(const ICriteria &criteria)
try
{
    static const std::string query =
    "update place.resource "
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

std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> PSQLPlaceResourceRepository::get(const ICriteria &criteria)
try
{
    auto interpreter = this->builder->get();
    criteria.accept(*interpreter);

    return std::make_shared<PSQLPlaceResource::SetWrap>(std::make_shared<PSQLGenericTimeChangeableRepositorySet<PlaceResource>>(this->connection, interpreter->result()),
                                                        this->rrepo);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}
catch (CommonCriteriaVisitorException &er)
{
    throw CALL_EX_MSG(WrongCriteriaTimeChangeableRepositoryException, er.what());
}

std::shared_ptr<ITimeChangeableRepositorySet<PlaceResource>> PSQLPlaceResourceRepository::getAll(void)
try
{
    return std::make_shared<PSQLPlaceResource::SetWrap>(std::make_shared<PSQLGenericTimeChangeableRepositorySet<PlaceResource>>(this->connection),
                                                        this->rrepo);
}
catch (std::bad_alloc &)
{
    throw CALL_EX(AllocationTimeChangeableRepositorySetException);
}

template <>
PlaceResource PSQLGenericTimeChangeableRepositoryIterator<PlaceResource>::get(void)
{
    const pqxx::row &row = *this->iter;

    Resource resource;
    resource.id = row["resource_id"].as<unsigned long long>();

    return PlaceResource (row["place_id"].as<unsigned long long>(),
                          {{resource, row["volume"].as<double>()}},
                          DateCommon::parseTime(row["valid_from"].as<std::string>()));
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<PlaceResource>::makeIdResult(void)
{
    const std::string query =
    "select distinct place_id as id "
    "from place.resource "
    "where (deleted = false and " + this->query + ")";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec(query);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

template <>
std::shared_ptr<pqxx::result> PSQLGenericTimeChangeableRepositorySet<PlaceResource>::makeResult(unsigned long long id)
{
    const std::string query =
    "select * "
    "from (select *, max(modification_date) over (partition by resource_id, valid_from) "
           "from place.resource "
           "where deleted = false and place_id = $1 and " + this->query + ") as filtered "
    "where modification_date = max "
    "order by valid_from desc";

    pqxx::nontransaction nt (*this->connection);
    pqxx::result res = nt.exec_params(query, id);
    nt.commit();

    return std::make_shared<pqxx::result>(res);
}

