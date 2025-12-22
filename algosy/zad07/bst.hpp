#pragma once

template <typename T>
class BST {
private:
    struct Node {
        T val;
        Node* left = nullptr;
        Node* right = nullptr;
        Node(T v) : val(v) {}
    };

    Node* root = nullptr;

    Node* insertHelper(Node* node, T val) {
        if (node == nullptr) {
            return new Node(val);
        }
        if (val < node->val) {
            node->left = insertHelper(node->left, val);
        } else if (val > node->val) {
            node->right = insertHelper(node->right, val);
        }
        return node;
    }

    Node* findHelper(Node* node, T val) {
        if (node == nullptr || node->val == val) {
            return node;
        }
        if (val < node->val) {
            return findHelper(node->left, val);
        }
        return findHelper(node->right, val);
    }

    Node* removeHelper(Node* node, T val) {
        if (node == nullptr)
            return nullptr;

        if (val < node->val) {
            node->left = removeHelper(node->left, val);
        } else if (val > node->val) {
            node->right = removeHelper(node->right, val);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            } else if (node->left == nullptr || node->right == nullptr) {
                Node* temp = (node->left == nullptr) ? node->right : node->left;
                delete node;
                return temp;
            } else {
                Node* next = node->right;
                while (next->left != nullptr)
                    next = next->left;
                node->val = next->val;
                node->right = removeHelper(node->right, node->val);
            }
        }
        return node;
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}
    ~BST() {
        clear(root);
    }

    void insert(T val) {
        root = insertHelper(root, val);
    }

    bool find(T val) {
        return findHelper(root, val) != nullptr;
    }

    void remove(T val) {
        root = removeHelper(root, val);
    }
};
