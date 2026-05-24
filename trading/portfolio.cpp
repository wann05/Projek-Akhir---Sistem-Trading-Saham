#include "portfolio.h"
#include "stock.h"
#include "../utils/helper.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
using namespace helper;

namespace portfolio
{
    PortfolioItem *headPortfolio = nullptr;

    PortfolioItem *cariItem(const string &username, const string &kode)
    {
        PortfolioItem *porto = headPortfolio;
        while (porto)
        {
            if (porto->username == username && porto->kode == kode)
                return porto;
            porto = porto->next;
        }
        return nullptr;
    }

    void tambahAtauUpdate(const string &username, const string &kode, int lot, double harga)
    {
        PortfolioItem *porto = cariItem(username, kode);
        if (porto)
        {
            double totalNilai = (porto->avgBuy * porto->lot * 100) + (harga * lot * 100);
            porto->lot += lot;
            porto->avgBuy = totalNilai / (porto->lot * 100);
        }
        else
        {
            PortfolioItem *newPorto = new PortfolioItem();
            newPorto->username = username;
            newPorto->kode = kode;
            newPorto->lot = lot;
            newPorto->avgBuy = harga;
            newPorto->next = headPortfolio;
            headPortfolio = newPorto;
        }
        saveToCSV();
    }

    void kurangiLot(const string &username, const string &kode, int lot)
    {
        PortfolioItem *porto = headPortfolio;
        PortfolioItem *prev = nullptr;
        while (porto)
        {
            if (porto->username == username && porto->kode == kode)
            {
                porto->lot -= lot;
                if (porto->lot <= 0)
                {
                    if (prev)
                        prev->next = porto->next;
                    else
                        headPortfolio = porto->next;
                    delete porto;
                }
                saveToCSV();
                return;
            }
            prev = porto;
            porto = porto->next;
        }
        cout << "Saham tidak ditemukan\n";
    }

    void lihatPortfolio(const string &username)
    {
        long long totalAset = 0;
        long long totalProfit = 0;
        bool ada = false;

        cout << endl;
        judul("PORTOFOLIO", 70);
        kolom(8, "Kode");
        kolom(6, "Lot");
        kolom(12, "Avg Buy");
        kolom(12, "Harga Now");
        kolom(14, "Profit/Loss");
        kolom(14, "Sektor");
        cout << "\n"
             << string(70, '-') << "\n";

        PortfolioItem *porto = headPortfolio;
        while (porto)
        {
            if (porto->username == username)
            {
                ada = true;
                stock::Stock *saham = stock::cariStock(porto->kode);
                double lastPrice;
                string sektor;
                if (saham)
                {
                    lastPrice = saham->harga;
                    sektor = saham->sektor;
                }
                else
                {
                    lastPrice = porto->avgBuy;
                    sektor = "-";
                }

                double profitLoss = (lastPrice - porto->avgBuy) * porto->lot * 100;
                totalAset += lastPrice * porto->lot * 100;
                totalProfit += profitLoss;

                kolom(8, porto->kode);
                kolom(6, porto->lot);
                kolom(12, porto->avgBuy);
                kolom(12, lastPrice);
                kolom(14, profitLoss);
                kolom(14, sektor);
                cout << "\n";
            }
            porto = porto->next;
        }

        if (!ada)
        {
            cout << "Portofolio kosong\n";
            return;
        }
        cout << string(70, '-') << "\n";
        cout << "Total Aset   : Rp " << totalAset << "\n";
        cout << "Total Profit : Rp " << totalProfit << "\n";
        cout << string(70, '=') << "\n";
    }

    void lihatPortfolioJual(const string &username)
    {
        bool ada = false;
        PortfolioItem *porto = headPortfolio;
        int no = 1;
        kolom(5, "No");
        kolom(10, "Kode");
        kolom(7, "Lot");
        kolom(10, "Harga");
        cout << "\n"
             << string(28, '-') << "\n";
        while (porto)
        {
            if (porto->username == username)
            {
                ada = true;
                kolom(5, to_string(no++) + ".");
                kolom(10, porto->kode);
                kolom(7, porto->lot);
                kolom(10, porto->avgBuy);
                cout << "\n";
            }
            porto = porto->next;
        }
        if (!ada)
        {
            cout << "Portofolio kosong\n";
            return;
        }
        cout << string(28, '=');
    }

    bool loadFromCSV()
    {
        ifstream fileCSV(DB_PORTFOLIO);
        if (!fileCSV.is_open())
        {
            cout << "[ERROR] File portfolio.csv tidak ditemukan\n";
            return false;
        }
        clearPortfolio();
        string line;
        while (getline(fileCSV, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            string username, kode, lot, avgBuy;
            getline(ss, username, ',');
            getline(ss, kode, ',');
            getline(ss, lot, ',');
            getline(ss, avgBuy, ',');

            PortfolioItem *newPorto = new PortfolioItem();
            newPorto->username = username;
            newPorto->kode = kode;
            newPorto->lot = stoi(lot);
            newPorto->avgBuy = stod(avgBuy);
            newPorto->next = headPortfolio;
            headPortfolio = newPorto;
        }
        fileCSV.close();
        return true;
    }

    void saveToCSV()
    {
        ofstream fileCSV(DB_PORTFOLIO);
        PortfolioItem *item = headPortfolio;
        while (item)
        {
            fileCSV << item->username << "," << item->kode << ","
                    << item->lot << "," << item->avgBuy << "\n";
            item = item->next;
        }
        fileCSV.close();
    }

    void clearPortfolio()
    {
        PortfolioItem *curr = headPortfolio;
        while (curr)
        {
            PortfolioItem *hapus = curr;
            curr = curr->next;
            delete hapus;
        }
        headPortfolio = nullptr;
    }
}