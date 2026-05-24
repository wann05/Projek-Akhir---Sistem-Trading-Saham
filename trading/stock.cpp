#include "stock.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../utils/helper.h"
using namespace std;
using namespace helper;

namespace stock
{
    Stock *hashTable[MAX_STOCK];

    void initHashTable()
    {
        for (int i = 0; i < MAX_STOCK; i++)
            hashTable[i] = nullptr;
    }

    int hashStock(const string &kode)
    {
        int total = 0;
        for (int i = 0; i < kode.length(); i++)
            total += kode[i];
        return total % MAX_STOCK;
    }

    void insertStock(Stock *s)
    {
        int i = hashStock(s->kode);
        s->next = hashTable[i];
        hashTable[i] = s;
    }

    Stock *cariStock(const string &kode)
    {
        Stock *cari = hashTable[hashStock(kode)];
        while (cari)
        {
            if (cari->kode == kode)
                return cari;
            cari = cari->next;
        }
        return nullptr;
    }

    bool loadFromCSV()
    {
        initHashTable();
        ifstream fileCSV(DB_STOCK);

        if (!fileCSV.is_open())
        {
            cout << "[!] File stock.csv tidak ditemukan\n";
            return false;
        }

        string line;

        while (getline(fileCSV, line))
        {
            if (line.empty())
                continue;

            stringstream ss(line);

            string kode, nama, sektor;
            string harga, high, low, volume, perubahan, nilai;

            getline(ss, kode, ',');
            getline(ss, nama, ',');
            getline(ss, sektor, ',');
            getline(ss, harga, ',');
            getline(ss, high, ',');
            getline(ss, low, ',');
            getline(ss, volume, ',');
            getline(ss, perubahan, ',');
            getline(ss, nilai, ',');

            Stock *s = new Stock();
            s->kode = kode;
            s->nama = nama;
            s->sektor = sektor;
            s->harga = stod(harga);
            s->high = stod(high);
            s->low = stod(low);
            s->volume = stoll(volume);
            s->perubahan = stod(perubahan);
            s->nilai = stoll(nilai);
            s->next = nullptr;

            insertStock(s);
        }

        fileCSV.close();
        return true;
    }

    void tampilkanStock()
    {
        int j = 1;
        judul("INFORMASI SAHAM", 80);
        kolom(5, "No");
        kolom(10, "Kode");
        kolom(35, "Emiten");
        kolom(20, "Sektor");
        kolom(10, "Harga");
        cout << endl;
        cout << string(80, '-') << "\n";

        for (int i = 0; i < MAX_STOCK; i++)
        {
            Stock *saham = hashTable[i];
            while (saham)
            {
                kolom(5, to_string(j++) + ".");
                kolom(10, saham->kode);
                kolom(35, saham->nama);
                kolom(20, saham->sektor);
                kolom(10, formatHarga(saham->harga));
                cout << endl;
                saham = saham->next;
            }
        }
        cout << string(80, '=') << "\n";
        cout << endl;
    }
}