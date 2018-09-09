#ifndef CPP_OTP_BUDGETDAO_H
#define CPP_OTP_BUDGETDAO_H

#include <vector>
#include "date.h"
#include "Period.h"

using namespace std;
using namespace date;

class Budget {
public:
	Budget (year_month_day_last yearMonth, int amount) {
		this->yearMonth = yearMonth;
		this->amount = amount;
	}

    int getOverlappingAmount(const Period &period) const {
        return getDailyAmount() * period.getOverlappingDayCount({getFirstDay(), getLastDay()});
    }

private:
    int getDailyAmount() const { return amount / unsigned(yearMonth.day()); }

    year_month_day getLastDay() const {
        return yearMonth;
    }

    year_month_day getFirstDay() const {
        return {yearMonth.year(), yearMonth.month(), day(1)};
    }

    year_month_day_last yearMonth = year_month_day_last(year(1999), month_day_last(month(1)));
	int amount = 0;

};

typedef vector<Budget> Budgets;

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

