#include "BudgetQuery.h"

BudgetQuery::BudgetQuery(BudgetDao *budgetDao)
        : m_budgetDao(budgetDao) {
}

BudgetQuery::~BudgetQuery() {
}

int BudgetQuery::findBudget(year_month_day startDate, year_month_day endDate) {
    Budgets data = m_budgetDao->findAll();
    if (data.empty())
        return 0;

    year_month_day_last startMonth(startDate.year(), month_day_last(startDate.month()));
    year_month_day_last endMonth(endDate.year(), month_day_last(endDate.month()));

    if (startMonth == endMonth) {
        int diffDays = unsigned(endDate.day()) - unsigned(startDate.day()) + 1;
        return getBudgetAmount(data, startMonth).amount / unsigned(startMonth.day()) * diffDays;
    }

    int totalAmount = 0;

    for (year_month_day_last currentMonth = startMonth; currentMonth <= endMonth; currentMonth += months(1)) {

        const Budget &budget = getBudgetAmount(data, currentMonth);

        if (startMonth == currentMonth) {
            int diffDays = unsigned(startMonth.day()) - unsigned(startDate.day()) + 1;
            totalAmount += budget.amount / unsigned(currentMonth.day()) * diffDays;
        } else if (endMonth == currentMonth) {
            int diffDays = unsigned(endDate.day()) - unsigned(year_month_day(currentMonth.year(), currentMonth.month(), day(1)).day()) + 1;
            totalAmount += budget.amount / unsigned(currentMonth.day()) * diffDays;
        } else {
            int diffDays = unsigned(currentMonth.day()) - unsigned(year_month_day(currentMonth.year(), currentMonth.month(), day(1)).day()) + 1;
            totalAmount += budget.amount / unsigned(currentMonth.day()) * diffDays;
        }

    }

    return totalAmount;
}

Budget BudgetQuery::getBudgetAmount(Budgets &data, const year_month_day_last &startMonth) const {
    return data.find(startMonth) == data.end() ? Budget(startMonth, 0) : data.find(startMonth)->second;
}