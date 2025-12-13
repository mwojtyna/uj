#include <array>
#include <cassert>
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
public:
    virtual ~Queue() = default;

    virtual void enqueue(T x) = 0;
    virtual T dequeue() = 0;
    virtual T getFront() = 0;
    virtual T getRear() = 0;
    virtual size_t getSize() = 0;
};

template <typename T, size_t C>
class ArrayQueue : public Queue<T> {
public:
    virtual void enqueue(T x) override {
        if (this->size == C) {
            throw std::out_of_range("Queue is full");
        }

        size_t rear = (this->front + this->size) % C;
        this->data[rear] = x;
        this->size++;
    }
    virtual T dequeue() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        T res = this->data[this->front];
        this->front = (this->front + 1) % C;
        this->size--;
        return res;
    }
    virtual T getFront() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        return this->data[this->front];
    }
    virtual T getRear() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        size_t rear = (this->front + this->size - 1) % C;
        return this->data[rear];
    }
    virtual size_t getSize() override {
        return this->size;
    }

private:
    size_t front = 0;
    size_t size = 0;
    std::array<T, C> data;
};

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
class PointerQueue : public Queue<T> {
public:
    PointerQueue() {
        this->front->next = this->rear;
        this->rear->next = this->front;
    }

    virtual void enqueue(T x) override {
        ListNode<T>* node = new ListNode<T>(x);
        ListNode<T>* last = this->rear->next;
        last->next = node;
        this->rear->next = node;
        this->size++;
    }
    virtual T dequeue() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }

        ListNode<T>* first = this->front->next;
        this->front->next = first->next;

        T val = first->val;
        delete first;
        this->size--;

        return val;
    }
    virtual T getFront() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }
        return this->front->next->val;
    }
    virtual T getRear() override {
        if (this->size == 0) {
            throw std::out_of_range("Queue is empty");
        }
        return this->rear->next->val;
    }
    virtual size_t getSize() override {
        return this->size;
    }

private:
    ListNode<T>* front = new ListNode<T>();
    ListNode<T>* rear = new ListNode<T>();
    size_t size = 0;
};

void testQueue(Queue<int>* q) {
    std::cout << "Test 1: new queue is empty\n";
    assert(q->getSize() == 0);

    std::cout << "Test 2: enqueue elements\n";
    q->enqueue(10);
    q->enqueue(20);
    q->enqueue(30);

    assert(q->getSize() == 3);
    assert(q->getFront() == 10);
    // rear should be last inserted
    assert(q->getRear() == 30);

    std::cout << "Test 3: dequeue preserves FIFO\n";
    assert(q->dequeue() == 10);
    assert(q->dequeue() == 20);
    assert(q->getFront() == 30);
    assert(q->getSize() == 1);

    std::cout << "Test 4: wrap-around behavior\n";
    q->enqueue(40);
    q->enqueue(50);
    q->enqueue(60);
    q->enqueue(70); // queue now full

    assert(q->getSize() == 5);
    assert(q->getFront() == 30);
    assert(q->getRear() == 70);

    std::cout << "Test 5: dequeue after wrap-around\n";
    assert(q->dequeue() == 30);
    assert(q->dequeue() == 40);
    assert(q->getFront() == 50);

    std::cout << "Test 6: dequeue until empty\n";
    q->dequeue(); // 50
    q->dequeue(); // 60
    q->dequeue(); // 70
    assert(q->getSize() == 0);

    std::cout << "Test 7: dequeue from empty queue throws\n";
    try {
        q->dequeue();
        assert(false); // should not reach here
    } catch (const std::out_of_range&) {
        // expected
    }

    std::cout << "All tests passed.\n";
}

int main() {
    Queue<int>* arrQ = new ArrayQueue<int, 5>();
    Queue<int>* listQ = new PointerQueue<int>();

    std::cout << "Testing array queue...\n";
    testQueue(arrQ);
    std::cout << "\nTesting pointer queue...\n";
    testQueue(listQ);

    delete arrQ;
    delete listQ;

    return 0;
}
