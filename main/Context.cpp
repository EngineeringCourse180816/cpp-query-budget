#include "Context.h"

using namespace std;

map<string, string> Context::profiles;

Context::Context() {
    profiles = {
            {"joey", "91"},
            {"mei",  "99"}
    };
}

string Context::getPassword(const string userName) {
    return profiles[userName];
}
