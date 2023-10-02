#ifndef _TESTPSQLCOUNTRYREPOSITORY_H_
#define _TESTPSQLCOUNTRYREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLCountryRepository : public testing::Test {
    PSQLTestContext context;
    Country country;

    void insertCountry(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into country.general (country_id, type, name, gdp, valid_from, source) "
                      "values ($1, $2, $3, $4, $5, 'desktop')",
                      *country.id, *country.type, *country.name, *country.gdp,
                      DateCommon::getTime(*country.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.country (source) values ('desktop') returning id");
        country = Country(r[0][0].as<unsigned long long>(), "type", "name", 123, now);
        w.commit();
    }
};

TEST_F(TestPSQLCountryRepository, create_test)
{
    auto crepo = context.repositories->getCountryRepository();

    ASSERT_NO_THROW(crepo->create(country));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from country.general "
                        "where country_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and gdp = $4 "
                              "and valid_from = $5",
                        *country.id, *country.type, *country.name, *country.gdp,
                        DateCommon::getTime(*country.validFrom));
    );
}

TEST_F(TestPSQLCountryRepository, update_test)
{
    insertCountry();

    Country updated (country.id, "new", "new", 789, std::time(nullptr));

    auto crepo = context.repositories->getCountryRepository();

    ASSERT_NO_THROW(crepo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from country.general "
                             "where country_id = $1 ", *country.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from country.general "
                        "where country_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and gdp = $4 "
                              "and valid_from = $5",
                        *updated.id, *updated.type, *updated.name, *updated.gdp,
                        DateCommon::getTime(*updated.validFrom));
    );
}

TEST_F(TestPSQLCountryRepository, erase_single_test)
{
    insertCountry();

    auto crepo = context.repositories->getCountryRepository();

    ASSERT_NO_THROW(crepo->erase(country));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from country.general "
                             "where country_id = $1 ", *country.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from country.general "
                        "where deleted = true "
                              "and country_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and gdp = $4 "
                              "and valid_from = $5",
                        *country.id, *country.type, *country.name, *country.gdp,
                        DateCommon::getTime(*country.validFrom));
    );

    ASSERT_EQ(res.size(), 1);
}

TEST_F(TestPSQLCountryRepository, erase_strategy_test)
{
    insertCountry();

    ValueCriteria criteria (TypeName::getAttribute<Country>("id"), "=", std::to_string(*country.id));
    auto crepo = context.repositories->getCountryRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from country.general "
                             "where country_id = $1 ", *country.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from country.general "
                        "where deleted = true "
                              "and country_id = $1 "
                              "and type = $2 "
                              "and name = $3 "
                              "and gdp = $4 "
                              "and valid_from = $5",
                        *country.id, *country.type, *country.name, *country.gdp,
                        DateCommon::getTime(*country.validFrom));
    );
}

TEST_F(TestPSQLCountryRepository, get_test)
{
    insertCountry();

    auto crepo = context.repositories->getCountryRepository();
    std::shared_ptr<ITimeChangeableRepositorySet<Country>> set = nullptr;;

    ASSERT_NO_THROW(set = crepo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));
    
    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(country, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

