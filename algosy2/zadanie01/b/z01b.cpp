#include "./z01b.hpp"
#include <chrono>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

void printResult(const std::string& testName, bool condition) {
    std::cout << testName << ": " << (condition ? "PASS" : "FAIL") << std::endl;
}

void testInsertContains() {
    std::cout << "\n=== testInsertContains ===\n";
    SetLinked s;

    s.insert(3);
    s.insert(7);

    printResult("contains(3)", s.contains(3));
    printResult("contains(7)", s.contains(7));
    printResult("contains(5) == false", !s.contains(5));
}

void testRemove() {
    std::cout << "\n=== testRemove ===\n";
    SetLinked s;

    s.insert(4);
    s.remove(4);

    printResult("removed element not present", !s.contains(4));

    s.remove(8);
    printResult("removing non-existing doesn't break", !s.contains(8));
}

void testEquality() {
    std::cout << "\n=== testEquality ===\n";
    SetLinked a, b;

    a.insert(2);
    a.insert(5);

    b.insert(2);
    b.insert(5);

    printResult("equal sets", a == b);

    b.insert(7);
    printResult("not equal after change", !(a == b));
}

void testSum() {
    std::cout << "\n=== testSum (union) ===\n";
    SetLinked a, b;

    a.insert(1);
    a.insert(3);

    b.insert(3);
    b.insert(4);

    SetLinked c = a.sum(b);

    printResult("union contains 1", c.contains(1));
    printResult("union contains 3", c.contains(3));
    printResult("union contains 4", c.contains(4));
    printResult("union doesn't contain 2", !c.contains(2));
}

void testIntersection() {
    std::cout << "\n=== testIntersection ===\n";
    SetLinked a, b;

    a.insert(1);
    a.insert(2);
    a.insert(3);

    b.insert(2);
    b.insert(3);
    b.insert(4);

    SetLinked c = a.intersection(b);

    printResult("intersection contains 2", c.contains(2));
    printResult("intersection contains 3", c.contains(3));
    printResult("intersection doesn't contain 1", !c.contains(1));
    printResult("intersection doesn't contain 4", !c.contains(4));
}

void testDifference() {
    std::cout << "\n=== testDifference ===\n";
    SetLinked a, b;

    a.insert(1);
    a.insert(2);
    a.insert(3);

    b.insert(2);

    SetLinked c = a.difference(b);

    printResult("difference contains 1", c.contains(1));
    printResult("difference contains 3", c.contains(3));
    printResult("difference doesn't contain 2", !c.contains(2));
}

void testEdgeCases() {
    std::cout << "\n=== testEdgeCases ===\n";
    SetLinked s;

    // insert same element multiple times
    s.insert(2);
    s.insert(2);
    printResult("duplicate insert still present", s.contains(2));

    // boundary values
    s.insert(0);
    s.insert(4);

    printResult("contains 0", s.contains(0));
    printResult("contains max index", s.contains(4));

    // full set
    SetLinked full;
    full.insert(0);
    full.insert(1);
    full.insert(2);

    SetLinked empty;

    SetLinked diff = full.difference(full);
    printResult("full - full = empty", !diff.contains(0) && !diff.contains(1) && !diff.contains(2));

    SetLinked sum = full.sum(empty);
    printResult("full U empty = full", sum == full);
}

double timePerOperation(const std::chrono::high_resolution_clock::time_point& start,
                        const std::chrono::high_resolution_clock::time_point& end,
                        size_t operations = 1) {
    return std::chrono::duration<double, std::milli>(end - start).count() / operations;
}

std::vector<double> benchmark(num_t N) {
    std::vector<double> row = {static_cast<double>(N)};

    SetLinked a, b;

    // random generator
    std::mt19937 rng(42);
    std::uniform_int_distribution<num_t> dist(0, UINT64_MAX);

    // measure insert
    auto start = std::chrono::high_resolution_clock::now();
    for (num_t i = 0; i < N; i++) {
        a.insert(dist(rng));
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto insertMs = timePerOperation(start, end, N);

    // fill b
    for (num_t i = 0; i < N; i++) {
        b.insert(dist(rng));
    }

    // union
    start = std::chrono::high_resolution_clock::now();
    SetLinked u = a.sum(b);
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end));

    // intersection
    start = std::chrono::high_resolution_clock::now();
    SetLinked inter = a.intersection(b);
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end));

    // difference
    start = std::chrono::high_resolution_clock::now();
    SetLinked diff = a.difference(b);
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end));

    // equality
    start = std::chrono::high_resolution_clock::now();
    bool eq = (a == b);
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end));

    // insert
    row.push_back(insertMs);

    // remove
    start = std::chrono::high_resolution_clock::now();
    for (num_t i = 0; i < N; i++) {
        a.remove(dist(rng));
    }
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end, N));

    // contains
    start = std::chrono::high_resolution_clock::now();
    num_t hits = 0;
    for (num_t i = 0; i < N; i++) {
        if (a.contains(dist(rng))) {
            hits++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end, N));

    return row;
}

void printResults(std::vector<std::vector<double>> results, int precision = 8) {
    std::cout << std::fixed << std::setprecision(8);
    std::cout << "[\n";
    for (size_t i = 0; i < results.size(); i++) {
        std::cout << "  [";
        for (size_t j = 0; j < results[i].size(); j++) {
            std::cout << results[i][j];
            if (j + 1 < results[i].size()) {
                std::cout << ", ";
            }
        }
        std::cout << "]";
        if (i + 1 < results.size()) {
            std::cout << ",";
        }
        std::cout << "\n";
    }
    std::cout << "]\n";
}

int main() {
    testSum();
    testIntersection();
    testDifference();
    testEquality();
    testInsertContains();
    testRemove();
    testEdgeCases();

    std::vector<num_t> sizes = {1, 10, 100, 500, 1'000, 5'000, 10'000, 20'000, 30'000};
    std::vector<std::vector<double>> results;

    std::cout << "\nBenchmarking...\n";
    for (auto N : sizes) {
        results.push_back(benchmark(N));
    }

    printResults(results);

    return 0;
}
