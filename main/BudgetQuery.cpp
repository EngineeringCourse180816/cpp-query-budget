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
        return (getBudgetAmount(data, startMonth) / unsigned(startMonth.day()) * diffDays);
    }

    int totalAmount = 0;

    for (year_month_day_last currentMonth = startMonth; currentMonth <= endMonth; currentMonth += months(1)) {

        int amount = getBudgetAmount(data, currentMonth);

        if (startMonth == currentMonth) {
            unsigned startMonDays = unsigned(startMonth.day());
            unsigned startYearMonDays = unsigned(startDate.day());
            int diffDays = startMonDays - startYearMonDays + 1;
            totalAmount += (amount * diffDays / startMonDays);
        } else if (endMonth == currentMonth) {
            unsigned endYearMonDays = unsigned(endDate.day());
            totalAmount += (amount * endYearMonDays / unsigned(currentMonth.day()));
        } else {
            totalAmount += amount;
        }

    }

    return totalAmount;
}

int BudgetQuery::getBudgetAmount(Budgets &data, const year_month_day_last &startMonth) const {
    return data.find(startMonth) == data.end() ? 0 : data.find(startMonth)->second;
}