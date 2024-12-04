#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
    long long key;
    TreeNode* left;
    TreeNode* right;
    int height;
    int size;

    TreeNode(long long k) : key(k), left(nullptr), right(nullptr), height(1), size(1) {}
};

class avltree {
private:
    TreeNode* root;

    int height(TreeNode* node) {
        return node ? node->height : 0;
    }

    int size(TreeNode* node) {
        return node ? node->size : 0;
    }

    int dhx(TreeNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    TreeNode* rrotate(TreeNode* y) {
        TreeNode* x = y->left;
        TreeNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        y->size = size(y->left) + size(y->right) + 1;
        x->size = size(x->left) + size(x->right) + 1;

        return x;
    }

    TreeNode* lrotate(TreeNode* x) {
        TreeNode* y = x->right;
        TreeNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        x->size = size(x->left) + size(x->right) + 1;
        y->size = size(y->left) + size(y->right) + 1;

        return y;
    }

    TreeNode* insert(TreeNode* node, long long key) {
        if (node == nullptr) {
            return new TreeNode(key);
        }

        if (key < node->key) {
            node->left = insert(node->left, key);
        } else if (key > node->key) {
            node->right = insert(node->right, key);
        }
        node->height = max(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
        int balance = dhx(node);
        if (balance > 1 && key < node->left->key)
            return rrotate(node);
        if (balance > 1 && key > node->left->key) {
            node->left = lrotate(node->left);
            return rrotate(node);
        }
        if (balance < -1 && key > node->right->key)
            return lrotate(node);
        if (balance < -1 && key < node->right->key) {
            node->right = rrotate(node->right);
            return lrotate(node);
        }

        return node;
    }

    TreeNode* findMin(TreeNode* node) {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    TreeNode* remove(TreeNode* node, long long key) {
        if (node == nullptr)
            return node;

        if (key < node->key) {
            node->left = remove(node->left, key);
        }
        else if (key > node->key) {
            node->right = remove(node->right, key);
        }
        else {
            if (node->left == nullptr || node->right == nullptr) {
                TreeNode* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    delete node;
                    return nullptr;
                }
                else {
                    *node = *temp;
                    delete temp;
                }
            }
            else {
                TreeNode* temp = findMin(node->right);
                node->key = temp->key;
                node->right = remove(node->right, temp->key);
            }
        }
        if (node == nullptr)
            return node;
        node->height = max(height(node->left), height(node->right)) + 1;
        node->size = size(node->left) + size(node->right) + 1;
        int balance = dhx(node);
        if (balance > 1 && dhx(node->left) >= 0)
            return rrotate(node);
        if (balance > 1 && dhx(node->left) < 0) {
            node->left = lrotate(node->left);
            return rrotate(node);
        }
        if (balance < -1 && dhx(node->right) <= 0)
            return lrotate(node);
        if (balance < -1 && dhx(node->right) > 0) {
            node->right = rrotate(node->right);
            return lrotate(node);
        }

        return node;
    }

    void findKth(TreeNode* node, int k, int& count, long long& result) {
        if (!node || count >= k)
            return;

        findKth(node->left, k, count, result);
        if (count < k) {
            count++;
            if (count == k) {
                result = node->key;
                return;
            }
            findKth(node->right, k, count, result);
        }
    }

    void sumK(TreeNode* node, int& k, long long& sum) {
        if (!node || k <= 0)
            return;

        sumK(node->left, k, sum);
        if (k > 0) {
            sum += node->key;
            k--;
            sumK(node->right, k, sum);
        }
    }

public:
    avltree() : root(nullptr) {}

    void Insert(long long key) {
        root = insert(root, key);
    }

    void Remove(long long key) {
        root = remove(root, key);
    }

    long long FindKth(int k) {
        int count = 0;
        long long result = -1;
        findKth(root, k, count, result);
        return result;
    }

    int Index(long long x) {
        TreeNode* current = root;
        int index = 0;

        while (current) {
            if (x < current->key) {
                current = current->left;
            }
            else {
                index += size(current->left) + 1;
                if (current->key == x)
                    break;
                current = current->right;
            }
        }
        return index;
    }

    long long Sum(int k) {
        long long sum = 0;
        sumK(root, k, sum);
        return sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    cin >> n;
    avltree avl;

    for (int i = 0; i < n; ++i) {
        int op;
        cin >> op;
        long long x;

        if (op == 1) {
            cin >> x;
            avl.Insert(x);
        }
        else if (op == 2) {
            cin >> x;
            avl.Remove(x);
        }
        else if (op == 3) {
            cin >> x;
            int k = static_cast<int>(x);
            cout << avl.FindKth(k) << endl;
        }
        else if (op == 4) {
            cin >> x;
            cout << avl.Index(x) << endl;
        }
        else if (op == 5) {
            cin >> x;
            int k = static_cast<int>(x);
            cout << avl.Sum(k) << endl;
        }
    }

    return 0;
}