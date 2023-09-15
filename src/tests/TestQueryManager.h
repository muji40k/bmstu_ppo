#ifndef _TESTQUERYMANAGER_H_
#define _TESTQUERYMANAGER_H_

#include <gtest/gtest.h>
#include <cmath>

#include "typestring.h"

#include "setupMockTest.h"
#include "AppContext.h"
#include "StepCompositeAggregate.h"
#include "QueryManager.h"

#include "ValueCriteria.h"
#include "CountryPlaceLinker.h"

#include "SimpleQueryComposerAdapter.h"
#include "SimpleQueryAggregatorComposerAdapter.h"

#include "CountryPlaceLinker.h"

#include "CompositeAggregator.h"
#include "CountAggregator.h"
#include "OrderAggregator.h"
#include "SumAggregator.h"

#include "order_functions.h"

static void createPlaces(AppContext &context);

struct QueryManagerTest : public testing::Test {
    std::shared_ptr<AppContext> context = setupRepositories();
    bool init = false;

    void SetUp()
    {
        if (!init)
        {
            createPlaces(*context);
            init = true;
        }
    }
    void TearDown() {}
};

TEST_F(QueryManagerTest, basic_query)
{
    std::list<std::shared_ptr<QueryComposer>> qcomposers;
    qcomposers.push_back(std::make_shared<QueryComposer>());
    QueryComposer &country_composer = *qcomposers.back();
    qcomposers.push_back(std::make_shared<QueryComposer>());
    QueryComposer &place_composer = *qcomposers.back();
    country_composer.add(std::make_shared<SimpleQueryComposerAdapter<Country, ICountryRepository>>(&RepositoryContext::getCountryRepository));
    place_composer.add(std::make_shared<SimpleQueryComposerAdapter<Place, IPlaceRepository>>(&RepositoryContext::getPlaceRepository));
    place_composer.add(std::make_shared<SimpleQueryComposerAdapter<PlaceCountry, IPlaceCountryRepository>>(&RepositoryContext::getPlaceCountryRepository));

    CriteriaBank bank;
    bank.set(TypeName::get<Country>(),
             std::make_shared<ValueCriteria>(TypeName::getAttribute<Country>("type"), "=", "monarchy"));
    bank.set(TypeName::get<Place>(),
             std::make_shared<ValueCriteria>(TypeName::getAttribute<Place>("type"), "=", "city"));
    bank.set(TypeName::get<PlaceCountry>(), nullptr);

    std::list<std::shared_ptr<StepCompositeAggregate::Linker>> linkers = {std::make_shared<CountryPlaceLinker>()};

    OrderAggregator<Place, double> min_aggregator (&Place::getArea, lt<double>);
    SumAggregator<Place, double> sum_aggregator (&Place::getArea);
    CountAggregator<Place> count_aggregator;
    CompositeAggregator<Place> composite;

    composite.addAggregator(min_aggregator);
    composite.addAggregator(sum_aggregator);
    composite.addAggregator(count_aggregator);

    std::list<std::shared_ptr<AggregatorComposer::AggregatorItem>> aggregators =
    {
        std::make_shared<SimpleQueryAggregatorComposerAdapter<Place, IPlaceRepository>>(&RepositoryContext::getPlaceRepository, composite)
    };

    StepCompositeAggregate strategy(qcomposers, linkers, aggregators, bank);

    auto manager = context->getQueryManager();
    ASSERT_NO_THROW(manager->find(strategy));
    ASSERT_EQ(count_aggregator.result(), 3);
    ASSERT_TRUE(1e-8 > fabs(3941.4415406752605 - sum_aggregator.result()));
    ASSERT_TRUE(1e-8 > fabs(961.2722225279686 - min_aggregator.result()));
}

