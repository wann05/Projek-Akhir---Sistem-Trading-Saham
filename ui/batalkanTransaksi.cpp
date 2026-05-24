#include <iostream>
#include "batalkanTransaksi.h"
#include "../utils/helper.h"
#include "../user/user.h"
#include "../trading/portfolio.h"
using namespace helper;
using namespace std;
using namespace order;
using namespace user;
using namespace portfolio;

namespace batalkanTransaksi
{
    void tampilkanOrderAktif(const string &username)
    {
        Order *order = headOrder;
        int no = 1;
        cout << "\n";
        judul("ORDER AKTIF", 50);
        kolom(5, "No");
        kolom(5, "ID");
        kolom(10, "Tipe");
        kolom(10, "Kode");
        kolom(15, "Sisa Lot");
        kolom(10, "Harga");
        cout << "\n"
             << string(50, '-') << "\n";

        while (order)
        {
            if (order->username == username && (order->status == OPEN || order->status == PARTIAL_MATCH))
            {
                kolom(5, to_string(no++) + ".");
                kolom(5, order->id);
                kolom(10, tipeToString(order->tipe));
                kolom(10, order->kodeSaham);
                kolom(15, to_string(order->sisaLot) + "/" + to_string(order->lot) + " lot");
                kolom(10, formatHarga(order->harga));
                cout << "\n";
            }
            order = order->nextOrder;
        }
        if (no == 1)
        {
            cout << "Tidak ada order aktif\n";
            return;
        }
        cout << string(50, '=') << "\n";
    }

    void batalkanTransaksi(const string &username)
    {
        tampilkanOrderAktif(username);
        cout << "\nMasukkan ID order yang ingin Anda batalkan : ";
        string id;
        cin >> id;

        Order *order = headOrder;
        while (order)
        {
            if (order->id == id && order->username == username && (order->status == OPEN || order->status == PARTIAL_MATCH))
            {
                double nilaiSisa = order->sisaLot * order->harga * 100;

                if (order->tipe == BUY)
                {
                    user::tambahSaldo(username, nilaiSisa);
                    cout << "[✓] Saldo Rp " << nilaiSisa << " dikembalikan.\n";
                }
                else
                {
                    portfolio::tambahAtauUpdate(username, order->kodeSaham, order->sisaLot, order->harga);
                    cout << "[✓] " << order->sisaLot << " lot " << order->kodeSaham << " dikembalikan.\n";
                }

                order->status = CANCELLED;
                hapusDariAntrian(order);
                order::saveToCSV();
                cout << "[SUKSES] Order berhasil dibatalkan\n";
                return;
            }
            order = order->nextOrder;
        }
        cout << "[ERROR] Order tidak ditemukan\n";
    }
}