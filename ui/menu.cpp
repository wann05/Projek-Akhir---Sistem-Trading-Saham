#include <iostream>
#include "menu.h"
#include "beliSaham.h"
#include "../trading/portfolio.h"
#include "../user/user.h"
#include "../trading/stock.h"
#include "sektorSaham.h"
#include "filterSaham.h"
#include "cariSaham.h"
#include "jualSaham.h"
#include "../market/stockGraph.h"
#include "../trading/transaction.h"
#include "../ui/batalkanTransaksi.h"
#include "../utils/helper.h"
using namespace std;
using namespace portfolio;
using namespace user;
using namespace stock;
using namespace filterSaham;
using namespace cariSaham;
using namespace stockGraph;
using namespace transaksi;
using namespace batalkanTransaksi;
using namespace helper;

namespace menu
{
    void userMenu()
    {
        while (true)
        {
            int pilihan;
            cout << "\n";
            judul("SISTEM TRADING SAHAM", 30);
            cout << "1.  Beli Saham" << endl;
            cout << "2.  Jual Saham" << endl;
            cout << "3.  Lihat Portofolio" << endl;
            cout << "4.  Lihat Histori Transaksi" << endl;
            cout << "5.  Cari Saham" << endl;
            cout << "6.  Filter Saham" << endl;
            cout << "7.  Sektor Saham" << endl;
            cout << "8.  Batalkan Transaksi" << endl;
            cout << "9.  Lihat Relasi Saham" << endl;
            cout << "10. Tambahkan Saldo" << endl;
            cout << "11. Logout" << "\n"
                 << "\n";

            cout << "Pilihan : ";
            cin >> pilihan;
            cout << "\n";
            if (pilihan == 1)
                beliSaham();
            else if (pilihan == 2)
                jualSaham();
            else if (pilihan == 3)
                portfolio::lihatPortfolio(user::authUser.username);
            else if (pilihan == 4)
                transaksi::tampilHistori(user::authUser.username);
            else if (pilihan == 5)
                cariSaham::cariSaham();
            else if (pilihan == 6)
                filterSaham::filterSaham();
            else if (pilihan == 7)
                sektorSaham();
            else if (pilihan == 8)
                batalkanTransaksi::batalkanTransaksi(user::authUser.username);
            else if (pilihan == 9)
                stockGraph::relasiSaham();
            else if (pilihan == 10)
                user::tambahSaldoUser(user::authUser.username);
            else if (pilihan == 11)
            {
                cout << "[SUKSES] Anda berhasil Logout";
                break;
            }
            else
                cout << "Pilihan Anda Tidak Valid!";
        }
    }
}