#include "../c/z05c.hpp"

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

    g.draw("graph.dot");

    return 0;
}
