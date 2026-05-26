# Sistem Trading Saham C++

Aplikasi terminal berbasis C++ untuk simulasi trading saham dengan fitur login, transaksi saham, portofolio, histori transaksi, filter saham, dan relasi saham.

## Fitur
- Login & Register
- Trading PIN
- Beli saham
- Jual saham
- Lihat portofolio
- Histori transaksi
- Cari saham
- Filter saham
  - Top Value
  - Top Volume
  - Top Gainers
  - Top Losers
- Sektor saham
- Batalkan transaksi
- Relasi saham
- Isi saldo

## Sektor Saham
- Energy
- Healthcare
- Industrial
- Technology
- Transportation
- Property
- Finance
- Infrastructure

## Struktur Data
- Hash Table
- Binary Search Tree (BST)
- Graph
- Stack
- Queue
- Sorting Algorithm

## Penyimpanan Data
Menggunakan file CSV:
- users.csv
- stocks.csv
- portfolios.csv
- transactions.csv
- orders.csv
- relasi.csv

## Compile
g++ main.cpp .\auth\Login.cpp .\auth\Register.cpp .\ui\General.cpp .\user\User.cpp .\utils\helper.cpp .\ui\Menu.cpp .\trading\Stock.cpp .\ui\BeliSaham.cpp .\trading\Portfolio.cpp .\ui\SektorSaham.cpp .\ui\FilterSaham.cpp .\ui\CariSaham.cpp .\trading\Order.cpp .\trading\Transaction.cpp .\ui\JualSaham.cpp .\market\StockGraph.cpp .\ui\BatalkanTransaksi.cpp -o app
