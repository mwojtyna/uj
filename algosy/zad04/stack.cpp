#include <cassert>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

template <typename T>
class Stack {
public:
    virtual ~Stack() = default;

    virtual void insert(T data) = 0;
    virtual T pop() = 0;
    virtual T peek() = 0;
    virtual size_t size() = 0;
};

template <typename T>
class ArrayStack : public Stack<T> {
public:
    virtual void insert(T data) override {
        this->data.emplace_back(data);
    }
    virtual T pop() override {
        if (this->data.empty()) {
            throw std::out_of_range("Stack is empty");
        }

        T val = this->data[this->data.size() - 1];
        this->data.pop_back();
        return val;
    }
    virtual T peek() override {
        if (this->data.empty()) {
            throw std::out_of_range("Stack is empty");
        }

        return this->data[this->data.size() - 1];
    }
    virtual size_t size() override {
        return this->data.size();
    }

private:
    std::vector<T> data;
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
class PointerStack : public Stack<T> {
public:
    virtual void insert(T data) override {
        ListNode<T>* node = new ListNode<T>(data);
        node->next = this->head->next;
        this->head->next = node;
        this->length++;
    }
    virtual T pop() override {
        if (this->head->next == nullptr) {
            throw std::out_of_range("Stack is empty");
        }

        ListNode<T>* next = this->head->next;
        T val = next->val;
        this->head->next = this->head->next->next;
        delete next;
        this->length--;

        return val;
    }
    virtual T peek() override {
        if (this->head->next == nullptr) {
            throw std::out_of_range("Stack is empty");
        }

        return this->head->next->val;
    }
    virtual size_t size() override {
        return this->length;
    }

private:
    ListNode<T>* head = new ListNode<T>();
    size_t length = 0;
};

double evaluateONP(std::vector<std::string> onp, Stack<double>* stack) {
    for (std::string token : onp) {
        if (token == "+") {
            double b = stack->pop();
            double a = stack->pop();
            stack->insert(a + b);
        } else if (token == "-") {
            double b = stack->pop();
            double a = stack->pop();
            stack->insert(a - b);
        } else if (token == "*") {
            double b = stack->pop();
            double a = stack->pop();
            stack->insert(a * b);
        } else if (token == "/") {
            double b = stack->pop();
            double a = stack->pop();
            if (b == 0) {
                throw std::runtime_error("Dzielenie przez 0");
            }
            stack->insert(a / b);
        } else {
            stack->insert((double)std::stoi(token));
        }
    }

    return stack->pop();
}

int main() {
    std::cout << "Podaj wyrażenie w ONP (tokeny oddzielone spacją):\n";

    std::string line;
    std::getline(std::cin, line);

    // Podziel po spacji
    std::stringstream ss(line);
    std::vector<std::string> onp;
    std::string tok;
    while (ss >> tok) {
        onp.push_back(tok);
    }

    Stack<double>* stack1 = new ArrayStack<double>();
    Stack<double>* stack2 = new PointerStack<double>();

    double res1 = evaluateONP(onp, stack1);
    double res2 = evaluateONP(onp, stack2);

    delete stack1;
    delete stack2;

    std::cout << "Wynik (ArrayStack):   " << res1 << "\n";
    std::cout << "Wynik (PointerStack): " << res2 << "\n";

    assert(res1 == res2);

    return 0;
}
