#pragma once

#include <vector>

class SimpleSet {
public:
    SimpleSet(int N);

    void add(SimpleSet a);
    void intersection(SimpleSet a);
    void difference(SimpleSet a);

    void insert(int x);
    void remove(int x);
    bool contains(int x);

private:
    std::vector<bool> m_Array;
};
