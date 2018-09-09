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
    if (data.empty())
        return 0;

    year_month_day_last startMonth(period.start.year(), month_day_last(period.start.month()));
    year_month_day_last endMonth(period.end.year(), month_day_last(period.end.month()));

    if (startMonth == endMonth) {
        return getBudget(data, startMonth).getDailyAmount() * period.getDayCount();
    }

    int totalAmount = 0;

    for (year_month_day_last currentMonth = startMonth; currentMonth <= endMonth; currentMonth += months(1)) {

        const Budget &budget = getBudget(data, currentMonth);

        if (startMonth == currentMonth) {
            totalAmount += budget.getDailyAmount() * getOverlappingDayCount(period, budget.getPeriod());
        } else if (endMonth == currentMonth) {
            int diffDays = unsigned(period.end.day()) - unsigned(budget.getFirstDay().day()) + 1;
            totalAmount += budget.getDailyAmount() * diffDays;
        } else {
            int diffDays = unsigned(budget.getLastDay().day()) - unsigned(budget.getFirstDay().day()) + 1;
            totalAmount += budget.getDailyAmount() * diffDays;
        }

    }

    return totalAmount;
}

int BudgetQuery::getOverlappingDayCount(const Period &period, const Period &another) const {
    return unsigned(another.end.day()) - unsigned(period.start.day()) + 1;
}

Budget BudgetQuery::getBudget(Budgets &data, const year_month_day_last &startMonth) const {
    return data.find(startMonth) == data.end() ? Budget(startMonth, 0) : data.find(startMonth)->second;
}