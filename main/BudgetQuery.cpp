#include "BudgetQuery.h"
#include "BudgetDao.h"


BudgetQuery::BudgetQuery(BudgetDao* budgetDao)
	: m_budgetDao(budgetDao)
{
}

BudgetQuery::~BudgetQuery()
{
}

int BudgetQuery::findBudget(year_month_day startYearMonDay, year_month_day endYearMonDay)
{
	int totalAmount = 0;
	//if (startYearMonDay.ok()  || endYearMonDay.ok())
	//{
	//	return totalAmount;
	//}
	
	Budgets data = m_budgetDao->findAll();
	if (data.empty())
		return 0;

	year_month_day_last startMon(startYearMonDay.year(), month_day_last(startYearMonDay.month()));
	year_month_day_last endMon(endYearMonDay.year(), month_day_last(endYearMonDay.month()));
	if (startMon == endMon)
	{
		int monAmount = data.find(startMon)->second;
		unsigned startMonDays = unsigned(startYearMonDay.day());
		unsigned endMonDays = unsigned(endYearMonDay.day());
		int diffDays = endMonDays - startMonDays + 1;
		totalAmount += (monAmount / startMonDays * diffDays);
	}
	else if (startMon < endMon)
	{
		year_month_day_last tmpYearMon = startMon;
		while (tmpYearMon <= endMon)
		{
			int monAmount = 0;
			map<year_month_day_last, int>::iterator it = data.find(tmpYearMon);
			if(it != data.end())
				monAmount = data.find(tmpYearMon)->second;

			if (startMon == tmpYearMon)
			{
				unsigned startMonDays = unsigned(startMon.day());
				unsigned startYearMonDays = unsigned(startYearMonDay.day());
				int diffDays = startMonDays - startYearMonDays + 1;
				totalAmount += (monAmount * diffDays / startMonDays);
			}
			else if (endMon == tmpYearMon)
			{
				unsigned startMonDays = unsigned(startMon.day());
				unsigned endYearMonDays = unsigned(endYearMonDay.day());
				totalAmount += (monAmount * endYearMonDays / startMonDays);
			}
			else
			{
				totalAmount += monAmount;
			}
			tmpYearMon += months(1);
		}
		
	}
	return totalAmount;
}