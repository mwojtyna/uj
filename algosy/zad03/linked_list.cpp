#include <cassert>
#include <iostream>

/*
    Implementacja listy wskaźnikowej z dodatkowym węzłem na początku (czyli pierwsza wartość to head->next->val)
*/

template <typename T>
class ListNode {
public:
    ListNode() = default;
    ListNode(T val) {
        this->val = val;
    }

    T val;
    ListNode* next = nullptr;
};

template <typename T>
ListNode<T>* init() {
    return new ListNode<T>();
}

// Dodaje wartość na początek listy.
template <typename T>
void insert(ListNode<T>* head, T val) {
    ListNode<T>* node = new ListNode<T>(val);
    node->next = head->next;
    head->next = node;
}

// Zwraca ListNode **przed** pierwszym ListNode który ma podaną wartość.
// Jeśli nie ma takiego ListNode, zwraca null.
template <typename T>
ListNode<T>* contains(ListNode<T>* head, T val) {
    ListNode<T>* cur = head;
    while (cur->next != nullptr) {
        if (cur->next->val == val) {
            return cur;
        }

        cur = cur->next;
    }

    return nullptr;
}

// Usuwa pierwszy ListNode z podaną wartością.
// Nie możemy nazwać funkcji "delete", bo jest to keyword w C++.
template <typename T>
void remove(ListNode<T>* head, T val) {
    ListNode<T>* node = contains(head, val);
    if (node == nullptr) {
        return;
    }

    ListNode<T>* after = node->next->next;
    delete node->next;
    node->next = after;
}

template <typename T>
ListNode<T>* merge(ListNode<T>* l1, ListNode<T>* l2) {
    ListNode<T>* head = new ListNode<T>();
    ListNode<T>* cur = head;

    while (l1 != nullptr && l2 != nullptr) {
        if (l1->val <= l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }

    if (l1 != nullptr) {
        cur->next = l1;
    }
    if (l2 != nullptr) {
        cur->next = l2;
    }

    return head->next;
}

template <typename T>
ListNode<T>* sort(ListNode<T>* head) {
    if (head->next == nullptr) {
        return head;
    }

    // Podziel listę na połowy
    ListNode<T>* prev = head;
    ListNode<T>* slow = head->next;
    ListNode<T>* fast = head->next;

    while (fast != nullptr && fast->next != nullptr) {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }

    prev->next = nullptr;

    // Posortuj każdą połowę
    ListNode<T>* l1 = sort(head);
    ListNode<T>* l2 = sort(slow);

    return merge(l1, l2);
}

int main() {
    // 4->3->2->1
    ListNode<int>* head = init<int>();
    insert(head, 1);
    insert(head, 2);
    insert(head, 3);
    insert(head, 4);
    assert(head->next->val == 4);

    // Sortuj (1->2->3->4)
    sort(head);

    // Sprawdź czy posortowane
    ListNode<int>* cur = head->next;
    for (int i = 1; i <= 4; i++) {
        assert(cur->val == i);
        cur = cur->next;
    }

    // 1->2->3->4
    //    ^
    //   node
    ListNode<int>* node = contains(head, 3);
    assert(node->next->val == 3);

    // 1->2->4
    remove(head, 3);
    assert(node->next->val == 4);

    std::cout << "Testy zakończyły się pomyślnie.\n";

    return 0;
}
