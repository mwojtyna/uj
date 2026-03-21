#include "./z01d.hpp"

#include <chrono>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

constexpr char kSamples[][51] = {
    "00000000000000000000000000000000000000000000000000",
    "00000000000000000000000000000000000000000000000001",
    "00000000000000000000000000000000000000000000000002",
    "00000000000000000000000000000000000000000000000003",
    "00000000000000000000000000000000000000000000000004",
    "00000000000000000000000000000000000000000000000005",
    "00000000000000000000000000000000000000000000000006",
    "00000000000000000000000000000000000000000000000007",
    "00000000000000000000000000000000000000000000000008",
    "00000000000000000000000000000000000000000000000009",
    "00000000000000000000000000000000000000000000000010",
    "00000000000000000000000000000000000000000000000011",
    "00000000000000000000000000000000000000000000000012",
    "00000000000000000000000000000000000000000000000013",
    "00000000000000000000000000000000000000000000000014",
    "00000000000000000000000000000000000000000000000015",
};
constexpr num_t kSampleCount = sizeof(kSamples) / sizeof(kSamples[0]);

char50_t sampleAt(num_t index) {
    return kSamples[index % kSampleCount];
}

void printResult(const std::string& testName, bool condition) {
    std::cout << testName << ": " << (condition ? "PASS" : "FAIL") << '\n';
}

void testInsertContains() {
    std::cout << "\n=== testInsertContains ===\n";

    SetChar50 s;
    s.insert(sampleAt(0));
    s.insert(sampleAt(1));
    s.insert(sampleAt(3));
    s.insert(sampleAt(8));

    printResult("contains sample 0", s.contains(sampleAt(0)));
    printResult("contains sample 1", s.contains(sampleAt(1)));
    printResult("contains sample 3", s.contains(sampleAt(3)));
    printResult("contains sample 8", s.contains(sampleAt(8)));
    printResult("does not contain sample 5", !s.contains(sampleAt(5)));
}

void testRemove() {
    std::cout << "\n=== testRemove ===\n";

    SetChar50 s;
    s.insert(sampleAt(0));
    s.insert(sampleAt(2));
    s.insert(sampleAt(4));
    s.remove(sampleAt(0));

    printResult("removed element is gone", !s.contains(sampleAt(0)));
    printResult("other element remains", s.contains(sampleAt(2)));
    printResult("second remaining element stays", s.contains(sampleAt(4)));

    s.remove(sampleAt(7));
    printResult("removing missing element does not break set", s.contains(sampleAt(2)));
}

void testSizeAndDuplicates() {
    std::cout << "\n=== testSizeAndDuplicates ===\n";

    SetChar50 s;
    s.insert(sampleAt(4));
    s.insert(sampleAt(4));
    s.insert(sampleAt(6));
    s.insert(sampleAt(9));
    s.insert(sampleAt(9));

    printResult("duplicate insert does not grow size", s.size() == 3);
    printResult("duplicate value still present", s.contains(sampleAt(4)));
    printResult("second unique value present", s.contains(sampleAt(6)));
    printResult("third unique value present", s.contains(sampleAt(9)));
}

double timePerOperation(const std::chrono::high_resolution_clock::time_point& start,
                        const std::chrono::high_resolution_clock::time_point& end,
                        size_t operations = 1) {
    return std::chrono::duration<double, std::milli>(end - start).count() / operations;
}

std::vector<double> benchmark(num_t N) {
    std::vector<double> row = {static_cast<double>(N)};

    SetChar50 s;

    auto start = std::chrono::high_resolution_clock::now();
    for (num_t i = 0; i < N; ++i) {
        s.insert(sampleAt(i));
    }
    auto end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end, N));

    start = std::chrono::high_resolution_clock::now();
    num_t hits = 0;
    for (num_t i = 0; i < N; ++i) {
        if (s.contains(sampleAt(i + 1))) {
            hits++;
        }
    }
    end = std::chrono::high_resolution_clock::now();
    row.push_back(timePerOperation(start, end, N));

    start = std::chrono::high_resolution_clock::now();
    for (num_t i = 0; i < N; ++i) {
        s.remove(sampleAt(i));
    }
    end = std::chrono::high_resolution_clock::now();
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
    testInsertContains();
    testRemove();
    testSizeAndDuplicates();

    std::vector<num_t> sizes = {1'000,     5'000,     10'000,    25'000,    50'000,
                                100'000,   500'000,   1'000'000, 2'000'000, 3'000'000,
                                4'000'000, 5'000'000, 7'500'000, 10'000'000};
    std::vector<std::vector<double>> results;

    std::cout << "\nBenchmarking...\n";
    for (num_t N : sizes) {
        results.push_back(benchmark(N));
    }

    printResults(results);
    return 0;
}
