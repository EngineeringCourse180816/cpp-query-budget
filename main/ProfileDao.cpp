#include "ProfileDao.h"
#include "Context.h"

using namespace std;

string ProfileDao::getPassword(const string userName) {
    return Context::getPassword(userName);
}
