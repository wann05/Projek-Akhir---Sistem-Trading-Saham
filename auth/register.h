#pragma once
#include "../user/user.h"

namespace auth
{
    bool isUsernameTaken(string usernameInput);
    bool isNoTelpTaken(string no_telpInput);
    bool registerUser(user::User *userRegister);
}
