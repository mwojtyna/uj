#include "../c/z05c.hpp"
#include <iostream>
#include <unordered_map>

bool isValid(num_t v, num_t c, const Graph& graph, std::unordered_map<num_t, num_t>& coloring) {
    for (const num_t nb : graph.neighbors(v)) {
        if (coloring.contains(nb) && coloring[nb] == c) {
            return false;
        }
    }
    return true;
}

bool checkColoring(num_t k, const Graph& graph, std::unordered_map<num_t, num_t>& coloring,
                   num_t v) {
    if (v == graph.getSize() + 1) {
        return true;
    }

    for (num_t c = 1; c <= k; c++) {
        if (isValid(v, c, graph, coloring)) {
            num_t prev = coloring[v];

            coloring[v] = c;
            if (checkColoring(k, graph, coloring, v + 1)) {
                return true;
            }
            coloring[v] = prev;
        }
    }

    return false;
}

int main() {
    Graph g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(1, 4);
    g.addEdge(4, 1);

    g.addEdge(2, 3);
    g.addEdge(3, 2);
    g.addEdge(2, 4);
    g.addEdge(4, 2);
    g.addEdge(2, 5);
    g.addEdge(5, 2);

    g.addEdge(3, 5);
    g.addEdge(5, 3);

    g.addEdge(4, 5);
    g.addEdge(5, 4);

    for (num_t k = 2; k <= g.getSize(); k++) {
        // vertex -> color
        std::unordered_map<num_t, num_t> coloring;

        if (checkColoring(k, g, coloring, 1)) {
            std::cout << "Najmniejsza liczba faz dla tego skrzyżowania wynosi " << k << "\n";
            return 0;
        }
    }

    return 0;
}
