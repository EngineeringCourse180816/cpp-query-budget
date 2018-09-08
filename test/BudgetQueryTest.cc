#include "gtest/gtest.h"
#include <string>
#include "StubClass.h"
#include "../main/BudgetQuery.h"
#include "../main/date.h"
#include <stdarg.h>
#include <array>

using namespace std;
using namespace testing;
using namespace date;

class BudgetQueryTest : public testing::Test {
protected:
    StubBudgetDao budgetDao;
    Budgets budgets;
    BudgetQuery target = BudgetQuery(&budgetDao);

    void givenBudgets(vector<pair<year_month_day_last, int>> all) {
        for (const pair<year_month_day_last, int> budget : all) {
            budgets.insert(budget);
        }
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
    givenBudgets({budget(2018, 1, 310), budget(2018, 2, 280), budget(2018, 3, 310), budget(2018, 4, 300)});

    ASSERT_EQ(300 + 280 + 90, target.findBudget(date(2018, 1, 2), date(2018, 3, 9)));
}

TEST_F(BudgetQueryTest, no_budget) {
    givenBudgets({});

    ASSERT_EQ(0, target.findBudget(date(2018, 1, 2), date(2018, 1, 2)));
}

TEST_F(BudgetQueryTest, one_day_in_budget_month) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(10, target.findBudget(date(2018, 9, 2), date(2018, 9, 2)));
}
