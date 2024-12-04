#include <iostream>
#include <vector>
#include <cstdlib>

using namespace std;

struct TreeNode {
    int key;
    TreeNode* left;
    TreeNode* right;
    TreeNode* parent;

    TreeNode(int t) : key(t), left(nullptr), right(nullptr), parent(nullptr) {}
};

class BST {
public:
    TreeNode* root;

    BST() : root(nullptr) {}

    void insert(int t) {
        TreeNode* x = root;
        TreeNode* y = nullptr;
        TreeNode* z = new TreeNode(t);

        while (x != nullptr) {
            y = x;
            if (z->key < x->key) {
                x = x->left;
            } else {
                x = x->right;
            }
        }

        z->parent = y;
        z->left = nullptr;
        z->right = nullptr;

        if (y == nullptr) {
            root = z;
        } else if (z->key < y->key) {
            y->left = z;
        } else {
            y->right = z;
        }
    }
};

int height(TreeNode* node) {
    if (node == nullptr) {
        return -1;
    }
    return 1 + max(height(node->left), height(node->right));
}

int dhx(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }

    int lheight = height(node->left);
    int rheight = height(node->right);
    int subdhx = abs(lheight - rheight);

    int maxDhx = max(subdhx, max(dhx(node->left), dhx(node->right)));

    return maxDhx;
}

int main() {
    BST bst;

    int n;
    cin >> n;

    for (int i = 0; i < n; ++i) {
        int s;
        cin >> s;
        bst.insert(s);
    }

    int m = dhx(bst.root);
    cout << m << endl;

    return 0;
}