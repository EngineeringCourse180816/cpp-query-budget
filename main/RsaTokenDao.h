#ifndef CPP_OTP_RSATOKENDAO_H
#define CPP_OTP_RSATOKENDAO_H

#include <string>

using namespace std;

class RsaTokenDao {

public:
    virtual string getRandom(string userName);
};

#endif //CPP_OTP_RSATOKENDAO_H
