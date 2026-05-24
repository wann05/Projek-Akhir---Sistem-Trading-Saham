#pragma once
#include "../trading/stock.h"
using namespace std;
using namespace stock;

namespace cariSaham
{
    struct TreeNode
    {
        stock::Stock *data;
        TreeNode *kiri;
        TreeNode *kanan;
    };

    extern TreeNode *root;
    void buildBST();
    TreeNode *insert(TreeNode *root, stock::Stock *data);
    TreeNode *search(TreeNode *root, string kode);
    void cariSaham();
    void clearTree(TreeNode *node);
}