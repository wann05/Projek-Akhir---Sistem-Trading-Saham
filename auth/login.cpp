#include "login.h"
#include <iostream>
using namespace std;
using namespace user;

namespace auth
{
    bool loginUser(user::User *userLogin)
    {
        for (int i = 0; i < user::totalUsers; i++)
        {
            if (allUsers[i].username == userLogin->username)
            {
                if (allUsers[i].password == userLogin->password)
                {
                    if (allUsers[i].pin == userLogin->pin)
                    {
                        authUser = allUsers[i];
                        isLoggedIn = true;

                        cout << "\n[SUKSES] Selamat datang, " << authUser.nama << "!\n"
                             << endl;
                        return true;
                    }
                    cout << "\n[ERROR] Trading PIN salah!\n";
                    return false;
                }
                cout << "\n[ERROR] Password salah!\n";
                return false;
            }
        }
        cout << "\n[ERROR] Username tidak ditemukan.\n";
        return false;
    }
}