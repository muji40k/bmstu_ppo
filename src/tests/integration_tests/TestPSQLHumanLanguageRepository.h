#ifndef _TESTPSQLHUMANLANGUAGEREPOSITORY_H_
#define _TESTPSQLHUMANLANGUAGEREPOSITORY_H_

#include <gtest/gtest.h>
#include "test_eq.h"

#include "typestring.h"
#include "date_common.h"

#include "QueryableFilterGeneric.h"

#include "setupPSQLTest.h"
#include "ValueCriteria.h"

struct TestPSQLHumanLanguageRepository : public testing::Test {
    PSQLTestContext context;
    std::shared_ptr<IHumanLanguageRepository> repo;
    HumanLanguage hl;
    Language language;

    void insertHumanLanguage(void)
    {
        pqxx::work w (*context.connection);
        w.exec_params("insert into language.general (language_id, name, family, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *language.id, *language.name, *language.family,
                      DateCommon::getTime(*language.validFrom));
        w.exec_params("insert into human.language (human_id, language_id, level, valid_from, source) "
                      "values ($1, $2, $3, $4, 'desktop')",
                      *hl.id, *language.id, "good",
                      DateCommon::getTime(*hl.validFrom));
        w.commit();
    }

    void SetUp()
    {
        std::time_t now = std::time(nullptr);
        context = setupPSQLRepositories();
        repo = context.repositories->getHumanLanguageRepository();
        pqxx::work w (*context.connection);

        pqxx::result r = w.exec("insert into entities.language (source) values ('desktop') returning id");
        language = Language(r[0][0].as<unsigned long long>(), "name", "family", now);

        r = w.exec("insert into entities.human (source) values ('desktop') returning id");
        hl = HumanLanguage(r[0][0].as<unsigned long long>(), {{language, "good"}}, now);
        w.commit();
    }
};

TEST_F(TestPSQLHumanLanguageRepository, create_test)
{
    ASSERT_NO_THROW(repo->create(hl));

    pqxx::nontransaction nt (*context.connection);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.language "
                        "where human_id = $1 "
                              "and language_id = $2 "
                              "and level = $3 "
                              "and valid_from = to_timestamp($4)",
                        *hl.id, *language.id, "good", *hl.validFrom);
    );
}

TEST_F(TestPSQLHumanLanguageRepository, update_test)
{
    insertHumanLanguage();
    HumanLanguage updated (hl);
    updated.setLevel(language, "excelent");

    ASSERT_NO_THROW(repo->update(updated));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.language "
                             "where human_id = $1 ", *updated.id);
    );

    ASSERT_EQ(res.size(), 2);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.language "
                        "where human_id = $1 "
                              "and language_id = $2 "
                              "and level = $3 "
                              "and valid_from = to_timestamp($4)",
                        *updated.id, *language.id, "excelent", *updated.validFrom);
    );
}

TEST_F(TestPSQLHumanLanguageRepository, erase_single_test)
{
    insertHumanLanguage();

    ASSERT_NO_THROW(repo->erase(hl));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.language "
                             "where human_id = $1 ", *hl.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.language "
                        "where deleted = true and human_id = $1 "
                              "and language_id = $2 "
                              "and level = $3 "
                              "and valid_from = to_timestamp($4)",
                        *hl.id, *language.id, "good", *hl.validFrom);
    );
}

TEST_F(TestPSQLHumanLanguageRepository, erase_strategy_test)
{
    insertHumanLanguage();

    ValueCriteria criteria (TypeName::getAttribute<HumanLanguage>("id"), "=", std::to_string(*hl.id));
    auto crepo = context.repositories->getHumanLanguageRepository();

    ASSERT_NO_THROW(crepo->erase(criteria));

    pqxx::nontransaction nt (*context.connection);
    pqxx::result res;

    ASSERT_NO_THROW
    (
        res = nt.exec_params("select * from human.language "
                             "where human_id = $1 ", *hl.id);
    );

    ASSERT_EQ(res.size(), 1);

    ASSERT_NO_THROW
    (
        nt.exec_params1("select * from human.language "
                        "where deleted = true and human_id = $1 "
                              "and language_id = $2 "
                              "and level = $3 "
                              "and valid_from = to_timestamp($4)",
                        *hl.id, *language.id, "good", *hl.validFrom);
    );
}

TEST_F(TestPSQLHumanLanguageRepository, get_test)
{
    insertHumanLanguage();
    std::shared_ptr<ITimeChangeableRepositorySet<HumanLanguage>> set = nullptr;;

    ASSERT_NO_THROW(set = repo->getAll());

    auto id_iter = set->begin(),
         id_end = set->end();

    ASSERT_NO_THROW(ASSERT_TRUE(id_end->notEqual(id_iter)));

    auto iter = set->beginId(id_iter),
         end = set->endId(id_iter);

    ASSERT_NO_THROW(ASSERT_TRUE(end->notEqual(iter)));

    const HumanLanguage hlc = iter->get();

    ASSERT_EQ(*hl.id, *hlc.id);
    std::list<Language> languages = hlc.get(AllFilter<Language>());
    ASSERT_EQ(languages.size(), 1);
    ASSERT_TRUE(test_eq(language, languages.front()));
    ASSERT_EQ(hlc.getLevel(languages.front()), "good");

    iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(end->notEqual(iter)));
    id_iter->next();
    ASSERT_NO_THROW(ASSERT_FALSE(id_end->notEqual(id_iter)));
}

#endif

