#pragma once

#include <stdexcept>
#include <vector>

using num_t = size_t;

class SimpleSet {
public:
    SimpleSet(num_t N) : m_Array(N), m_Size(N) {}

    SimpleSet sum(const SimpleSet& b) {
        auto res = SimpleSet(this->m_Array.size());

        for (auto i = 0; i < m_Size; i++) {
            res.m_Array[i] = this->m_Array[i] || b.m_Array[i];
        }

        return res;
    }

    SimpleSet intersection(const SimpleSet& b) {
        auto res = SimpleSet(this->m_Array.size());

        for (auto i = 0; i < m_Size; i++) {
            res.m_Array[i] = this->m_Array[i] && b.m_Array[i];
        }

        return res;
    }

    SimpleSet difference(const SimpleSet& b) {
        auto res = SimpleSet(this->m_Array.size());

        for (auto i = 0; i < m_Size; i++) {
            res.m_Array[i] = this->m_Array[i] && !b.m_Array[i];
        }

        return res;
    }

    bool operator==(const SimpleSet& b) const {
        if (m_Size != b.m_Size) {
            return false;
        }

        for (auto i = 0; i < m_Size; i++) {
            if (m_Array[i] != b.m_Array[i]) {
                return false;
            }
        }

        return true;
    }

    void insert(num_t x) {
        if (x < 0 || x >= m_Size) {
            throw std::out_of_range("Element out of range");
        }

        m_Array[x] = true;
    }

    void remove(num_t x) {
        if (x < 0 || x >= m_Size) {
            throw std::out_of_range("Element out of range");
        }

        m_Array[x] = false;
    }

    bool contains(num_t x) {
        if (x < 0 || x >= m_Size) {
            throw std::out_of_range("Element out of range");
        }

        return m_Array[x];
    }

private:
    num_t m_Size;
    std::vector<bool> m_Array;
};
