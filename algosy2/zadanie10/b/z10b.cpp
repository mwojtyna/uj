#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <queue>
#include <ranges>
#include <vector>

// Adj list
using Graph = std::vector<std::vector<size_t>>;

Graph loadGraph(const std::filesystem::path& path) {
    std::ifstream file(path);
    if (!file) {
        throw std::runtime_error("Cannot open file: " + path.string());
    }

    std::vector<std::vector<size_t>> matrix;
    std::string line;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        std::vector<size_t> row;
        size_t value;

        size_t i = 0;
        while (iss >> value) {
            if (value == 1) {
                row.push_back(i);
            }
            i++;
        }

        matrix.push_back(std::move(row));
    }

    return matrix;
}

void dfs(const size_t v, std::vector<bool>& visited, const Graph& graph) {
    if (visited[v]) {
        return;
    }

    visited[v] = true;

    for (const size_t nb : graph[v]) {
        dfs(nb, visited, graph);
    }
}

bool isConnected(const Graph& graph) {
    Graph graphT(graph.size(), std::vector<size_t>());
    for (const size_t v : std::views::iota(0uz, graph.size())) {
        for (const size_t nb : graph[v]) {
            graphT[nb].push_back(v);
        }
    }

    std::vector<bool> visited(graph.size());
    std::vector<bool> visitedT(graph.size());

    dfs(0, visited, graph);
    dfs(0, visitedT, graphT);

    return !std::ranges::contains(visited, false) && !std::ranges::contains(visitedT, false);
}

void printResult(const Graph& g, std::string_view name) {
    std::println(std::cout, "Graf {} jest {}", name, isConnected(g) ? "spójny" : "niespójny");
}

int main() {
    const Graph h1 = loadGraph("h1.txt");
    const Graph h2 = loadGraph("h2.txt");
    const Graph h3 = loadGraph("h3.txt");

    printResult(h1, "h1");
    printResult(h2, "h2");
    printResult(h3, "h3");

    return 0;
}
