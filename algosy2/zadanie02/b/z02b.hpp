#pragma once

#include <vector>

#include "../../zadanie01/b/z01b.hpp"

using num_t = size_t;

class SetHashed {
public:
    SetHashed(num_t N) : m_Buckets(N) {}

    SetHashed sum(const SetHashed& b) const {
        SetHashed newSet(m_Buckets.size());
        for (num_t i = 0; i < m_Buckets.size(); i++) {
            newSet.m_Buckets[i] = m_Buckets[i].sum(b.m_Buckets[i]);
        }
        return newSet;
    }

    SetHashed intersection(const SetHashed& b) const {
        SetHashed newSet(m_Buckets.size());
        for (num_t i = 0; i < m_Buckets.size(); i++) {
            newSet.m_Buckets[i] = m_Buckets[i].intersection(b.m_Buckets[i]);
        }
        return newSet;
    }

    SetHashed difference(const SetHashed& b) const {
        SetHashed newSet(m_Buckets.size());
        for (num_t i = 0; i < m_Buckets.size(); i++) {
            newSet.m_Buckets[i] = m_Buckets[i].difference(b.m_Buckets[i]);
        }
        return newSet;
    }

    bool operator==(const SetHashed& b) const {
        for (const SetLinked& bucket : m_Buckets) {
            for (num_t value : bucket) {
                if (!b.contains(value)) {
                    return false;
                }
            }
        }

        return true;
    }

    bool operator!=(const SetHashed& b) const {
        return !(*this == b);
    }

    void insert(num_t x) {
        m_Buckets[h(x)].insert(x);
    }

    void remove(num_t x) {
        m_Buckets[h(x)].remove(x);
    }

    bool contains(num_t x) const {
        return m_Buckets[h(x)].contains(x);
    }

private:
    // Hash function
    num_t h(num_t x) const {
        return x % m_Buckets.size();
    }

    std::vector<SetLinked> m_Buckets;
};
