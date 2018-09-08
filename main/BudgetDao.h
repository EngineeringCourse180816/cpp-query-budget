#ifndef CPP_OTP_BUDGETDAO_H
#define CPP_OTP_BUDGETDAO_H

#include <map>
#include "date.h"

using namespace std;
using namespace date;

struct Budget {
	year_month_day_last yearMonth = year_month_day_last(year(1999), month_day_last(month(1)));
	int amount = 0;

	Budget (year_month_day_last yearMonth, int amount) {
		this->yearMonth = yearMonth;
		this->amount = amount;
	}
};
typedef map<year_month_day_last, Budget> Budgets;

class BudgetDao
{
public:
	BudgetDao();
	~BudgetDao();

	virtual Budgets findAll();
private:
	Budgets m_budgets;
};

#endif //CPP_OTP_BUDGETDAO_H