static void createPlaces(AppContext &context)
{
    auto crepo = context.getRepositoryContext().getCountryRepository();
    auto prepo = context.getRepositoryContext().getPlaceRepository();
    auto pcrepo = context.getRepositoryContext().getPlaceCountryRepository();

    crepo->create(Country(1, "republic", "Sudan", 207700000000.0, 0));
    prepo->create(Place(1, "village", "Place1", 83.93076786596524, "Africa", 0));
    pcrepo->create(PlaceCountry(1, Country(1, "republic", "Sudan", 207700000000.0, 0), 0));
    prepo->create(Place(2, "city", "Place2", 1303.692523206821, "Africa", 0));
    pcrepo->create(PlaceCountry(2, Country(1, "republic", "Sudan", 207700000000.0, 0), 0));
    prepo->create(Place(3, "village", "Place3", 89.82839310311518, "Africa", 0));
    pcrepo->create(PlaceCountry(3, Country(1, "republic", "Sudan", 207700000000.0, 0), 0));
    crepo->create(Country(2, "republic", "Libya", 168371000000.0, 0));
    prepo->create(Place(4, "city", "Place4", 620.4347249442762, "Africa", 0));
    pcrepo->create(PlaceCountry(4, Country(2, "republic", "Libya", 168371000000.0, 0), 0));
    prepo->create(Place(5, "city", "Place5", 1343.7602226450367, "Africa", 0));
    pcrepo->create(PlaceCountry(5, Country(2, "republic", "Libya", 168371000000.0, 0), 0));
    prepo->create(Place(6, "locality", "Place6", 110.05677801339431, "Africa", 0));
    pcrepo->create(PlaceCountry(6, Country(2, "republic", "Libya", 168371000000.0, 0), 0));
    crepo->create(Country(3, "republic", "DR Congo", 128000000000.0, 0));
    prepo->create(Place(7, "village", "Place7", 97.17067136469514, "Africa", 0));
    pcrepo->create(PlaceCountry(7, Country(3, "republic", "DR Congo", 128000000000.0, 0), 0));
    prepo->create(Place(8, "city", "Place8", 1410.9676115639152, "Africa", 0));
    pcrepo->create(PlaceCountry(8, Country(3, "republic", "DR Congo", 128000000000.0, 0), 0));
    prepo->create(Place(9, "village", "Place9", 16.70097448296046, "Africa", 0));
    pcrepo->create(PlaceCountry(9, Country(3, "republic", "DR Congo", 128000000000.0, 0), 0));
    crepo->create(Country(4, "monarchy", "Canada", 2385000000000.0, 0));
    prepo->create(Place(10, "locality", "Place10", 300.1164420160583, "North America", 0));
    pcrepo->create(PlaceCountry(10, Country(4, "monarchy", "Canada", 2385000000000.0, 0), 0));
    prepo->create(Place(11, "city", "Place11", 961.2722225279686, "North America", 0));
    pcrepo->create(PlaceCountry(11, Country(4, "monarchy", "Canada", 2385000000000.0, 0), 0));
    prepo->create(Place(12, "locality", "Place12", 381.6055216473435, "North America", 0));
    pcrepo->create(PlaceCountry(12, Country(4, "monarchy", "Canada", 2385000000000.0, 0), 0));
    crepo->create(Country(5, "republic", "USA", 26855000000000.0, 0));
    prepo->create(Place(13, "locality", "Place13", 356.7303940200981, "North America", 0));
    pcrepo->create(PlaceCountry(13, Country(5, "republic", "USA", 26855000000000.0, 0), 0));
    prepo->create(Place(14, "city", "Place14", 934.0403198404487, "North America", 0));
    pcrepo->create(PlaceCountry(14, Country(5, "republic", "USA", 26855000000000.0, 0), 0));
    prepo->create(Place(15, "village", "Place15", 91.7411237851171, "North America", 0));
    pcrepo->create(PlaceCountry(15, Country(5, "republic", "USA", 26855000000000.0, 0), 0));
    crepo->create(Country(6, "republic", "Mexico", 2920000000000.0, 0));
    prepo->create(Place(16, "city", "Place16", 965.6211629907154, "North America", 0));
    pcrepo->create(PlaceCountry(16, Country(6, "republic", "Mexico", 2920000000000.0, 0), 0));
    prepo->create(Place(17, "city", "Place17", 1264.1889344390374, "North America", 0));
    pcrepo->create(PlaceCountry(17, Country(6, "republic", "Mexico", 2920000000000.0, 0), 0));
    prepo->create(Place(18, "city", "Place18", 1375.1003938617127, "North America", 0));
    pcrepo->create(PlaceCountry(18, Country(6, "republic", "Mexico", 2920000000000.0, 0), 0));
    crepo->create(Country(7, "republic", "Argentina", 1274000000000.0, 0));
    prepo->create(Place(19, "locality", "Place19", 406.43348501126195, "South America", 0));
    pcrepo->create(PlaceCountry(19, Country(7, "republic", "Argentina", 1274000000000.0, 0), 0));
    prepo->create(Place(20, "city", "Place20", 1176.0494807584087, "South America", 0));
    pcrepo->create(PlaceCountry(20, Country(7, "republic", "Argentina", 1274000000000.0, 0), 0));
    prepo->create(Place(21, "locality", "Place21", 134.1950553191428, "South America", 0));
    pcrepo->create(PlaceCountry(21, Country(7, "republic", "Argentina", 1274000000000.0, 0), 0));
    crepo->create(Country(8, "republic", "Brazil", 4020000000000.0, 0));
    prepo->create(Place(22, "village", "Place22", 11.017328994743792, "South America", 0));
    pcrepo->create(PlaceCountry(22, Country(8, "republic", "Brazil", 4020000000000.0, 0), 0));
    prepo->create(Place(23, "village", "Place23", 66.26675756710631, "South America", 0));
    pcrepo->create(PlaceCountry(23, Country(8, "republic", "Brazil", 4020000000000.0, 0), 0));
    prepo->create(Place(24, "city", "Place24", 1263.8026765886007, "South America", 0));
    pcrepo->create(PlaceCountry(24, Country(8, "republic", "Brazil", 4020000000000.0, 0), 0));
    crepo->create(Country(9, "republic", "Russia", 4771000000000.0, 0));
    prepo->create(Place(25, "city", "Place25", 1001.7342998464535, "Eurasia", 0));
    pcrepo->create(PlaceCountry(25, Country(9, "republic", "Russia", 4771000000000.0, 0), 0));
    prepo->create(Place(26, "locality", "Place26", 322.78558499379096, "Eurasia", 0));
    pcrepo->create(PlaceCountry(26, Country(9, "republic", "Russia", 4771000000000.0, 0), 0));
    prepo->create(Place(27, "locality", "Place27", 245.695351691026, "Eurasia", 0));
    pcrepo->create(PlaceCountry(27, Country(9, "republic", "Russia", 4771000000000.0, 0), 0));
    crepo->create(Country(10, "republic", "China", 33015000000000.0, 0));
    prepo->create(Place(28, "locality", "Place28", 332.49045414665136, "Eurasia", 0));
    pcrepo->create(PlaceCountry(28, Country(10, "republic", "China", 33015000000000.0, 0), 0));
    prepo->create(Place(29, "locality", "Place29", 318.1695222623893, "Eurasia", 0));
    pcrepo->create(PlaceCountry(29, Country(10, "republic", "China", 33015000000000.0, 0), 0));
    prepo->create(Place(30, "village", "Place30", 27.27505528635935, "Eurasia", 0));
    pcrepo->create(PlaceCountry(30, Country(10, "republic", "China", 33015000000000.0, 0), 0));
    crepo->create(Country(11, "republic", "India", 3737000000000.0, 0));
    prepo->create(Place(31, "city", "Place31", 1313.0520416442318, "Eurasia", 0));
    pcrepo->create(PlaceCountry(31, Country(11, "republic", "India", 3737000000000.0, 0), 0));
    prepo->create(Place(32, "city", "Place32", 1393.6644034127307, "Eurasia", 0));
    pcrepo->create(PlaceCountry(32, Country(11, "republic", "India", 3737000000000.0, 0), 0));
    prepo->create(Place(33, "village", "Place33", 47.310253981532924, "Eurasia", 0));
    pcrepo->create(PlaceCountry(33, Country(11, "republic", "India", 3737000000000.0, 0), 0));
    crepo->create(Country(12, "monarchy", "Australia", 1718000000000.0, 0));
    prepo->create(Place(34, "village", "Place34", 36.64938800950183, "Australia", 0));
    pcrepo->create(PlaceCountry(34, Country(12, "monarchy", "Australia", 1718000000000.0, 0), 0));
    prepo->create(Place(35, "city", "Place35", 1498.8299728089714, "Australia", 0));
    pcrepo->create(PlaceCountry(35, Country(12, "monarchy", "Australia", 1718000000000.0, 0), 0));
    prepo->create(Place(36, "city", "Place36", 1481.3393453383205, "Australia", 0));
    pcrepo->create(PlaceCountry(36, Country(12, "monarchy", "Australia", 1718000000000.0, 0), 0));
}

#endif

