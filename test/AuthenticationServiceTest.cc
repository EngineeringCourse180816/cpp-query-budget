#include "gtest/gtest.h"
#include "../main/AuthenticationService.h"
#include "StubProfileDao.h"
#include "gmock/gmock.h"
#include "StubRsaTokenDao.h"

using ::testing::NiceMock;
using ::testing::Return;

class AuthenticationServiceTest : public testing::Test {
protected:
    NiceMock<StubProfileDao> stubProfileDao;
    NiceMock<StubRsaTokenDao> stubRsaTokenDao;
    AuthenticationService target = AuthenticationService(stubProfileDao, stubRsaTokenDao);

    void givenPassword(string userName, string password) {
        ON_CALL(stubProfileDao, getPassword(userName)).WillByDefault(Return(password));
    }

    void givenToken(string userName, string token) {
        ON_CALL(stubRsaTokenDao, getRandom(userName)).WillByDefault(Return(token));
    }
};

TEST_F(AuthenticationServiceTest, IsValid) {
    givenPassword("joey", "91");
    givenToken("joey", "000000");

    ASSERT_TRUE(target.isValid("joey", "91000000"));
}

TEST_F(AuthenticationServiceTest, IsNotValid) {
    givenPassword("joey", "91");
    givenToken("joey", "000000");

    ASSERT_FALSE(target.isValid("joey", "wrong password"));
}

TEST_F(AuthenticationServiceTest, NormalUsage) {
    ConcreteAuthenticationService target;

    ASSERT_FALSE(target.isValid("joey", "91264206"));
}
