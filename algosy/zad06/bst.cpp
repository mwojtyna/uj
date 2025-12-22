#include <cstdlib>
#include <iostream>

#define ASSERT(cond, msg)                                                                          \
    do {                                                                                           \
        if (!(cond)) {                                                                             \
            std::cerr << "ASSERT FAILED: " << msg << std::endl;                                    \
            std::exit(1);                                                                          \
        }                                                                                          \
    } while (0)

template <typename T>
struct BSTNode {
    BSTNode(T val) {
        this->val = val;
    }

    T val;
    BSTNode<T>* left = nullptr;
    BSTNode<T>* right = nullptr;
};

template <typename T>
void insert(T val, BSTNode<T>* root) {
    if (val < root->val) {
        if (root->left != nullptr) {
            insert(val, root->left);
        } else {
            root->left = new BSTNode<T>(val);
            return;
        }
    } else {
        if (root->right != nullptr) {
            insert(val, root->right);
        } else {
            root->right = new BSTNode<T>(val);
            return;
        }
    }
}

template <typename T>
BSTNode<T>* search(T val, BSTNode<T>* root) {
    if (val < root->val) {
        if (root->left == nullptr) {
            return nullptr;
        }
        return search(val, root->left);
    } else if (val > root->val) {
        if (root->right == nullptr) {
            return nullptr;
        }
        return search(val, root->right);
    } else {
        return root;
    }
}

template <typename T>
BSTNode<T>* remove(T val, BSTNode<T>* root) {
    if (val < root->val) {
        root->left = remove(val, root->left);
    } else if (val > root->val) {
        root->right = remove(val, root->right);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            // 0 dzieci
            delete root;
            return nullptr;
        } else if (root->left == nullptr || root->right == nullptr) {
            // 1 dziecko
            if (root->left == nullptr) {
                BSTNode<T>* ret = root->right;
                delete root;
                return ret;
            }
            if (root->right == nullptr) {
                BSTNode<T>* ret = root->left;
                delete root;
                return ret;
            }
        } else {
            // 2 dzieci
            BSTNode<T>* next = root->right;
            while (next->left != nullptr) {
                next = next->left;
            }
            root->val = next->val;
            root->right = remove(root->val, root->right);
        }
    }

    return root;
}

// Dla testów
template <typename T>
bool isBST(BSTNode<T>* root, T min, T max) {
    if (!root) {
        return true;
    }
    if (root->val <= min || root->val >= max) {
        return false;
    }
    return isBST(root->left, min, root->val) && isBST(root->right, root->val, max);
}

template <typename T>
int countNodes(BSTNode<T>* root) {
    if (!root)
        return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    BSTNode<int>* root = new BSTNode<int>(5);
    insert(3, root);
    insert(2, root);
    insert(4, root);
    insert(6, root);
    insert(9, root);
    insert(8, root);
    insert(10, root);

    // ---- INSERT TEST ----
    ASSERT(isBST(root, -1000, 1000), "Tree is not a BST after insert");
    ASSERT(countNodes(root) == 8, "Incorrect node count after insert");

    // ---- SEARCH TEST ----
    ASSERT(search(5, root) != nullptr, "Search failed for existing key 5");
    ASSERT(search(2, root) != nullptr, "Search failed for existing key 2");
    ASSERT(search(10, root) != nullptr, "Search failed for existing key 10");
    ASSERT(search(7, root) == nullptr, "Search falsely found key 7");

    // ---- REMOVE LEAF ----
    root = remove(2, root);
    ASSERT(search(2, root) == nullptr, "Leaf removal failed");
    ASSERT(countNodes(root) == 7, "Node count wrong after leaf removal");
    ASSERT(isBST(root, -1000, 1000), "BST broken after leaf removal");

    // ---- REMOVE NODE WITH ONE CHILD ----
    root = remove(9, root);
    ASSERT(search(9, root) == nullptr, "One-child removal failed");
    ASSERT(countNodes(root) == 6, "Node count wrong after one-child removal");
    ASSERT(isBST(root, -1000, 1000), "BST broken after one-child removal");

    // ---- REMOVE NODE WITH TWO CHILDREN ----
    root = remove(5, root);
    ASSERT(search(5, root) == nullptr, "Two-child removal failed");
    ASSERT(countNodes(root) == 5, "Node count wrong after two-child removal");
    ASSERT(isBST(root, -1000, 1000), "BST broken after two-child removal");

    std::cout << "ALL TESTS PASSED\n";
    return 0;
}
