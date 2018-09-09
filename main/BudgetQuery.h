#include "date.h"
#include "BudgetDao.h"
#include "Period.h"

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

};

