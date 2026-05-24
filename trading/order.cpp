#include "order.h"
#include "../trading/portfolio.h"
#include "../user/user.h"
#include "transaction.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace order
{
    Order *headOrder = nullptr;
    Order *tailOrder = nullptr;
    Order *frontAntri = nullptr;
    Order *rearAntri = nullptr;

    string tipeToString(TipeOrder tipe)
    {
        return (tipe == BUY) ? "BUY" : "SELL";
    }

    string statusToString(StatusOrder status)
    {
        if (status == OPEN)
            return "OPEN";
        if (status == MATCHED)
            return "MATCHED";
        if (status == PARTIAL_MATCH)
            return "PARTIAL_MATCH";
        return "CANCELLED";
    }

    TipeOrder stringToTipe(string tipe)
    {
        return (tipe == "BUY") ? BUY : SELL;
    }

    StatusOrder stringToStatus(string status)
    {
        if (status == "OPEN")
            return OPEN;
        if (status == "MATCHED")
            return MATCHED;
        if (status == "PARTIAL_MATCH")
            return PARTIAL_MATCH;
        return CANCELLED;
    }

    string generateOrderID()
    {
        int maxId = 0;
        Order *curr = headOrder;
        while (curr)
        {
            int id = stoi(curr->id);
            if (id > maxId)
                maxId = id;
            curr = curr->nextOrder;
        }
        return to_string(maxId + 1);
    }

    void enqueue(Order *order)
    {
        order->nextQueue = nullptr;
        if (!rearAntri)
            frontAntri = rearAntri = order;
        else
        {
            rearAntri->nextQueue = order;
            rearAntri = order;
        }
    }

    void hapusDariAntrian(Order *target)
    {
        Order *curr = frontAntri;
        Order *prev = nullptr;
        while (curr)
        {
            if (curr == target)
            {
                if (prev)
                    prev->nextQueue = curr->nextQueue;
                else
                    frontAntri = curr->nextQueue;
                if (curr == rearAntri)
                    rearAntri = prev;
                curr->nextQueue = nullptr;
                return;
            }
            prev = curr;
            curr = curr->nextQueue;
        }
    }

    void buatOrder(string username, TipeOrder tipe, string kodeSaham, int lot, double harga)
    {
        double totalNilai = lot * harga * 100;

        if (tipe == BUY)
            user::kurangiSaldo(username, totalNilai);
        else
            portfolio::kurangiLot(username, kodeSaham, lot);

        Order *orderBaru = new Order();
        orderBaru->id = generateOrderID();
        orderBaru->username = username;
        orderBaru->tipe = tipe;
        orderBaru->kodeSaham = kodeSaham;
        orderBaru->lot = lot;
        orderBaru->sisaLot = lot;
        orderBaru->harga = harga;
        orderBaru->status = OPEN;

        if (!headOrder)
            headOrder = tailOrder = orderBaru;
        else
        {
            tailOrder->nextOrder = orderBaru;
            tailOrder = orderBaru;
        }

        enqueue(orderBaru);
        cout << "\n[SUKSES] Order berhasil masuk ke antrian\n";
        prosesAntrian();
        saveToCSV();
    }

    void prosesAntrian()
    {
        Order *order = frontAntri;
        while (order)
        {
            Order *nextAntri = order->nextQueue;
            if (order->status != OPEN && order->status != PARTIAL_MATCH)
            {
                order = nextAntri;
                continue;
            }

            TipeOrder tipeLawan = (order->tipe == BUY) ? SELL : BUY;

            Order *lawan = frontAntri;
            while (lawan)
            {
                if (lawan != order &&
                    lawan->tipe == tipeLawan &&
                    lawan->kodeSaham == order->kodeSaham &&
                    lawan->harga == order->harga &&
                    lawan->username != order->username &&
                    (lawan->status == OPEN || lawan->status == PARTIAL_MATCH))
                {
                    int lotMatch = (order->sisaLot < lawan->sisaLot)
                                       ? order->sisaLot
                                       : lawan->sisaLot;

                    Order *buyer = (order->tipe == BUY) ? order : lawan;
                    Order *seller = (order->tipe == BUY) ? lawan : order;

                    double totalTransaksi = lotMatch * order->harga * 100;

                    portfolio::tambahAtauUpdate(buyer->username, buyer->kodeSaham, lotMatch, buyer->harga);
                    user::tambahSaldo(seller->username, totalTransaksi);

                    order->sisaLot -= lotMatch;
                    lawan->sisaLot -= lotMatch;

                    order->status = (order->sisaLot == 0) ? MATCHED : PARTIAL_MATCH;
                    lawan->status = (lawan->sisaLot == 0) ? MATCHED : PARTIAL_MATCH;

                    transaksi::catatTransaksi(buyer->username, "BUY", buyer->kodeSaham, lotMatch, buyer->harga);
                    transaksi::catatTransaksi(seller->username, "SELL", seller->kodeSaham, lotMatch, seller->harga);

                    if (order->status == MATCHED)
                        hapusDariAntrian(order);
                    if (lawan->status == MATCHED)
                        hapusDariAntrian(lawan);

                    saveToCSV();
                    if (order->status == MATCHED)
                        break;
                }
                lawan = lawan->nextQueue;
            }
            order = nextAntri;
        }
    }

    bool loadFromCSV()
    {
        Order *hapus = headOrder;
        while (hapus)
        {
            Order *next = hapus->nextOrder;
            delete hapus;
            hapus = next;
        }
        headOrder = nullptr;
        tailOrder = nullptr;
        frontAntri = nullptr;
        rearAntri = nullptr;

        ifstream fileCSV(DB_ORDER);
        if (!fileCSV.is_open())
        {
            cout << "[!] File order.csv tidak ditemukan\n";
            return false;
        }

        string line;
        while (getline(fileCSV, line))
        {
            if (line.empty())
                continue;
            stringstream ss(line);
            string id, username, tipe, kodeSaham, lot, sisaLot, harga, status;
            getline(ss, id, ',');
            getline(ss, username, ',');
            getline(ss, tipe, ',');
            getline(ss, kodeSaham, ',');
            getline(ss, lot, ',');
            getline(ss, sisaLot, ',');
            getline(ss, harga, ',');
            getline(ss, status, ',');

            Order *order = new Order();
            order->id = id;
            order->username = username;
            order->tipe = stringToTipe(tipe);
            order->kodeSaham = kodeSaham;
            order->lot = stoi(lot);
            order->sisaLot = stoi(sisaLot);
            order->harga = stod(harga);
            order->status = stringToStatus(status);

            if (!headOrder)
                headOrder = tailOrder = order;
            else
            {
                tailOrder->nextOrder = order;
                tailOrder = order;
            }
            if (order->status == OPEN || order->status == PARTIAL_MATCH)
                enqueue(order);
        }
        fileCSV.close();
        return true;
    }

    void saveToCSV()
    {
        ofstream fileCSV(DB_ORDER);
        Order *curr = headOrder;
        while (curr)
        {
            fileCSV << curr->id << ","
                    << curr->username << ","
                    << tipeToString(curr->tipe) << ","
                    << curr->kodeSaham << ","
                    << curr->lot << ","
                    << curr->sisaLot << ","
                    << curr->harga << ","
                    << statusToString(curr->status) << "\n";
            curr = curr->nextOrder;
        }
        fileCSV.close();
    }
}