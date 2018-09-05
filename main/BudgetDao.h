#include <map>
#include "date.h"

using namespace std;
using namespace date;

typedef map<year_month_day_last, int> Budgets;

class BudgetDao
{
public:
	BudgetDao();
	~BudgetDao();

	virtual Budgets findAll();
private:
	Budgets m_budgets;
};

