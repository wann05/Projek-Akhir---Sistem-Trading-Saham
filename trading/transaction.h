#pragma once
#include <iostream>
using namespace std;

#define DB_TRANSACTION "./database/transaksi.csv"

namespace transaksi
{
    struct Transaction
    {
        string id;
        string username;
        string tipe;
        string kodeSaham;
        int lot;
        long long harga;
        long long total;
        Transaction *next = nullptr;
    };

    extern Transaction *top;

    void push(Transaction *transaksi);
    void tampilHistori(string username);
    void catatTransaksi(string username, string tipe, string kodeSaham, int lot, double harga);
    bool loadFromCSV();
    void saveToCSV();
}