#ifndef CPP_OTP_PROFILEDAO_H
#define CPP_OTP_PROFILEDAO_H

#include <string>

using namespace std;

class ProfileDao {

public:
    virtual string getPassword(string userName);
};

#endif //CPP_OTP_PROFILEDAO_H
