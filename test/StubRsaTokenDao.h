#ifndef CPP_OTP_STUBRSATOKENDAO_H
#define CPP_OTP_STUBRSATOKENDAO_H


#include "gmock/gmock.h"
#include "../main/RsaTokenDao.h"

using namespace std;

class StubRsaTokenDao : public RsaTokenDao {

public:
    MOCK_METHOD1(getRandom, string(string));

};


#endif //CPP_OTP_STUBRSATOKENDAO_H
