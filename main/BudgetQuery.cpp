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

    for (year_month_day_last tmpYearMon = startMonth; tmpYearMon <= endMonth; tmpYearMon += months(1)) {

        int monAmount = 0;
        auto it = data.find(tmpYearMon);
        if (it != data.end())
            monAmount = data.find(tmpYearMon)->second;

        if (startMonth == tmpYearMon) {
            unsigned startMonDays = unsigned(startMonth.day());
            unsigned startYearMonDays = unsigned(startDate.day());
            int diffDays = startMonDays - startYearMonDays + 1;
            totalAmount += (monAmount * diffDays / startMonDays);
        } else if (endMonth == tmpYearMon) {
            unsigned endYearMonDays = unsigned(endDate.day());
            totalAmount += (monAmount * endYearMonDays / unsigned(tmpYearMon.day()));
        } else {
            totalAmount += monAmount;
        }

    }

    return totalAmount;
}

int BudgetQuery::getBudgetAmount(Budgets &data, const year_month_day_last &startMonth) const {
    int monAmount = data.find(startMonth) == data.end() ? 0 : data.find(startMonth)->second;
    return monAmount;
}