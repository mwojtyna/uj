#ifndef RED_BLACK_H
#define RED_BLACK_H

enum Color { RED, BLACK };

template <typename T>
class RedBlackTree {
private:
    struct Node {
        T data;
        Color color;
        Node *left, *right, *parent;
        Node(T val) : data(val), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;
    Node* TNULL;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != TNULL)
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != TNULL)
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            root = x;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void rbTransplant(Node* u, Node* v) {
        if (u->parent == nullptr) {
            root = v;
        } else if (u == u->parent->left) {
            u->parent->left = v;
        } else {
            u->parent->right = v;
        }
        v->parent = u->parent; // To jest bezpieczne, bo TNULL->parent może być nadpisany tymczasowo
    }

    Node* minimum(Node* node) {
        while (node->left != TNULL)
            node = node->left;
        return node;
    }

    void fixDelete(Node* x) {
        Node* s;
        // Dodany warunek x->parent != nullptr, aby uniknąć segfaulta na korzeniu
        while (x != root && x->color == BLACK && x->parent != nullptr) {
            if (x == x->parent->left) {
                s = x->parent->right;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    s = x->parent->right;
                }
                if (s->left->color == BLACK && s->right->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->right->color == BLACK) {
                        s->left->color = BLACK;
                        s->color = RED;
                        rightRotate(s);
                        s = x->parent->right;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                s = x->parent->left;
                if (s->color == RED) {
                    s->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    s = x->parent->left;
                }
                if (s->right->color == BLACK && s->left->color == BLACK) {
                    s->color = RED;
                    x = x->parent;
                } else {
                    if (s->left->color == BLACK) {
                        s->right->color = BLACK;
                        s->color = RED;
                        leftRotate(s);
                        s = x->parent->left;
                    }
                    s->color = x->parent->color;
                    x->parent->color = BLACK;
                    s->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

    void fixInsert(Node* k) {
        Node* u;
        while (k->parent && k->parent->color == RED) {
            if (k->parent == k->parent->parent->right) {
                u = k->parent->parent->left;
                if (u && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->left) {
                        k = k->parent;
                        rightRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    leftRotate(k->parent->parent);
                }
            } else {
                u = k->parent->parent->right;
                if (u && u->color == RED) {
                    u->color = BLACK;
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    k = k->parent->parent;
                } else {
                    if (k == k->parent->right) {
                        k = k->parent;
                        leftRotate(k);
                    }
                    k->parent->color = BLACK;
                    k->parent->parent->color = RED;
                    rightRotate(k->parent->parent);
                }
            }
            if (k == root)
                break;
        }
        root->color = BLACK;
    }

    void clear(Node* node) {
        if (node != nullptr && node != TNULL) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

public:
    RedBlackTree() {
        TNULL = new Node(0);
        TNULL->color = BLACK;
        TNULL->left = TNULL->right = TNULL->parent = nullptr;
        root = TNULL;
    }

    ~RedBlackTree() {
        clear(root);
        delete TNULL;
    }

    void insert(T key) {
        Node* node = new Node(key);
        node->parent = nullptr;
        node->left = TNULL;
        node->right = TNULL;
        node->color = RED;

        Node* y = nullptr;
        Node* x = this->root;

        while (x != TNULL) {
            y = x;
            if (node->data < x->data)
                x = x->left;
            else
                x = x->right;
        }

        node->parent = y;
        if (y == nullptr)
            root = node;
        else if (node->data < y->data)
            y->left = node;
        else
            y->right = node;

        if (node->parent == nullptr) {
            node->color = BLACK;
            return;
        }
        if (node->parent->parent == nullptr)
            return;

        fixInsert(node);
    }

    void remove(T key) {
        Node* z = TNULL;
        Node* curr = root;

        while (curr != TNULL) {
            if (curr->data == key) {
                z = curr;
                break;
            }
            if (key < curr->data)
                curr = curr->left;
            else
                curr = curr->right;
        }

        if (z == TNULL)
            return;

        Node* x;
        Node* y = z;
        Color y_original_color = y->color;

        if (z->left == TNULL) {
            x = z->right;
            rbTransplant(z, z->right);
        } else if (z->right == TNULL) {
            x = z->left;
            rbTransplant(z, z->left);
        } else {
            y = minimum(z->right);
            y_original_color = y->color;
            x = y->right;
            if (y->parent == z) {
                x->parent = y; // Ważne połączenie powrotne dla fixDelete
            } else {
                rbTransplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            rbTransplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }

        delete z;

        if (y_original_color == BLACK) {
            fixDelete(x);
        }
    }

    bool find(T key) {
        Node* curr = root;
        while (curr != TNULL) {
            if (key == curr->data)
                return true;
            curr = (key < curr->data) ? curr->left : curr->right;
        }
        return false;
    }
};

#endif
