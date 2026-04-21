#pragma once

#include "../../zadanie01/b/z01b.hpp" // include SetLinked
#include <stdexcept>

using num_t = size_t;

class PriorityQueue {
public:
    PriorityQueue(num_t n) : m_Set() {}

    void insert(num_t x) {
        m_Set.insert(x);
    }

    num_t pop() {
        if (m_Set.getSize() == 0) {
            throw std::runtime_error("Próbowano usunąć element z pustej kolejki");
        }

        num_t smallest = *m_Set.begin();
        m_Set.remove(smallest);
        return smallest;
    }

private:
    SetLinked m_Set;
};
