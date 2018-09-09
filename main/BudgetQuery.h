#include "date.h"
#include "BudgetDao.h"

using namespace date;

class BudgetDao;
class BudgetQuery
{
public:
	BudgetQuery(BudgetDao* m_budgetDao);
	~BudgetQuery();

	int findBudget(year_month_day startDate, year_month_day endDate);

private:
	BudgetDao* m_budgetDao;

	Budget getBudget(Budgets &data, const year_month_day_last &startMonth) const;

	unsigned int getDailyAmount(const Budget &budget) const;
};

