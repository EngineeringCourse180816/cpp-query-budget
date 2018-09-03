#include "gtest/gtest.h"
#include "../main/AuthenticationService.h"
#include "../main/ProfileDao.h"
#include "../main/RsaTokenDao.h"
#include <string>
#include "../main/StubClass.h"
#include "../main/BudgetQuery.h"
#include "../main/date.h"

using namespace std;
using namespace testing;
using namespace date;


namespace {

	TEST(BudgetQuery, findBudget) {
		StubBudgetDao budgetDao;
		BudgetQuery target(&budgetDao);

		Budgets budgets;
		budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last)month(0x01)), 370));
		budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last)month(0x02)), 370));
		budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last)month(0x03)), 370));
		budgets.insert(make_pair(year_month_day_last(year(2018), (month_day_last)month(0x04)), 370));
		ON_CALL(budgetDao, findAll()).WillByDefault(Return(budgets));
		int total = target.findBudget(year_month_day(year(2018), month(0x01), day(0x02)),
			year_month_day(year(2018), month(0x03), day(0x09)));
		ASSERT_TRUE(200 == total);
	}

  //  TEST(AuthenticationService, IsValid) {
		//MockOtpLogger logger;
		//StubRsaTokenDao rasToken;
  //      AuthenticationService target(&rasToken, &logger);
		//ON_CALL(rasToken, getRandom("joey")).WillByDefault(Return("000000"));
  //      ASSERT_TRUE(target.isValid("joey", "91000000"));
		////EXPECT_CALL(rasToken, getRandom("joey")).WillOnce(Return("000000"));
		////ASSERT_TRUE(target.isValid("joey", "91000000"));
		//EXPECT_CALL(rasToken, getRandom("joey")).WillOnce(Return("000001"));
		//EXPECT_CALL(logger, printf("Authentication is invalid!"));
		//ASSERT_FALSE(target.isValid("joey", "91000000"));
		////ASSERT_TRUE("Authentication is invalid!" == logger.getMsg());
  //  }

	//TEST(AuthenticationService, isTodayBirth) {
	//	OtpLogger logger;
	//	RsaTokenDao rasToken;
	//	AuthenticationService target(&rasToken, &logger);
	//	ASSERT_FALSE(target.isTodayBirth());

	//	SYSTEMTIME stUTC;
	//	::GetSystemTime(&stUTC);
	//	SYSTEMTIME newTime = stUTC;
	//	newTime.wMonth = 4;
	//	newTime.wDay = 9;
	//	SetSystemTime(&newTime);
	//	ASSERT_TRUE(target.isTodayBirth());
	//	SetSystemTime(&stUTC);


	//	//ASSERT_TRUE(target.isTodayBirth(4, 9));
	//	//ASSERT_FALSE(target.isTodayBirth(9, 32));
	//	//ASSERT_FALSE(target.isTodayBirth(9, 0));
	//	//ASSERT_FALSE(target.isTodayBirth(0, 12));
	//	//ASSERT_FALSE(target.isTodayBirth(13, 12));
	//}
}