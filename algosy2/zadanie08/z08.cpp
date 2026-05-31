#include <algorithm>
#include <fstream>
#include <iostream>
#include <print>
#include <ranges>
#include <vector>

using num_t = int32_t;
using Node = std::string;

struct Edge {
    size_t fromIdx;
    size_t toIdx;
    num_t weight;
};

struct Graph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};

Graph readFile(const std::string& filename) {
    std::ifstream file(filename);

    std::vector<Node> nodes;
    std::vector<Edge> edges;

    std::string line;
    while (std::getline(file, line)) {
        std::vector<std::string> split = line
                                         | std::views::split(' ')
                                         | std::views::transform([](auto&& str) {
                                               return std::string(str.begin(), str.end());
                                           })
                                         | std::ranges::to<std::vector>();

        Node from = std::move(split[0]);
        Node to = std::move(split[1]);
        num_t weight = std::stoi(split[2]);

        size_t fromIdx = std::distance(nodes.begin(), std::ranges::find(nodes, from));
        if (fromIdx == nodes.size()) {
            nodes.push_back(from);
            fromIdx = nodes.size() - 1;
        }

        size_t toIdx = std::distance(nodes.begin(), std::ranges::find(nodes, to));
        if (toIdx == nodes.size()) {
            nodes.push_back(to);
            toIdx = nodes.size() - 1;
        }

        edges.emplace_back(fromIdx, toIdx, weight);
    }

    return Graph{.nodes = std::move(nodes), .edges = std::move(edges)};
}

int main() {
    Graph graph = readFile("./czasy");

    constexpr num_t INF = std::numeric_limits<num_t>::max();
    std::vector<std::vector<num_t>> distances;
    distances.reserve(graph.nodes.size());
    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        distances.emplace_back(graph.nodes.size(), std::numeric_limits<num_t>::max());
    }

    for (const Edge& edge : graph.edges) {
        distances[edge.fromIdx][edge.toIdx] = edge.weight;
    }
    for (size_t v = 0; v < graph.nodes.size(); ++v) {
        distances[v][v] = 0;
    }
    for (size_t k = 0; k < graph.nodes.size(); ++k) {
        for (size_t i = 0; i < graph.nodes.size(); ++i) {
            for (size_t j = 0; j < graph.nodes.size(); ++j) {
                if (distances[i][j] == INF || distances[i][k] == INF || distances[k][j] == INF) {
                    continue;
                }

                num_t transitiveDist = distances[i][k] + distances[k][j];
                if (transitiveDist < distances[i][j]) {
                    distances[i][j] = transitiveDist;
                }
            }
        }
    }

    std::println("Czas:");
    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        for (size_t j = i + 1; j < graph.nodes.size(); ++j) {
            if (distances[i][j] == INF) {
                continue;
            }
            std::println("{} -> {}: {}", graph.nodes[i], graph.nodes[j], distances[i][j]);
        }
    }

    return 0;
}
