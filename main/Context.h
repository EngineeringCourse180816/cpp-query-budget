#ifndef CPP_OTP_CONTEXT_H
#define CPP_OTP_CONTEXT_H

#include <string>
#include <map>

using namespace std;

class Context {

public:
    Context();

    static string getPassword(string userName);

    static map<string, string> profiles;

};

#endif //CPP_OTP_CONTEXT_H
