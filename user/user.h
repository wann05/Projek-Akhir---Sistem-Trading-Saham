#pragma once
#include <iostream>
#include <string>
#define MAX_USER 50
#define DB_USERS "./database/user.csv"
using namespace std;

namespace user
{
    struct User
    {
        string id;
        string nama;
        string username;
        string password;
        string pin;
        string nomorHP;
        long long saldo;
    };

    extern User allUsers[MAX_USER];
    extern int totalUsers;
    extern User authUser;
    extern bool isLoggedIn;

    bool loadUsers();
    bool tambahUser(User newUser);
    bool overwriteAllUsersToCSV();

    bool kurangiSaldo(string username, long long jumlah);
    bool tambahSaldo(string username, long long jumlah);
    void tambahSaldoUser(string username);
}