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
    Budgets data = m_budgetDao->findAll();

    year_month_day_last startMonth(period.start.year(), month_day_last(period.start.month()));
    year_month_day_last endMonth(period.end.year(), month_day_last(period.end.month()));

    int totalAmount = 0;

    for (year_month_day_last currentMonth = startMonth; currentMonth <= endMonth; currentMonth += months(1)) {

        const Budget &budget = getBudget(data, currentMonth);

        totalAmount += budget.getDailyAmount() * period.getOverlappingDayCount(budget.getPeriod());
    }

    return totalAmount;
}

Budget BudgetQuery::getBudget(Budgets &data, const year_month_day_last &startMonth) const {
    return data.find(startMonth) == data.end() ? Budget(startMonth, 0) : data.find(startMonth)->second;
}