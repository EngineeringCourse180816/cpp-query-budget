#pragma once
#include "date.h"

using namespace date;

class BudgetDao;
class BudgetQuery
{
public:
	BudgetQuery(BudgetDao* m_budgetDao);
	~BudgetQuery();

	int findBudget(year_month_day startDay, year_month_day endDay);

private:
	BudgetDao* m_budgetDao;
};

