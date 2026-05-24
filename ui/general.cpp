#include <iostream>
#include <limits>
#include "../user/user.h"
#include "../auth/login.h"
#include "../auth/register.h"
#include "menu.h"
#include "../utils/helper.h"
using namespace std;
using namespace helper;

namespace general
{
    void loginScreen()
    {
        user::User login;
        cout << "\n";
        judul("LOGIN SPEEDTRADE", 30);
        while (true)
        {
            string username, password, pin;
            cout << "Username    : ";
            cin >> username;
            cout << "Password    : ";
            cin >> password;
            cout << "Trading PIN : ";
            cin >> pin;

            login.username = username;
            login.password = password;
            login.pin = pin;

            if (auth::loginUser(&login))
            {
                menu::userMenu();
                return;
            }
            cout << "\n[GAGAL] Login gagal. Silakan coba lagi." << endl;
        }
    }

    string getUsername()
    {
        string username;
        while (true)
        {
            cout << "Masukkan Username      : ";
            cin >> username;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (auth::isUsernameTaken(username))
            {
                cout << "[ERROR] Username sudah digunakan.\n";
                continue;
            }
            return username;
        }
    }

    string getPassword()
    {
        string password, konfirmasiPassword;
        while (true)
        {
            cout << "Masukkan Password      : ";
            cin >> password;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Konfirmasi Password    : ";
            cin >> konfirmasiPassword;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if (password != konfirmasiPassword)
            {
                cout << "\n[ERROR] Password tidak cocok.\n";
                continue;
            }
            return password;
        }
    }

    void registerScreen()
    {
        user::User userRegister;
        judul("REGISTRASI SPEEDTRADE", 30);
        while (true)
        {
            string nama, username, password, pin, nomorHP;
            cout << "Masukkan Nama Lengkap  : ";
            getline(cin >> ws, nama);
            username = getUsername();
            password = getPassword();
            cout << "Masukkan Trading PIN   : ";
            cin >> pin;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Masukkan Nomor Telepon : ";
            cin >> nomorHP;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (auth::isNoTelpTaken(nomorHP))
            {
                cout << "[ERROR] Nomor telepon sudah digunakan.\n";
                continue;
            }

            userRegister.nama = nama;
            userRegister.username = username;
            userRegister.password = password;
            userRegister.pin = pin;
            userRegister.nomorHP = nomorHP;
            userRegister.saldo = 0;

            if (auth::registerUser(&userRegister))
                break;
            cout << "\n[GAGAL] Registrasi gagal.\n";
        }
    }

    void authScreen()
    {
        int pilihan;
        while (true)
        {
            cout << "\n";
            judul("SPEEDTRADE", 20);
            cout << "1. Login" << endl;
            cout << "2. Register" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilihan : ";
            cin >> pilihan;

            if (pilihan == 1)
                loginScreen();
            else if (pilihan == 2)
                registerScreen();
            else if (pilihan == 3)
                exit(0);
            else
                cout << "[ERROR] Pilihan tidak valid\n";
        }
    }
}