//
// Created by Joseph Yao on 2018/7/31.
//

#include <string>
#include <iostream>
#include "AuthenticationService.h"

using namespace std;

AuthenticationService::AuthenticationService(ProfileDao &profileDao, RsaTokenDao &rsaTokenDao)
        : profileDao(profileDao), rsaTokenDao(rsaTokenDao) {

}

bool AuthenticationService::isValid(const string userName, const string password) {
    // 根據 account 取得自訂密碼
    auto passwordFromDao = profileDao.getPassword(userName);

    // 根據 account 取得 RSA token 目前的亂數
    auto randomCode = rsaTokenDao.getRandom(userName);

    // 驗證傳入的 password 是否等於自訂密碼 + RSA token亂數
    auto validPassword = passwordFromDao + randomCode;
    auto isValid = password == validPassword;

    if (isValid) {
        return true;
    } else {
        return false;
    }
}
