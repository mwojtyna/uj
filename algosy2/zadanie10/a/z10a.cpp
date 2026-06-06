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

bool isConnected(const Graph& graph) {
    std::vector<size_t> indegree(graph.size(), 0);
    for (const size_t v : std::views::iota(0uz, graph.size())) {
        for (const size_t nb : graph[v]) {
            indegree[nb]++;
        }
    }

    std::queue<size_t> queue;
    for (const auto& [v, indeg] : std::views::enumerate(indegree)) {
        if (indeg == 0) {
            queue.push(v);
        }
    }

    size_t visited = 0;
    while (!queue.empty()) {
        const size_t v = queue.front();
        queue.pop();
        visited++;

        for (size_t nb : graph[v]) {
            if (--indegree[nb] == 0) {
                queue.push(nb);
            }
        }
    }

    return visited != graph.size();
}

void printResult(const Graph& g, std::string_view name) {
    std::println(std::cout, "Graf {} jest {}", name, isConnected(g) ? "cykliczny" : "acykliczny");
}

int main() {
    const Graph g1 = loadGraph("g1.txt");
    const Graph g2 = loadGraph("g2.txt");
    const Graph g3 = loadGraph("g3.txt");

    printResult(g1, "g1");
    printResult(g2, "g2");
    printResult(g3, "g3");

    return 0;
}
