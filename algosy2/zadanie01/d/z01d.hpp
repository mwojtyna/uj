#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <string>
#include <vector>

using char50_t = const char (&)[51];
using num_t = std::uint32_t;

class SetChar50 {
public:
    void insert(char50_t x) {
        if (!contains(x)) {
            m_Array.push_back(x);
        }
    }

    void remove(char50_t x) {
        auto pos = std::find(m_Array.begin(), m_Array.end(), x);
        if (pos != m_Array.end()) {
            m_Array.erase(pos);
        }
    }

    bool contains(char50_t x) const {
        return std::find(m_Array.begin(), m_Array.end(), x) != m_Array.end();
    }

    num_t size() const {
        return m_Array.size();
    }

private:
    std::vector<std::string> m_Array;
};
