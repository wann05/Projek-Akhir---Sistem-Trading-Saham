#pragma once
#include "../trading/stock.h"
using namespace std;

namespace filterSaham
{
    void loadToArray();
    void insertionSort(stock::Stock *arr[], int size, string mode);
    void tampilHasil(string judul, string kolom);
    void filterSaham();
}