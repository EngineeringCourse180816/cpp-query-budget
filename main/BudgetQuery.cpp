#include "BudgetQuery.h"
#include "Period.h"

BudgetQuery::BudgetQuery(BudgetDao *budgetDao)
        : m_budgetDao(budgetDao) {
}

BudgetQuery::~BudgetQuery() {
}

int BudgetQuery::findBudget(year_month_day startDate, year_month_day endDate) {
    const Period period = Period(startDate, endDate);

    int totalAmount = 0;

    for (auto const& budget: m_budgetDao->findAll()) {
        totalAmount += budget.getOverlappingAmount(period);
    }

    return totalAmount;
}

