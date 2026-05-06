#include "./z05c.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

void printResult(const std::string& testName, bool condition) {
    std::cout << testName << ": " << (condition ? "PASS" : "FAIL") << '\n';
}

void testRemoveLastVertex() {
    std::cout << "\n=== testRemoveLastVertex ===\n";

    Graph g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.setVertexValue(2, 42);

    g.removeVertex(2);

    printResult("size shrinks after removing vertex", g.getSize() == 2);
    printResult("existing edge is preserved", g.adjacent(0, 1));
    printResult("remaining reverse edge is still absent", !g.adjacent(1, 0));

    bool removedValueThrows = false;
    try {
        (void)g.getVertexValue(2);
    } catch (const std::out_of_range&) {
        removedValueThrows = true;
    }
    printResult("removed vertex value is erased", removedValueThrows);
}

void testRemoveMiddleVertex() {
    std::cout << "\n=== testRemoveMiddleVertex ===\n";

    Graph g;
    g.addVertex(0);
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addEdge(0, 1);
    g.addEdge(1, 0);
    g.addEdge(1, 2);
    g.addEdge(2, 1);
    g.addEdge(0, 3);
    g.addEdge(3, 0);
    g.setVertexValue(1, 99);

    g.removeVertex(1);

    printResult("outgoing edges from removed vertex are cleared",
                !g.adjacent(1, 0) && !g.adjacent(1, 2));
    printResult("incoming edges to removed vertex are cleared",
                !g.adjacent(0, 1) && !g.adjacent(2, 1));
    printResult("unrelated edges are preserved", g.adjacent(0, 3) && g.adjacent(3, 0));

    bool removedValueThrows = false;
    try {
        (void)g.getVertexValue(1);
    } catch (const std::out_of_range&) {
        removedValueThrows = true;
    }
    printResult("removed middle vertex value is erased", removedValueThrows);
}

void testRemoveMissingVertexThrows() {
    std::cout << "\n=== testRemoveMissingVertexThrows ===\n";

    Graph g;
    g.addVertex(1);

    bool threw = false;
    try {
        g.removeVertex(3);
    } catch (const std::out_of_range&) {
        threw = true;
    }

    printResult("removing non-existing vertex throws", threw);
}

double timePerOperation(const std::chrono::high_resolution_clock::time_point& start,
                        const std::chrono::high_resolution_clock::time_point& end,
                        size_t operations = 1) {
    return std::chrono::duration<double, std::nano>(end - start).count() / operations;
}

double average(const std::vector<double>& values) {
    double sum = 0.0;
    for (double value : values) {
        sum += value;
    }
    return sum / values.size();
}

std::vector<double> benchmarkAddOperation(num_t N, size_t trials) {
    std::vector<double> row = {static_cast<double>(N)};
    std::vector<double> measurements;
    measurements.reserve(trials);

    for (size_t trial = 0; trial < trials; trial++) {
        Graph g;
        auto start = std::chrono::high_resolution_clock::now();
        for (num_t i = 0; i < N; i++) {
            g.addVertex(i);
        }
        auto end = std::chrono::high_resolution_clock::now();

        measurements.push_back(timePerOperation(start, end, static_cast<size_t>(N)));
    }

    row.push_back(average(measurements));
    return row;
}

void printResults(const std::vector<std::vector<double>>& results, int precision = 8) {
    std::cout << std::fixed << std::setprecision(precision);
    std::cout << "[\n";
    for (size_t i = 0; i < results.size(); ++i) {
        std::cout << "  [";
        for (size_t j = 0; j < results[i].size(); ++j) {
            std::cout << results[i][j];
            if (j + 1 < results[i].size()) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i + 1 < results.size()) {
            std::cout << ",";
        }
        std::cout << '\n';
    }
    std::cout << "]\n";
}

int main() {
    testRemoveLastVertex();
    testRemoveMiddleVertex();
    testRemoveMissingVertexThrows();

    std::vector<num_t> sizes = {100, 250, 500, 1'000, 2'000, 3'000, 4'000, 5'000};
    constexpr size_t trials = 100;
    std::vector<std::vector<double>> results;

    std::cout << "\nBenchmarking average of " << trials << " trials...\n";
    std::cout << "Columns: N, addVertex ns/op\n";
    for (num_t N : sizes) {
        results.push_back(benchmarkAddOperation(N, trials));
    }

    printResults(results);
    return 0;
}
