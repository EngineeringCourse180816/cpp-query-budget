#include "../main/BudgetDao.h"
#include "gmock/gmock.h"

class StubBudgetDao : public BudgetDao
{
public:
	MOCK_METHOD0(findAll, Budgets(void));
};
