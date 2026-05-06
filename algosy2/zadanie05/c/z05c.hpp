#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>

using num_t = int64_t;

// https://www.geeksforgeeks.org/cpp/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_pair {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        // Hash the first element
        size_t hash1 = std::hash<T1>()(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>()(p.second);
        // Combine the two hash values
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

// Directed graph implementation based on an adjacency list
class Graph {
public:
    Graph() : m_Adj() {}

    num_t getSize() const {
        return m_Adj.size();
    }

    bool adjacent(num_t x, num_t y) const {
        return m_Adj.contains(x) && m_Adj.at(x).contains(y);
    }

    std::unordered_set<num_t> neighbors(num_t x) const {
        return m_Adj.at(x);
    }

    void addVertex(num_t x) {
        if (m_Adj.contains(x)) {
            return;
        }
        m_Adj[x] = {};
    }

    void removeVertex(num_t x) {
        if (!m_Adj.contains(x)) {
            throw std::out_of_range("Wierzchołka " + std::to_string(x) + " nie ma w grafie!");
        }

        m_Adj.erase(x);
        for (auto& [_, nbs] : m_Adj) {
            nbs.erase(x);
        }

        m_VertexValue.erase(x);
    }

    void addEdge(num_t x, num_t y) {
        m_Adj[x].insert(y);
        setEdgeValue(x, y, 1);
    }

    void removeEdge(num_t x, num_t y) {
        m_Adj[x].erase(y);
        m_EdgeLabel.erase({x, y});
    }

    num_t getVertexValue(num_t x) const {
        return m_VertexValue.at(x);
    }

    void setVertexValue(num_t x, num_t v) {
        m_VertexValue[x] = v;
    }

    num_t getEdgeValue(num_t x, num_t y) const {
        return m_EdgeLabel.at({x, y});
    }

    void setEdgeValue(num_t x, num_t y, num_t v) {
        m_EdgeLabel[{x, y}] = v;
    }

private:
    std::unordered_map<num_t, std::unordered_set<num_t>> m_Adj;

    std::unordered_map<std::pair<num_t, num_t>, num_t, hash_pair> m_EdgeLabel;
    std::unordered_map<num_t, num_t> m_VertexValue;
};
