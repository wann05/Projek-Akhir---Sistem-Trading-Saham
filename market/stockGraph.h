#pragma once
#include <string>
using namespace std;
#define DB_RELASI "./database/relasi.csv"

namespace stockGraph
{
    struct RelasiNode
    {
        string kode;
        RelasiNode *next;
    };

    struct GraphNode
    {
        string kode;
        RelasiNode *subsidiary;
        GraphNode *next;
    };

    extern GraphNode *graph;

    bool loadFromCSV();
    void tambahRelasi(const string &a, const string &b);
    GraphNode *cariNode(const string &kode);
    void cariRelasi(const string &kode);
    void clearGraph();
    void relasiSaham();
}