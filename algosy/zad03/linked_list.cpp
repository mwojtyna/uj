#include <cassert>
#include <iostream>
#include <vector>

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
class LinkedList {
public:
    LinkedList() {
        this->head = new ListNode<T>();
    }
    ~LinkedList() {
        ListNode<T>* cur = this->head;
        while (cur != nullptr) {
            ListNode<T>* next = cur->next;
            delete cur;
            cur = next;
        }
    }

    // Dodaje wartość na początek listy.
    void insert(T val) {
        ListNode<T>* node = new ListNode<T>(val);
        node->next = this->head->next;
        this->head->next = node;
        this->size++;
    }

    // Zwraca ListNode **przed** pierwszym ListNode który ma podaną wartość.
    // Jeśli nie ma takiego ListNode, zwraca null.
    ListNode<T>* search(T val) {
        ListNode<T>* cur = this->head;
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
    void remove(T val) {
        ListNode<T>* node = this->search(val);
        if (node == nullptr) {
            return;
        }

        ListNode<T>* after = node->next->next;
        delete node->next;
        node->next = after;
    }

    ListNode<T>* getHead() {
        return this->head;
    }

    size_t getSize() {
        return this->size;
    }

private:
    ListNode<T>* head;
    size_t size = 0;
};

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
    LinkedList<int> list = LinkedList<int>();
    list.insert(1);
    list.insert(2);
    list.insert(3);
    list.insert(4);
    assert(list.getHead()->next->val == 4);

    // Sortuj (1->2->3->4)
    sort(list.getHead());

    // Sprawdź czy posortowane
    std::vector<int> result;
    ListNode<int>* head = list.getHead();
    for (int i = 0; i < list.getSize(); i++) {
        result.emplace_back(head->next->val);
        head = head->next;
    }
    for (int i = 0; i < result.size(); i++) {
        assert(result[i] == i + 1);
    }

    // 1->2->3->4
    //    ^
    //   node
    ListNode<int>* node = list.search(3);
    assert(node->next->val == 3);

    // 1->2->4
    list.remove(3);
    assert(node->next->val == 4);

    std::cout << "Testy zakończyły się pomyślnie.\n";

    return 0;
}
