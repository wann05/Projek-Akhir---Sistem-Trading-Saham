#pragma once
#include <iostream>
using namespace std;
#define DB_PORTFOLIO "./database/portfolio.csv"

namespace portfolio
{
    struct PortfolioItem
    {
        string username;
        string kode;
        int lot;
        double avgBuy;
        PortfolioItem *next = nullptr;
    };

    extern PortfolioItem *headPortfolio;

    PortfolioItem *cariItem(const string &username, const string &kode);
    void tambahAtauUpdate(const string &username, const string &kode, int lot, double harga);
    void kurangiLot(const string &username, const string &kode, int lot);
    void lihatPortfolio(const string &username);
    bool loadFromCSV();
    void saveToCSV();
    void clearPortfolio();
    void lihatPortfolioJual(const string &username);
}