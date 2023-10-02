#ifndef _TESTPSQLLANGUAGEREPOSITORY_H_
#define _TESTPSQLLANGUAGEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLLanguageRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<ILanguageRepository> repo;
    Language language;

    void insertLanguage(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into language.general (language_id, name, family, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *language.id, *language.name, *language.family,
                      DateCommon::getTime(*language.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getLanguageRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.language (source) values ('desktop') returning id");
        language = Language(r[0][0].as<unsigned long long>(), "name", "family", now);
        w.commit();
    }
};

TEST_F(TestPSQLLanguageRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(language));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from language.general "
                        "where language_id = $1 "
                              "and name = $2 "
                              "and family = $3 "
                              "and valid_from = $4",
                        *language.id, *language.name, *language.family,
                        DateCommon::getTime(*language.validFrom));
    );
}

TEST_F(TestPSQLLanguageRepository, update_test)
{
    insertLanguage();

    Language updated (language.id, "new", "new", std::time(nullptr));

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from language.general "
                             "where language_id = $1 ", *language.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from language.general "
                        "where language_id = $1 "
                              "and name = $2 "
                              "and family = $3 "
                              "and valid_from = $4",
                        *updated.id, *updated.name, *updated.family,
                        DateCommon::getTime(*updated.validFrom));
    );
}

TEST_F(TestPSQLLanguageRepository, erase_single_test)
{
    insertLanguage();

    ASSERT_NO_THROW(repo->erase(language));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from language.general "
                             "where language_id = $1 ", *language.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from language.general "
                        "where deleted = true "
                              "and language_id = $1 "
                              "and name = $2 "
                              "and family = $3 "
                              "and valid_from = $4",
                        *language.id, *language.name, *language.family,
                        DateCommon::getTime(*language.validFrom));
    );
}

TEST_F(TestPSQLLanguageRepository, erase_strategy_test)
{
    insertLanguage();

    ValueCriteria criteria (TypeName::getAttribute<Language>("id"), "=", std::to_string(*language.id));
    auto crepo = context.repositories->getLanguageRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from language.general "
                             "where language_id = $1 ", *language.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from language.general "
                        "where deleted = true "
                              "and language_id = $1 "
                              "and name = $2 "
                              "and family = $3 "
                              "and valid_from = $4",
                        *language.id, *language.name, *language.family,
                        DateCommon::getTime(*language.validFrom));
    );
}

TEST_F(TestPSQLLanguageRepository, get_test)
{
    insertLanguage();
    std::shared_ptr<ITimeChangeableRepositorySet<Language>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    ASSERT_TRUE(test_eq(language, iter->get()));
    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

