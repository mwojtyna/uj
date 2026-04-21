#include "./z03a.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <ratio>
#include <string>
#include <vector>

void printResult(const std::string& testName, bool condition) {
    std::cout << testName << ": " << (condition ? "PASS" : "FAIL") << '\n';
}

void testPopReturnsAscendingOrder() {
    std::cout << "\n=== testPopReturnsAscendingOrder ===\n";

    PriorityQueue q(10);
    q.insert(7);
    q.insert(2);
    q.insert(9);
    q.insert(1);
    q.insert(5);

    printResult("first pop returns minimum", q.pop() == 1);
    printResult("second pop returns next minimum", q.pop() == 2);
    printResult("third pop returns next minimum", q.pop() == 5);
    printResult("fourth pop returns next minimum", q.pop() == 7);
    printResult("fifth pop returns maximum", q.pop() == 9);
}

void testDuplicateInsertIsIgnored() {
    std::cout << "\n=== testDuplicateInsertIsIgnored ===\n";

    PriorityQueue q(10);
    q.insert(4);
    q.insert(4);
    q.insert(2);
    q.insert(2);
    q.insert(9);

    printResult("first unique element", q.pop() == 2);
    printResult("duplicate 2 was ignored", q.pop() == 4);
    printResult("duplicate 4 was ignored", q.pop() == 9);
}

void testInterleavedOperations() {
    std::cout << "\n=== testInterleavedOperations ===\n";

    PriorityQueue q(10);
    q.insert(8);
    q.insert(3);
    printResult("pop after two inserts", q.pop() == 3);

    q.insert(5);
    q.insert(1);
    printResult("new minimum after reinsertion", q.pop() == 1);
    printResult("remaining earlier value", q.pop() == 5);
    printResult("old maximum still present", q.pop() == 8);
}

void testPriorityFunction() {
    std::cout << "\n=== testPriorityFunction ===\n";

    PriorityQueue q(10);
    printResult("p(x) == x for 0", q.p(0) == 0);
    printResult("p(x) == x for 17", q.p(17) == 17);
    printResult("p(x) == x for 123456", q.p(123456) == 123456);
}

double timePerOperation(const std::chrono::high_resolution_clock::time_point& start,
                        const std::chrono::high_resolution_clock::time_point& end,
                        size_t operations = 1) {
    return std::chrono::duration<double, std::nano>(end - start).count() / operations;
}

std::vector<double> benchmark(num_t N) {
    std::vector<double> row = {static_cast<double>(N)};

    PriorityQueue q(N);
    // Descending inserts keep time linear instead of quadratic
    for (num_t value = N; value > 0; --value) {
        q.insert(value - 1);
    }

    auto start = std::chrono::high_resolution_clock::now();
    for (num_t i = 0; i < N; ++i) {
        q.pop();
    }
    auto end = std::chrono::high_resolution_clock::now();

    row.push_back(timePerOperation(start, end, N));
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
    testPopReturnsAscendingOrder();
    testDuplicateInsertIsIgnored();
    testInterleavedOperations();
    testPriorityFunction();

    std::vector<num_t> sizes = {1'000,     5'000,     10'000,    25'000,    50'000,
                                100'000,   250'000,   500'000,   1'000'000, 2'000'000,
                                3'000'000, 5'000'000, 10'000'000};
    std::vector<std::vector<double>> results;

    std::cout << "\nBenchmarking pop...\n";
    for (num_t N : sizes) {
        results.push_back(benchmark(N));
    }

    printResults(results);
    return 0;
}
