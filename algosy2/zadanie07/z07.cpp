#include <iostream>
#include <limits>
#include <queue>
#include <ranges>
#include <unordered_map>
#include <vector>

using Node = std::string;
using num_t = int32_t;
struct Edge {
    Node into;
    num_t weight;
};
using Graph = std::unordered_map<Node, std::vector<Edge>>;

auto edgeComp = [](const Edge& a, const Edge& b) -> bool {
    // must be reversed because std::priority_queue returns the largest element
    return a.weight > b.weight;
};
std::vector<Node> nodes = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J"};

Graph createGraph() {
    Graph graph;
    graph["A"] = {{"B", 3}};
    graph["B"] = {{"A", 3}, {"C", 2}, {"D", 1}};
    graph["C"] = {{"B", 2}, {"H", 2}};
    graph["D"] = {{"B", 1}, {"E", 1}};
    graph["E"] = {{"D", 1}, {"F", 1}};
    graph["F"] = {{"E", 1}, {"G", 1}, {"H", 2}};
    graph["G"] = {{"F", 1}, {"H", 1}};
    graph["H"] = {{"C", 2}, {"G", 1}, {"F", 2}, {"I", 2}, {"J", 1}};
    graph["I"] = {{"H", 2}};
    graph["J"] = {{"H", 1}};
    return graph;
}

std::unordered_map<Node, num_t> dijkstra(const Graph& graph, const Node& from) {
    std::unordered_map<Node, num_t> distances;
    for (const auto& node : nodes) {
        distances[node] = std::numeric_limits<num_t>::max();
    }
    distances[from] = 0;

    std::priority_queue<Edge, std::vector<Edge>, decltype(edgeComp)> pq;
    pq.push({from, 0});

    while (!pq.empty()) {
        const auto [node, dist] = pq.top();
        pq.pop();

        for (const auto& [nb, nbDist] : graph.at(node)) {
            const num_t newDist = dist + nbDist;
            if (newDist < distances[nb]) {
                distances[nb] = newDist;
                pq.push({nb, newDist});
            }
        }
    }

    return distances;
}

void printDistances(const std::unordered_map<Node, num_t>& distances) {
    for (const auto& node : nodes) {
        std::cout << node << ": ";

        if (distances.at(node) == std::numeric_limits<num_t>::max()) {
            std::cout << "nieosiagalny";
        } else {
            std::cout << distances.at(node);
        }

        std::cout << '\n';
    }
}

int main() {
    const Graph graph = createGraph();

    std::cout << "Czas do klatki:\n";
    printDistances(dijkstra(graph, "A"));

    std::cout << "\nCzas do ubikacji:\n";
    printDistances(dijkstra(graph, "J"));

    std::cout << "\nCzas z aneksu kuchennego do pokoju szefa:\n"
              << dijkstra(graph, "I")["D"] << "\n";

    return 0;
}
