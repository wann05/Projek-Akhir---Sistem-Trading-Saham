#include <iostream>
#include "../user/user.h"
#include "../trading/stock.h"
#include "../utils/helper.h"
#include "../trading/portfolio.h"
#include "../trading/order.h"
#include "jualSaham.h"
using namespace std;
using namespace stock;
using namespace user;
using namespace portfolio;
using namespace order;
using namespace helper;

void jualSaham()
{
    string kode;
    judul("KEPEMILIKAN SAHAM", 28);
    portfolio::lihatPortfolioJual(user::authUser.username);
    cout << "\n\nMasukkan kode saham : ";
    cin >> kode;

    order::TipeOrder tipe = SELL;

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
        cout << "Volume          : " << saham->volume << "\n";
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

    PortfolioItem *cekPortfolio = portfolio::cariItem(user::authUser.username, saham->kode);
    if (!cekPortfolio)
    {
        cout << "\n[ERROR] Anda tidak memiliki saham ini.\n";
        return;
    }

    int harga, lot, pilih;
    cout << "\n\n";
    judul("INPUT ORDER", 50);
    cout << "Harga Jual : Rp ";
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
    if (lot > cekPortfolio->lot)
    {
        cout << "\n[ERROR] Lot saham tidak mencukupi!\n";
        return;
    }

    long long totalHarga = harga * lot * 100;
    cout << "Total Harga : Rp" << totalHarga << endl;

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