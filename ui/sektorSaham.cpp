#include <iostream>
#include "sektorSaham.h"
#include "../trading/stock.h"
#include "../utils/helper.h"
using namespace helper;
using namespace std;
using namespace stock;

void tampilkanSektor(const string &sektor)
{
    int j = 1;
    cout << "\n";
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
            if (saham->sektor == sektor)
            {
                kolom(5, to_string(j++) + ".");
                kolom(10, saham->kode);
                kolom(35, saham->nama);
                kolom(20, saham->sektor);
                kolom(10, formatHarga(saham->harga));
                cout << "\n";
            }
            saham = saham->next;
        }
    }
    if (j == 1)
        cout << "Tidak ada saham pada sektor ini.\n";
    cout << string(80, '=');
}

void sektorSaham()
{
    string sektor[8] = {"Energy", "Healthcare", "Industrial", "Technology", "Transportation", "Property", "Finance", "Infrastructure"};
    int pilih;
    cout << "\n";
    judul("SEKTOR SAHAM", 25);
    for (int i = 0; i < 8; i++)
        cout << i + 1 << ". " << sektor[i] << endl;
    cout << "\nPilihan : ";
    cin >> pilih;
    if (pilih >= 1 && pilih <= 8)
        tampilkanSektor(sektor[pilih - 1]);
    else
        cout << "Pilihan tidak valid\n";
}