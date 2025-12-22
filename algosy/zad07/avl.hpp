#pragma once

#include <algorithm>

template <typename T>
class AVL {
private:
    struct Node {
        T data;
        Node *left, *right;
        int height;
        Node(T val) : data(val), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root = nullptr;

    int getHeight(Node* n) {
        return n ? n->height : 0;
    }
    int getBalance(Node* n) {
        return n ? getHeight(n->left) - getHeight(n->right) : 0;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
        return y;
    }

    Node* insert(Node* node, T key) {
        if (!node)
            return new Node(key);
        if (key < node->data)
            node->left = insert(node->left, key);
        else if (key > node->data)
            node->right = insert(node->right, key);
        else
            return node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        int balance = getBalance(node);

        if (balance > 1 && key < node->left->data)
            return rightRotate(node);
        if (balance < -1 && key > node->right->data)
            return leftRotate(node);
        if (balance > 1 && key > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && key < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current->left)
            current = current->left;
        return current;
    }

    Node* remove(Node* root, T key) {
        if (!root)
            return root;
        if (key < root->data)
            root->left = remove(root->left, key);
        else if (key > root->data)
            root->right = remove(root->right, key);
        else {
            if (!root->left || !root->right) {
                Node* temp = root->left ? root->left : root->right;
                if (!temp) {
                    temp = root;
                    root = nullptr;
                } else
                    *root = *temp;
                delete temp;
            } else {
                Node* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = remove(root->right, temp->data);
            }
        }
        if (!root)
            return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        return root;
    }

    void clear(Node* node) {
        if (node) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    ~AVL() {
        clear(root);
    }
    void insert(T key) {
        root = insert(root, key);
    }
    void remove(T key) {
        root = remove(root, key);
    }
    bool find(T key) {
        Node* curr = root;
        while (curr) {
            if (key == curr->data)
                return true;
            curr = (key < curr->data) ? curr->left : curr->right;
        }
        return false;
    }
};
