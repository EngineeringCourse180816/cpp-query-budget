#include "gtest/gtest.h"
#include <string>
#include "StubClass.h"
#include "../main/BudgetQuery.h"
#include "../main/date.h"
#include <stdarg.h>

using namespace std;
using namespace testing;
using namespace date;

class BudgetQueryTest : public testing::Test {
protected:
    StubBudgetDao budgetDao;
    BudgetQuery target = BudgetQuery(&budgetDao);

    void givenBudgets() {
        Budgets budgets;
        ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));
    }

    pair<year_month_day_last, int> budget(int aYear, int aMonth, int amount) {
        return make_pair(year_month_day_last(year(aYear), (month_day_last) month(aMonth)), amount);
    }

    year_month_day date(int aYear, int aMonth, int aDay) {
        return year_month_day(year(aYear), month(aMonth), day(aDay));
    }

};

TEST_F(BudgetQueryTest, original_test) {

    Budgets budgets;
    budgets.insert(budget(2018, 1, 310));
    budgets.insert(budget(2018, 2, 280));
    budgets.insert(budget(2018, 3, 310));
    budgets.insert(budget(2018, 4, 300));
    ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));

    ASSERT_EQ(300 + 280 + 90, target.findBudget(date(2018, 1, 2), date(2018, 3, 9)));
}

TEST_F(BudgetQueryTest, no_budget) {
    givenBudgets();

    ASSERT_EQ(0, target.findBudget(date(2018, 1, 2), date(2018, 1, 2)));
}
