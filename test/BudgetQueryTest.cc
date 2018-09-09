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

    void givenBudgets(vector<Budget> all) {
        for (const Budget& budget : all) {
            budgets.push_back(budget);
        }
        ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));
    }

    Budget budget(int aYear, int aMonth, int amount) {
        const year_month_day_last &yearMonth = year_month_day_last(year(aYear), (month_day_last) month(aMonth));
        return Budget(yearMonth, amount);
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

TEST_F(BudgetQueryTest, two_days_in_budget_month) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(20, target.findBudget(date(2018, 9, 2), date(2018, 9, 3)));
}

TEST_F(BudgetQueryTest, start_before_budget_first_day) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(30, target.findBudget(date(2018, 8, 2), date(2018, 9, 3)));
}

TEST_F(BudgetQueryTest, end_after_budget_last_day) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(110, target.findBudget(date(2018, 9, 20), date(2018, 10, 3)));
}

TEST_F(BudgetQueryTest, end_before_budget_first_day) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(0, target.findBudget(date(2018, 8, 20), date(2018, 8, 30)));
}

TEST_F(BudgetQueryTest, start_after_budget_last_day) {
    givenBudgets({budget(2018, 9, 300)});

    ASSERT_EQ(0, target.findBudget(date(2018, 10, 20), date(2018, 10, 30)));
}

TEST_F(BudgetQueryTest, two_budgets) {
    givenBudgets({budget(2018, 9, 300), budget(2018, 10, 310)});

    ASSERT_EQ(110 + 300, target.findBudget(date(2018, 9, 20), date(2018, 10, 30)));
}

TEST_F(BudgetQueryTest, amount_is_different) {
    givenBudgets({budget(2018, 9, 30), budget(2018, 10, 310)});

    ASSERT_EQ(11 + 300, target.findBudget(date(2018, 9, 20), date(2018, 10, 30)));
}

TEST_F(BudgetQueryTest, no_budget_in_between) {
    givenBudgets({budget(2018, 9, 30), budget(2018, 11, 300)});

    ASSERT_EQ(11 + 300, target.findBudget(date(2018, 9, 20), date(2018, 12, 30)));
}
