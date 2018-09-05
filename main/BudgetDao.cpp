#include "BudgetDao.h"

BudgetDao::BudgetDao()
{
}

BudgetDao::~BudgetDao()
{
}

Budgets BudgetDao::findAll()
{
	return m_budgets;
}
