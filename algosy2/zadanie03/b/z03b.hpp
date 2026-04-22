#pragma once

#include "../../zadanie01/b/z01b.hpp"
#include <stdexcept>
#include <vector>

using num_t = size_t;

class PriorityQueue {
public:
    void insert(num_t x) {
        m_Arr.push_back(x);

        // heapify
        num_t i = m_Arr.size() - 1;
        while (i > 0 && !(m_Arr[(i - 1) / 2] <= m_Arr[i])) {
            num_t parent = (i - 1) / 2;

            num_t tmp = m_Arr[i];
            m_Arr[i] = m_Arr[parent];
            m_Arr[parent] = tmp;

            i = parent;
        }
    }

    num_t pop() {
        if (m_Arr.empty()) {
            throw std::runtime_error("Próbowano usunąć element z pustej kolejki");
        }

        num_t res = m_Arr[0];
        num_t last = m_Arr[m_Arr.size() - 1];

        // heapify
        num_t i = 0;
        while (2 * i + 1 < m_Arr.size()) {
            num_t child = 2 * i + 1;
            if (child + 1 < m_Arr.size() && m_Arr[child + 1] < m_Arr[child]) {
                child++;
            }
            if (m_Arr[child] >= last) {
                break;
            }

            m_Arr[i] = m_Arr[child];
            i = child;
        }

        m_Arr[i] = last;
        m_Arr.pop_back();

        return res;
    }

private:
    std::vector<num_t> m_Arr;
};
