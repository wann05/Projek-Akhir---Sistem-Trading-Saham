#include "transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../utils/helper.h"
using namespace helper;
using namespace std;

namespace transaksi
{
    Transaction *top = nullptr;

    string generateId()
    {
        int count = 1;
        Transaction *tr = top;
        while (tr)
        {
            count++;
            tr = tr->next;
        }
        return "TR-" + to_string(count);
    }

    void push(Transaction *transaksi)
    {
        transaksi->next = top;
        top = transaksi;
    }

    void catatTransaksi(string username, string tipe, string kodeSaham, int lot, double harga)
    {
        Transaction *transaksi = new Transaction();
        transaksi->id = generateId();
        transaksi->username = username;
        transaksi->tipe = tipe;
        transaksi->kodeSaham = kodeSaham;
        transaksi->lot = lot;
        transaksi->harga = harga;
        transaksi->total = lot * harga * 100;
        transaksi->next = nullptr;

        push(transaksi);
        saveToCSV();
    }

    void tampilHistori(string username)
    {
        cout << "\n";
        judul("HISTORI TRANSAKSI", 65);
        kolom(6, "No");
        kolom(8, "ID");
        kolom(8, "Tipe");
        kolom(10, "Saham");
        kolom(6, "Lot");
        kolom(12, "Harga");
        kolom(15, "Total");
        cout << "\n"
             << string(65, '-') << "\n";

        bool ada = false;
        int no = 1;
        Transaction *transaksi = top;
        while (transaksi)
        {
            if (transaksi->username == username)
            {
                kolom(6, no);
                kolom(8, transaksi->id);
                kolom(8, transaksi->tipe);
                kolom(10, transaksi->kodeSaham);
                kolom(6, transaksi->lot);
                kolom(12, transaksi->harga);
                kolom(15, transaksi->total);
                cout << "\n";
                no++;
                ada = true;
            }
            transaksi = transaksi->next;
        }
        if (!ada)
            cout << "Belum ada transaksi\n";
        cout << string(65, '=') << "\n";
    }

    bool loadFromCSV()
    {
        while (top)
        {
            Transaction *hapus = top;
            top = top->next;
            delete hapus;
        }

        ifstream fileCSV(DB_TRANSACTION);
        if (!fileCSV.is_open())
        {
            cout << "[ERROR] File transaksi.csv tidak ditemukan\n";
            return false;
        }

        string line;
        const int MAX = 100;
        Transaction *temp[MAX];
        int count = 0;

        while (getline(fileCSV, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            string id, username, tipe, kodeSaham, lot, harga, total;
            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, tipe, ',');
            getline(ss, kodeSaham, ',');
            getline(ss, lot, ',');
            getline(ss, harga, ',');
            getline(ss, total, ',');

            if (!total.empty() && total.back() == '\r')
                total.pop_back();

            Transaction *transaksi = new Transaction();
            transaksi->id = id;
            transaksi->username = username;
            transaksi->tipe = tipe;
            transaksi->kodeSaham = kodeSaham;
            transaksi->lot = stoi(lot);
            transaksi->harga = stoll(harga);
            transaksi->total = stoll(total);
            transaksi->next = nullptr;

            temp[count] = transaksi;
            count++;
        }
        fileCSV.close();
        for (int i = count - 1; i >= 0; i--)
            push(temp[i]);
        return true;
    }

    void saveToCSV()
    {
        ofstream fileCSV(DB_TRANSACTION);
        Transaction *curr = top;
        while (curr)
        {
            fileCSV << curr->id << "," << curr->username << ","
                    << curr->tipe << "," << curr->kodeSaham << ","
                    << curr->lot << "," << curr->harga << ","
                    << curr->total << "\n";
            curr = curr->next;
        }
        fileCSV.close();
    }
}