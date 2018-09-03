#pragma once
#include "../main/RsaTokenDao.h"
#include "BudgetDao.h"
#include "gmock/gmock.h"

class StubRsaTokenDao : public RsaTokenDao
{
public:
	MOCK_METHOD1(getRandom, std::string(const std::string));
};

class StubBudgetDao : public BudgetDao
{
public:
	MOCK_METHOD0(findAll, Budgets(void));
};
