#pragma once
#include <iostream>
using namespace std;

#define DB_STOCK "./database/stock.csv"

namespace stock
{
    struct Stock
    {
        string kode;
        string nama;
        string sektor;
        double harga;
        double high;
        double low;
        long long volume;
        double perubahan;
        long long nilai;
        Stock *next = nullptr;
    };

    const int MAX_STOCK = 50;
    extern Stock *hashTable[MAX_STOCK];

    void initHashTable();
    int hashStock(const string &kode);
    void insertStock(Stock *s);
    Stock *cariStock(const string &kode);
    bool loadFromCSV();
    void tampilkanStock();
}