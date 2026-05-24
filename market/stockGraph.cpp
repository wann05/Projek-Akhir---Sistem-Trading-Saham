#include <iostream>
#include <fstream>
#include <sstream>
#include "stockGraph.h"
#include "../utils/helper.h"
#include "../trading/stock.h"
using namespace std;
using namespace helper;
using namespace stock;

namespace stockGraph
{
    GraphNode *graph = nullptr;

    GraphNode *cariAtauBuat(const string &kode)
    {
        GraphNode *node = cariNode(kode);
        if (node)
            return node;

        node = new GraphNode{kode, nullptr, graph};
        graph = node;

        return node;
    }

    GraphNode *cariNode(const string &kode)
    {
        GraphNode *curr = graph;
        while (curr)
        {
            if (curr->kode == kode)
                return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    void tambahRelasi(const string &a, const string &b)
    {
        GraphNode *sahamA = cariAtauBuat(a);
        GraphNode *sahamB = cariAtauBuat(b);

        RelasiNode *adjB = new RelasiNode{b, sahamA->subsidiary};
        sahamA->subsidiary = adjB;

        RelasiNode *adjA = new RelasiNode{a, sahamB->subsidiary};
        sahamB->subsidiary = adjA;
    }

    bool loadFromCSV()
    {
        clearGraph();

        ifstream file(DB_RELASI);
        if (!file.is_open())
        {
            cout << "File relasi tidak ditemukan\n";
            return false;
        }

        string line;
        while (getline(file, line))
        {
            if (line.empty())
                continue;

            string relasi[10];
            int relasiSize = 0;

            stringstream ss(line);
            string kode;

            while (getline(ss, kode, ','))
            {
                if (!kode.empty())
                    relasi[relasiSize++] = kode;
            }

            for (int i = 0; i < relasiSize; i++)
            {
                for (int j = i + 1; j < relasiSize; j++)
                {
                    tambahRelasi(relasi[i], relasi[j]);
                }
            }
        }

        file.close();
        return true;
    }

    void cariRelasi(const string &kode)
    {
        GraphNode *node = cariNode(kode);
        if (!node)
        {
            cout << "\nSaham " << kode << " tidak ditemukan dalam data relasi.\n";
            return;
        }

        RelasiNode *curr = node->subsidiary;
        if (!curr)
        {
            cout << "Tidak ada relasi ditemukan.\n";
            return;
        }

        int i = 1;
        judul("RELASI SAHAM " + kode, 50);
        kolom(5, "No");
        kolom(10, "Kode");
        kolom(35, "Emiten");
        cout << "\n"
             << string(50, '-') << "\n";
        while (curr)
        {
            stock::Stock *saham = stock::cariStock(curr->kode);

            kolom(5, to_string(i++) + ". ");
            kolom(10, curr->kode);
            if (saham)
                kolom(35, saham->nama);
            else
                kolom(35, "-");
            cout << "\n";
            curr = curr->next;
        }
        cout << string(50, '=');
    }

    void clearGraph()
    {
        GraphNode *curr = graph;
        while (curr)
        {
            RelasiNode *adj = curr->subsidiary;
            while (adj)
            {
                RelasiNode *tmpAdj = adj;
                adj = adj->next;
                delete tmpAdj;
            }

            GraphNode *tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        graph = nullptr;
    }

    void relasiSaham()
    {
        cout << "\n";
        judul("RELASI SAHAM", 50);
        string kode;
        cout << "Masukkan kode saham yang ingin Anda cari : ";
        cin >> kode;
        cout << "\n";
        helper::toUpperCase(kode);
        cariRelasi(kode);
    }

}