#include <iostream>
#include "cariSaham.h"
#include "../utils/helper.h"
using namespace std;
using namespace helper;

namespace cariSaham
{
    TreeNode *root = nullptr;

    void buildBST()
    {
        clearTree(root);
        root = nullptr;
        for (int i = 0; i < stock::MAX_STOCK; i++)
        {
            stock::Stock *saham = stock::hashTable[i];
            while (saham)
            {
                root = insert(root, saham);
                saham = saham->next;
            }
        }
    }

    TreeNode *insert(TreeNode *root, stock::Stock *data)
    {
        if (root == nullptr)
            return new TreeNode{data, nullptr, nullptr};
        if (data->kode < root->data->kode)
            root->kiri = insert(root->kiri, data);
        else if (data->kode > root->data->kode)
            root->kanan = insert(root->kanan, data);
        return root;
    }

    TreeNode *search(TreeNode *root, string kode)
    {
        if (root == nullptr)
            return nullptr;
        if (kode == root->data->kode)
            return root;
        if (kode < root->data->kode)
            return search(root->kiri, kode);
        return search(root->kanan, kode);
    }

    void clearTree(TreeNode *node)
    {
        if (!node)
            return;
        clearTree(node->kiri);
        clearTree(node->kanan);
        delete node;
    }

    void cariSaham()
    {
        buildBST();
        string kode;
        judul("Cari Saham", 30);
        cout << "Masukkan kode saham : ";
        cin >> kode;
        helper::toUpperCase(kode);

        TreeNode *hasil = search(root, kode);
        if (hasil)
        {
            cout << endl;
            judul("INFORMASI SAHAM", 50);
            cout << "Kode Saham      : " << hasil->data->kode << "\n";
            cout << "Nama Perusahaan : " << hasil->data->nama << "\n";
            cout << "Sektor          : " << hasil->data->sektor << "\n";
            cout << "Harga Market    : Rp " << hasil->data->harga << "\n";
            cout << "ARA             : Rp " << hasil->data->high << "\n";
            cout << "ARB             : Rp " << hasil->data->low << "\n";
            cout << "Volume          : Rp " << hasil->data->volume << "\n";
            cout << "Perubahan       : " << hasil->data->perubahan << "%\n";
        }
        else
            cout << "\nSaham tidak ditemukan\n";
        cout << string(50, '=');
    }
}