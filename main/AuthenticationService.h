#ifndef CPP_OTP_AUTHENTICATIONSERVICE_H
#define CPP_OTP_AUTHENTICATIONSERVICE_H

#include <string>
#include "ProfileDao.h"
#include "RsaTokenDao.h"

using namespace std;

class AuthenticationService {

public:
    AuthenticationService(ProfileDao &profileDao, RsaTokenDao &rsaTokenDao);

    bool isValid(string userName, string password);

private:
    ProfileDao& profileDao;
    RsaTokenDao& rsaTokenDao;
};

class ConcreteAuthenticationService : public AuthenticationService {
public:
    ConcreteAuthenticationService() : AuthenticationService(profileDao, rsaTokenDao) { }

private:
    ProfileDao profileDao;
    RsaTokenDao rsaTokenDao;
};


#endif //CPP_OTP_AUTHENTICATIONSERVICE_H
