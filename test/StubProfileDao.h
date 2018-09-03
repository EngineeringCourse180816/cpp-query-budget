#ifndef CPP_OTP_STUBPROFILEDAO_H
#define CPP_OTP_STUBPROFILEDAO_H

#include "gmock/gmock.h"
#include "../main/ProfileDao.h"

using namespace std;

class StubProfileDao : public ProfileDao {

public:
    MOCK_METHOD1(getPassword, string(string));
};


#endif //CPP_OTP_STUBPROFILEDAO_H
