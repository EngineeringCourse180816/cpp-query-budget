#include "BudgetQuery.h"
#include "Period.h"

BudgetQuery::BudgetQuery(BudgetDao *budgetDao)
        : m_budgetDao(budgetDao) {
}

BudgetQuery::~BudgetQuery() {
}

int BudgetQuery::findBudget(year_month_day startDate, year_month_day endDate) {
    return queryBudget(Period(startDate, endDate));
}

int BudgetQuery::queryBudget(const Period period) const {
    int totalAmount = 0;

    for (auto const& yearMonthBudget: m_budgetDao->findAll()) {
        totalAmount += yearMonthBudget.second.getDailyAmount() * period.getOverlappingDayCount(yearMonthBudget.second.getPeriod());
    }

    return totalAmount;
}

