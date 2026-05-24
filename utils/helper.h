#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

namespace helper
{
    void generateUserID(int totalData, string *outID);
    void toUpperCase(string &text);

    template <typename T>
    void kolom(int lebar, T value)
    {
        cout << left << setw(lebar) << value;
    }

    string formatHarga(double harga);
    void judul(string text, int lebar);

}