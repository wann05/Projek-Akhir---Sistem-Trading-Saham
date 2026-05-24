#include <iostream>
#include "beliSaham.h"
#include "../user/user.h"
#include "../trading/stock.h"
#include "../utils/helper.h"
#include "../trading/portfolio.h"
#include "../trading/order.h"
using namespace std;
using namespace stock;
using namespace user;
using namespace portfolio;
using namespace order;
using namespace helper;

void beliSaham()
{
    string kode;
    stock::tampilkanStock();
    cout << "\nMasukkan kode saham : ";
    cin >> kode;

    order::TipeOrder tipe = BUY;

    helper::toUpperCase(kode);
    Stock *saham = cariStock(kode);
    if (saham != nullptr)
    {
        cout << endl;
        judul("INFORMASI SAHAM", 50);
        cout << "Kode Saham      : " << saham->kode << "\n";
        cout << "Nama Perusahaan : " << saham->nama << "\n";
        cout << "Sektor          : " << saham->sektor << "\n";
        cout << "Harga Market    : Rp " << saham->harga << "\n";
        cout << "ARA             : Rp " << saham->high << "\n";
        cout << "ARB             : Rp " << saham->low << "\n";
        cout << "Volume          : Rp " << saham->volume << "\n";
        cout << "Perubahan       : " << saham->perubahan << "%\n";

        PortfolioItem *porto = portfolio::cariItem(user::authUser.username, saham->kode);
        if (porto)
            cout << "Lot Dimiliki    : " << porto->lot << " lot";
        else
            cout << "Lot Dimiliki    : 0 lot";
    }
    else
    {
        cout << "Saham Tidak di Temukan";
        return;
    }
    cout << "\n"
         << string(50, '=');

    int harga, lot, pilih;
    cout << "\n\n";
    judul("INPUT ORDER", 50);
    cout << "Harga Beli : Rp ";
    cin >> harga;
    if (harga < saham->low || harga > saham->high)
    {
        cout << "\n[ERROR] Harga tidak boleh diatas ARA dan dibawah ARB" << endl;
        return;
    }
    cout << "Jumlah Lot : ";
    cin >> lot;
    if (lot <= 0)
    {
        cout << "\n[ERROR] Jumlah lot tidak valid!" << endl;
        return;
    }

    long long totalHarga = harga * lot * 100;
    cout << "Total Harga : Rp" << totalHarga << endl;
    if (user::authUser.saldo < totalHarga)
    {
        cout << "\n[ERROR] Saldo Anda tidak mencukupi!" << endl;
        return;
    }

    cout << "\n1. Konfirmasi" << endl;
    cout << "2. Batal" << endl;
    cout << "Pilihan : ";
    cin >> pilih;

    if (pilih == 1)
        buatOrder(user::authUser.username, tipe, saham->kode, lot, harga);
    else if (pilih == 2)
        return;
    else
        cout << "Pilihan Anda Tidak Valid!";
}