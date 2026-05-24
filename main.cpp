#include <iostream>
#include "user/user.h"
#include "ui/general.h"
#include "trading/stock.h"
#include "trading/portfolio.h"
#include "market/stockGraph.h"
#include "trading/order.h"
#include "trading/transaction.h"
using namespace std;
using namespace stock;
using namespace portfolio;
using namespace stockGraph;
using namespace order;
using namespace transaksi;
using namespace user;

bool initData()
{
    cout << "\n==== MEMUAT DATA APLIKASI ====" << endl;

    bool stockLoaded = stock::loadFromCSV();
    bool portfolioLoaded = portfolio::loadFromCSV();
    bool graphLoaded = stockGraph::loadFromCSV();
    bool orderLoaded = order::loadFromCSV();
    bool transactionLoaded = transaksi::loadFromCSV();
    bool usersLoaded = user::loadUsers();

    return stockLoaded && portfolioLoaded && graphLoaded && orderLoaded && transactionLoaded && usersLoaded;
}

int main()
{
    if (!initData())
    {
        cout << "\n[ERROR] Inisialisasi gagal. Program dihentikan.\n";
        return 0;
    }
    else
        cout << "[SUKSES] Data Berhasil Dimuat" << endl;

    general::authScreen();

    return 0;
}