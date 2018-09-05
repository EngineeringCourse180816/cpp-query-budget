#include "gtest/gtest.h"
#include <string>
#include "StubClass.h"
#include "../main/BudgetQuery.h"
#include "../main/date.h"

using namespace std;
using namespace testing;
using namespace date;


namespace {

    TEST(BudgetQuery, original_test) {
        StubBudgetDao budgetDao;
        BudgetQuery target(&budgetDao);

        Budgets budgets;
        budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last) month(0x01)), 310));
        budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last) month(0x02)), 280));
        budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last) month(0x03)), 310));
        budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last) month(0x04)), 300));
        ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));

        int total = target.findBudget(year_month_day(year(2018), month(0x01), day(0x02)),
                                      year_month_day(year(2018), month(0x03), day(0x09)));
        ASSERT_EQ(300 + 280 + 90, total);
    }

    TEST(BudgetQuery, no_budget) {
        StubBudgetDao budgetDao;
        BudgetQuery target(&budgetDao);

        Budgets budgets;
        ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));

        int total = target.findBudget(year_month_day(year(2018), month(1), day(2)),
                                      year_month_day(year(2018), month(1), day(2)));
        ASSERT_EQ(0, total);
    }

}