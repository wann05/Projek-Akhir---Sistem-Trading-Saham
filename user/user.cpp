#include "user.h"
#include "../utils/helper.h"
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
using namespace helper;

namespace user
{
    User allUsers[MAX_USER];
    User authUser;

    int totalUsers = 0;
    bool isLoggedIn = false;

    bool tambahUser(User newUser)
    {
        ofstream file(DB_USERS, ios::app);
        if (file.is_open())
        {
            file << newUser.id << ","
                 << newUser.nama << ","
                 << newUser.username << ","
                 << newUser.password << ","
                 << newUser.pin << ","
                 << newUser.nomorHP << ","
                 << newUser.saldo << endl;
            file.close();
            return true;
        }
        else
        {
            cout << "[ERROR] Gagal membuka file untuk menambahkan user baru.";
            return false;
        }
    }

    bool overwriteAllUsersToCSV()
    {
        ofstream file(DB_USERS);
        if (!file.is_open())
            return false;
        for (int i = 0; i < user::totalUsers; i++)
            file << user::allUsers[i].id << "," << user::allUsers[i].nama << "," << user::allUsers[i].username << "," << user::allUsers[i].password << "," << user::allUsers[i].pin << "," << user::allUsers[i].nomorHP << "," << user::allUsers[i].saldo << endl;
        file.close();
        return true;
    }

    bool loadUsers()
    {
        totalUsers = 0;
        for (int i = 0; i < MAX_USER; i++)
            allUsers[i] = User();

        ifstream file(DB_USERS);
        string line;
        int i = 0;

        if (!file.is_open())
        {
            cout << "[ERROR] File user.csv tidak ditemukan\n";
            return false;
        }

        while (getline(file, line) && i < MAX_USER)
        {
            stringstream ss(line);
            string temp;
            getline(ss, allUsers[i].id, ',');
            getline(ss, allUsers[i].nama, ',');
            getline(ss, allUsers[i].username, ',');
            getline(ss, allUsers[i].password, ',');
            getline(ss, allUsers[i].pin, ',');
            getline(ss, allUsers[i].nomorHP, ',');
            getline(ss, temp, ',');
            allUsers[i].saldo = stoll(temp);
            i++;
        }
        totalUsers = i;
        file.close();
        return true;
    }

    bool kurangiSaldo(string username, long long jumlah)
    {
        for (int i = 0; i < totalUsers; i++)
        {
            if (allUsers[i].username == username)
            {
                allUsers[i].saldo -= jumlah;
                if (authUser.username == username)
                    authUser.saldo = allUsers[i].saldo;
                overwriteAllUsersToCSV();
                return true;
            }
        }
        cout << "[!] User tidak ditemukan\n";
        return false;
    }

    bool tambahSaldo(string username, long long jumlah)
    {
        for (int i = 0; i < totalUsers; i++)
        {
            if (allUsers[i].username == username)
            {
                allUsers[i].saldo += jumlah;
                if (authUser.username == username)
                    authUser.saldo = allUsers[i].saldo;
                overwriteAllUsersToCSV();
                return true;
            }
        }
        cout << "[ERROR] User tidak ditemukan\n";
        return false;
    }

    void tambahSaldoUser(string username)
    {
        long long jumlah;
        cout << "\n";
        judul("TAMBAH SALDO", 50);
        cout << "Masukkan jumlah saldo : Rp ";
        cin >> jumlah;
        if (jumlah <= 0)
        {
            cout << "[ERROR] Jumlah saldo harus lebih dari 0\n";
            return;
        }
        if (tambahSaldo(username, jumlah))
        {
            cout << "[SUKSES] Saldo berhasil ditambahkan\n";
            cout << "Saldo Anda saat ini : Rp " << authUser.saldo << endl;
        }
        cout << string(50, '=');
    }
}
