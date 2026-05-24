#include "register.h"
#include "../utils/helper.h"
#include <iostream>

using namespace std;

namespace auth
{
    bool isUsernameTaken(string username)
    {
        for (int i = 0; i < user::totalUsers; i++)
        {
            if (user::allUsers[i].username == username)
                return true;
        }
        return false;
    }

    bool isNoTelpTaken(string noTelp)
    {
        for (int i = 0; i < user::totalUsers; i++)
        {
            if (user::allUsers[i].nomorHP == noTelp)
                return true;
        }
        return false;
    }

    bool registerUser(user::User *userRegister)
    {
        helper::generateUserID(user::totalUsers, &userRegister->id);

        if (!user::tambahUser(*userRegister))
        {
            cout << "[ERROR] Gagal menyimpan data user\n";
            return false;
        }

        user::allUsers[user::totalUsers] = *userRegister;
        user::totalUsers++;
        cout << "\n[SUKSES] Registrasi berhasil!\n";

        return true;
    }
}