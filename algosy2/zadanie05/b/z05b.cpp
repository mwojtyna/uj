#include "./z05b.hpp"

int main() {
    Graph g;
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 1);
    g.draw("graph.dot");

    return 0;
}
