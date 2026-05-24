#include <iostream>
#include "filterSaham.h"
#include "../utils/helper.h"
using namespace std;
using namespace helper;

namespace filterSaham
{
    stock::Stock *arr[50];
    int arrSize = 0;

    void loadToArray()
    {
        arrSize = 0;
        for (int i = 0; i < stock::MAX_STOCK; i++)
        {
            stock::Stock *curr = stock::hashTable[i];
            while (curr)
            {
                arr[arrSize] = curr;
                arrSize++;
                curr = curr->next;
            }
        }
    }

    void insertionSort(stock::Stock *arr[], int size, string mode)
    {
        for (int i = 1; i < size; i++)
        {
            stock::Stock *index = arr[i];
            int j = i;
            while (j > 0)
            {
                bool pindah = false;
                if (mode == "nilai")
                    pindah = arr[j - 1]->nilai < index->nilai;
                else if (mode == "volume")
                    pindah = arr[j - 1]->volume < index->volume;
                else if (mode == "gainers")
                    pindah = arr[j - 1]->perubahan < index->perubahan;
                else if (mode == "losers")
                    pindah = arr[j - 1]->perubahan > index->perubahan;
                if (!pindah)
                    break;
                arr[j] = arr[j - 1];
                j--;
            }
            arr[j] = index;
        }
    }

    void tampilHasil(string jdl, string tipe)
    {
        judul(jdl, 60);
        kolom(5, "No");
        kolom(10, "Kode");
        kolom(30, "Nama");
        kolom(15, tipe);
        cout << "\n"
             << string(60, '-') << "\n";

        int tampil;
        if (arrSize < 10)
            tampil = arrSize;
        else
            tampil = 10;

        for (int i = 0; i < tampil; i++)
        {
            kolom(5, to_string(i + 1) + ".");
            kolom(10, arr[i]->kode);
            kolom(30, arr[i]->nama);
            if (tipe == "Value")
                cout << arr[i]->nilai;
            else if (tipe == "Volume")
                cout << arr[i]->volume;
            else
                cout << arr[i]->perubahan << "%";
            cout << "\n";
        }
        cout << string(60, '=') << "\n";
    }

    void filterSaham()
    {
        loadToArray();
        cout << "\n";
        judul("FILTER SAHAM", 25);
        cout << "1. Top Value\n";
        cout << "2. Top Volume\n";
        cout << "3. Top Gainers\n";
        cout << "4. Top Losers\n\n";
        cout << "Pilihan : ";

        int pilih;
        cin >> pilih;

        if (pilih == 1)
        {
            insertionSort(arr, arrSize, "nilai");
            tampilHasil("TOP VALUE", "Value");
        }
        else if (pilih == 2)
        {
            insertionSort(arr, arrSize, "volume");
            tampilHasil("TOP VOLUME", "Volume");
        }
        else if (pilih == 3)
        {
            insertionSort(arr, arrSize, "gainers");
            tampilHasil("TOP GAINERS", "Gainers");
        }
        else if (pilih == 4)
        {
            insertionSort(arr, arrSize, "losers");
            tampilHasil("TOP LOSERS", "Losers");
        }
        else
            cout << "Pilihan tidak valid\n";
    }
}