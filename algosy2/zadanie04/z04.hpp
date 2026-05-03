#pragma once

#include <cstdint>
#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using num_t = int64_t;

// Directed graph implementation based on an adjacency matrix
class Graph {
public:
    Graph() : m_Matrix() {}

    num_t getSize() const {
        return m_Matrix.size();
    }

    bool adjacent(num_t x, num_t y) const {
        return m_Matrix[x][y] != -1;
    }

    std::unordered_set<num_t> neighbors(num_t x) const {
        std::unordered_set<num_t> res;
        for (num_t nb = 0; nb < getSize(); nb++) {
            if (m_Matrix[x][nb] != -1) {
                res.insert(nb);
            }
        }

        return res;
    }

    void addVertex(num_t x) {
        // x is already in the graph
        if (x < getSize()) {
            return;
        }

        // add rows
        num_t cols = getSize();
        for (num_t i = getSize(); i <= x; i++) {
            m_Matrix.emplace_back(cols, -1);
        }

        // add cols
        for (num_t i = 0; i < getSize(); i++) {
            m_Matrix[i].resize(x + 1, -1);
        }
    }

    void removeVertex(num_t x) {
        // x not in graph
        if (x >= getSize()) {
            throw std::out_of_range("Próbowano usunąć wierzchołek, którego nie ma w grafie!");
        }

        // x is the last vertex in the matrix
        if (x == getSize() - 1) {
            m_VertexValue.erase(x);
            m_Matrix.pop_back();
            for (std::vector<num_t>& row : m_Matrix) {
                row.pop_back();
            }
            return;
        }

        // x is somewhere in the middle of the matrix
        for (num_t k = 0; k < getSize(); k++) {
            m_Matrix[x][k] = -1;
            m_Matrix[k][x] = -1;
        }

        m_VertexValue.erase(x);
    }

    void addEdge(num_t x, num_t y) {
        setEdgeValue(x, y, 1);
    }

    void removeEdge(num_t x, num_t y) {
        setEdgeValue(x, y, -1);
    }

    num_t getVertexValue(num_t x) const {
        return m_VertexValue.at(x);
    }

    void setVertexValue(num_t x, num_t v) {
        m_VertexValue[x] = v;
    }

    num_t getEdgeValue(num_t x, num_t y) const {
        return m_Matrix[x][y];
    }

    void setEdgeValue(num_t x, num_t y, num_t v) {
        m_Matrix[x][y] = v;
    }

private:
    // m_Matrix[i][j] = -1 if no edge between i and j, else it contains the weight of the edge
    std::vector<std::vector<num_t>> m_Matrix;

    std::unordered_map<num_t, num_t> m_VertexValue;
};
