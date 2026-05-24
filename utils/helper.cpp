#include "helper.h"
#include <iostream>
using namespace std;

namespace helper
{
    void generateUserID(int totalData, string *ID)
    {
        string num = to_string(totalData + 1);
        *ID = "ID-" + num;
    }

    void toUpperCase(string &text)
    {
        for (int i = 0; i < text.length(); i++)
        {
            text[i] = toupper(text[i]);
        }
    }

    string formatHarga(double harga)
    {
        stringstream ss;
        ss << fixed << setprecision(0) << harga;
        return "Rp " + ss.str();
    }

    void judul(string text, int lebar)
    {
        int padding = (lebar - text.length()) / 2;

        cout << string(lebar, '=') << endl;
        cout << string(padding, ' ') << text << endl;
        cout << string(lebar, '=') << endl;
    }
}