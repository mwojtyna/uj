#pragma once

#include <cassert>
#include <cstddef>

using num_t = size_t;

struct Node {
    Node(num_t val, Node* next = nullptr) : val(val), next(next) {}
    num_t val;
    Node* next;
};

class SetLinked {
public:
    SetLinked() : m_Size(0), m_Head(new Node(0, nullptr)) {}
    ~SetLinked() {
        Node* cur = m_Head;
        while (cur) {
            Node* tmp = cur;
            cur = cur->next;
            delete tmp;
        }
    }

    SetLinked(const SetLinked&) = delete;
    SetLinked& operator=(const SetLinked&) = delete;

    SetLinked(SetLinked&& other) : m_Size(other.m_Size), m_Head(other.m_Head) {
        other.m_Size = 0;
        other.m_Head = new Node(0, nullptr);
    }
    SetLinked& operator=(SetLinked&& other) {
        if (this != &other) {
            Node* cur = m_Head;
            while (cur) {
                Node* tmp = cur;
                cur = cur->next;
                delete tmp;
            }

            m_Size = other.m_Size;
            m_Head = other.m_Head;

            other.m_Size = 0;
            other.m_Head = nullptr;
        }
        return *this;
    }

    SetLinked sum(const SetLinked& b) {
        SetLinked newSet;

        auto cur1 = m_Head;
        auto cur2 = b.m_Head;
        auto cur3 = newSet.m_Head;

        while (cur1->next && cur2->next) {
            if (cur1->next->val == cur2->next->val) {
                cur3->next = new Node(cur1->next->val);
                cur1 = cur1->next;
                cur2 = cur2->next;
            } else if (cur1->next->val < cur2->next->val) {
                cur3->next = new Node(cur1->next->val);
                cur1 = cur1->next;
            } else {
                cur3->next = new Node(cur2->next->val);
                cur2 = cur2->next;
            }

            cur3 = cur3->next;
            newSet.m_Size++;
        }

        while (cur1->next) {
            cur3->next = new Node(cur1->next->val);
            cur1 = cur1->next;
            cur3 = cur3->next;
            newSet.m_Size++;
        }

        while (cur2->next) {
            cur3->next = new Node(cur2->next->val);
            cur2 = cur2->next;
            cur3 = cur3->next;
            newSet.m_Size++;
        }

        return newSet;
    }

    SetLinked intersection(const SetLinked& b) {
        SetLinked newSet;
        if (m_Size == 0 || b.m_Size == 0) {
            return newSet;
        }

        auto cur1 = m_Head;
        auto cur2 = b.m_Head;
        auto cur3 = newSet.m_Head;

        while (cur1->next && cur2->next) {
            if (cur1->next->val == cur2->next->val) {
                cur3->next = new Node(cur1->next->val);
                cur1 = cur1->next;
                cur2 = cur2->next;
                cur3 = cur3->next;
                newSet.m_Size++;
            } else if (cur1->next->val < cur2->next->val) {
                cur1 = cur1->next;
            } else {
                cur2 = cur2->next;
            }
        }

        return newSet;
    }

    SetLinked difference(const SetLinked& b) {
        SetLinked newSet;

        auto cur1 = m_Head;
        auto cur2 = b.m_Head;
        auto cur3 = newSet.m_Head;

        while (cur1->next && cur2->next) {
            if (cur1->next->val == cur2->next->val) {
                cur1 = cur1->next;
                cur2 = cur2->next;
            } else if (cur1->next->val < cur2->next->val) {
                cur3->next = new Node(cur1->next->val);
                cur1 = cur1->next;
                cur3 = cur3->next;
                newSet.m_Size++;
            } else {
                cur2 = cur2->next;
            }
        }

        while (cur1->next) {
            cur3->next = new Node(cur1->next->val);
            cur1 = cur1->next;
            cur3 = cur3->next;
            newSet.m_Size++;
        }

        return newSet;
    }

    bool operator==(const SetLinked& b) const {
        if (m_Size != b.m_Size) {
            return false;
        }

        auto cur1 = m_Head;
        auto cur2 = b.m_Head;

        while (cur1->next && cur2->next) {
            if (cur1->next->val != cur2->next->val) {
                return false;
            }
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        return true;
    }

    void insert(num_t x) {
        auto cur = m_Head;
        while (cur->next && cur->next->val < x) {
            cur = cur->next;
        }

        // now cur is the last node with value smaller than x
        // cur->next->val >= x

        // stop if already contains the value
        if (cur->next && cur->next->val == x) {
            return;
        }

        cur->next = new Node(x, cur->next);
        m_Size++;
    }

    void remove(num_t x) {
        auto cur = m_Head;
        while (cur->next) {
            if (cur->next->val == x) {
                auto tmp = cur->next;
                cur->next = cur->next->next;
                delete tmp;
                m_Size--;
                return;
            }
            cur = cur->next;
        }
    }

    bool contains(num_t x) {
        auto cur = m_Head;
        while (cur->next) {
            if (cur->next->val == x) {
                return true;
            }
            cur = cur->next;
        }

        return false;
    }

    num_t getSize() const {
        return m_Size;
    }

private:
    num_t m_Size;
    Node* m_Head; // guard/dummy
};
