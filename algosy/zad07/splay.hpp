#pragma once

#include <iostream>

template <typename T>
struct SplayNode {
    T key;
    SplayNode<T>* left;
    SplayNode<T>* right;

    SplayNode(T key) {
        this->key = key;
        this->left = nullptr;
        this->right = nullptr;
    }
};

template <typename T>
class SplayTree {
private:
    SplayNode<T>* root = nullptr;

    SplayNode<T>* rotateRight(SplayNode<T>* x) {
        SplayNode<T>* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    SplayNode<T>* rotateLeft(SplayNode<T>* x) {
        SplayNode<T>* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Splay x to root
    SplayNode<T>* splay(SplayNode<T>* node, int x) {
        if (!node || node->key == x) {
            return node;
        }

        if (x < node->key) {
            if (!node->left) {
                return node;
            }

            if (x < node->left->key) {
                node->left->left = splay(node->left->left, x);
                node = rotateRight(node);
            } else if (x > node->left->key) {
                node->left->right = splay(node->left->right, x);
                if (node->left->right) {
                    node->left = rotateLeft(node->left);
                }
            }

            return node->left ? rotateRight(node) : node;
        } else {
            if (!node->right) {
                return node;
            }

            if (x > node->right->key) {
                node->right->right = splay(node->right->right, x);
                node = rotateLeft(node);
            } else if (x < node->right->key) {
                node->right->left = splay(node->right->left, x);
                if (node->right->left) {
                    node->right = rotateRight(node->right);
                }
            }

            return node->right ? rotateLeft(node) : node;
        }
    }

    void inorder(SplayNode<T>* node) const {
        if (!node) {
            return;
        }

        inorder(node->left);
        std::cout << node->key << " ";
        inorder(node->right);
    }

public:
    void insert(int x) {
        if (!this->root) {
            this->root = new SplayNode<T>(x);
            return;
        }

        this->root = splay(this->root, x);

        if (this->root->key == x) {
            // Ensure no duplicates
            return;
        }

        SplayNode<T>* node = new SplayNode<T>(x);
        if (x < this->root->key) {
            node->right = this->root;
            node->left = this->root->left;
            this->root->left = nullptr;
        } else {
            node->left = this->root;
            node->right = this->root->right;
            this->root->right = nullptr;
        }
        this->root = node;
    }

    bool find(int x) {
        this->root = splay(this->root, x);
        return this->root && this->root->key == x;
    }

    void remove(int x) {
        if (!this->root) {
            return;
        }

        this->root = splay(this->root, x);
        if (this->root->key != x) {
            return;
        }

        SplayNode<T>* tmp;
        if (!this->root->left) {
            tmp = this->root;
            this->root = this->root->right;
        } else {
            tmp = this->root;
            this->root = splay(this->root->left, x);
            this->root->right = tmp->right;
        }
        delete tmp;
    }

    void printInorder() const {
        inorder(this->root);
        std::cout << "\n";
    }
};
