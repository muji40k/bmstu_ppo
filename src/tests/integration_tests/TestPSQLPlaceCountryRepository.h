#ifndef _TESTPSQLPLACECOUNTRYREPOSITORY_H_
#define _TESTPSQLPLACECOUNTRYREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLPlaceCountryRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IPlaceCountryRepository> repo;
    PlaceCountry pc;

    void insertPlaceCountry(void)
    {
        pqxx::work w (*context.connection);
        const Country &country = pc.country;
        w.exec_params("insert into country.general (country_id, type, name, gdp, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, 'desktop')",
                      *country.id, *country.type, *country.name, *country.gdp,
                      DateCommon::getTime(*country.validFrom));
        w.exec_params("insert into place.country (place_id, country_id, valid_from, source) "
                      "values ($1, $2, $3, 'desktop')",
                      *pc.id, *country.id,
                      DateCommon::getTime(*pc.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getPlaceCountryRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.country (source) values ('desktop') returning id");
        Country country(r[0][0].as<unsigned long long>(), "type", "name", 123, now);

        r = w.exec("insert into entities.place (source) values ('desktop') returning id");
        pc = PlaceCountry(r[0][0].as<unsigned long long>(), country, now);
        w.commit();
    }
};

TEST_F(TestPSQLPlaceCountryRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(pc));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.country "
                        "where place_id = $1 "
                              "and country_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *pc.id, *pc.country->id, *pc.validFrom);
    );
}

TEST_F(TestPSQLPlaceCountryRepository, update_test)
{
    insertPlaceCountry();
    std::time_t now = std::time(nullptr);
    pqxx::work w (*context.connection);
    pqxx::result r = w.exec("insert into entities.country (source) values ('desktop') returning id");
    Country country(r[0][0].as<unsigned long long>(), "updated", "updated", 451, now);
    w.exec_params("insert into country.general (country_id, type, name, gdp, valid_from, source) "
                  "values ($1, $2, $3, $4, $5, 'desktop')",
                  *country.id, *country.type, *country.name, *country.gdp,
                  DateCommon::getTime(*country.validFrom));
    w.commit();
    PlaceCountry updated (pc.id, country, now);

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.country "
                             "where place_id = $1 ", *updated.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.country "
                        "where place_id = $1 "
                              "and country_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *updated.id, *updated.country->id, *updated.validFrom);
    );
}

TEST_F(TestPSQLPlaceCountryRepository, erase_single_test)
{
    insertPlaceCountry();

    ASSERT_NO_THROW(repo->erase(pc));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.country "
                             "where place_id = $1 ", *pc.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.country "
                        "where deleted = true and place_id = $1 "
                              "and country_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *pc.id, *pc.country->id, *pc.validFrom);
    );
}

TEST_F(TestPSQLPlaceCountryRepository, erase_strategy_test)
{
    insertPlaceCountry();

    ValueCriteria criteria (TypeName::getAttribute<PlaceCountry>("id"), "=", std::to_string(*pc.id));
    auto crepo = context.repositories->getPlaceCountryRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from place.country "
                             "where place_id = $1 ", *pc.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from place.country "
                        "where deleted = true and place_id = $1 "
                              "and country_id = $2 "
                              "and valid_from = to_timestamp($3)",
                        *pc.id, *pc.country->id, *pc.validFrom);
    );
}

TEST_F(TestPSQLPlaceCountryRepository, get_test)
{
    insertPlaceCountry();
    std::shared_ptr<ITimeChangeableRepositorySet<PlaceCountry>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(pc, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

