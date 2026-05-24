#pragma once
#include <iostream>
using namespace std;

#define DB_ORDER "./database/order.csv"

namespace order
{
    enum TipeOrder
    {
        BUY,
        SELL
    };

    enum StatusOrder
    {
        OPEN,
        MATCHED,
        PARTIAL_MATCH,
        CANCELLED
    };

    struct Order
    {
        string id;
        string username;
        TipeOrder tipe;
        string kodeSaham;
        int lot;
        int sisaLot;
        double harga;
        StatusOrder status;
        Order *nextOrder = nullptr;
        Order *nextQueue = nullptr;
    };

    extern Order *headOrder;
    extern Order *tailOrder;
    extern Order *frontAntri;
    extern Order *rearAntri;

    string tipeToString(TipeOrder tipe);
    string statusToString(StatusOrder status);
    TipeOrder stringToTipe(string s);
    StatusOrder stringToStatus(string s);
    string generateOrderID();

    void enqueue(Order *o);
    void hapusDariAntrian(Order *target);
    void buatOrder(string username, TipeOrder tipe, string kodeSaham, int lot, double harga);
    void prosesAntrian();
    bool loadFromCSV();
    void saveToCSV();
}