#include "avl.hpp"
#include "bst.hpp"
#include "red_black.hpp"
#include "splay.hpp"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
#include <vector>

template <typename TreeType>
void run_benchmark(std::string name, const std::vector<int>& data,
                   const std::vector<int>& search_data) {
    TreeType tree;

    std::cout << std::left << std::setw(15) << name;

    // 1. INSERT
    auto start = std::chrono::high_resolution_clock::now();
    for (int x : data) {
        tree.insert(x);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s | ";

    // 2. FIND
    start = std::chrono::high_resolution_clock::now();
    for (int x : search_data) {
        tree.find(x);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s | ";

    // 3. REMOVE
    start = std::chrono::high_resolution_clock::now();
    for (int x : search_data) {
        tree.remove(x);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s"
              << std::endl;
}

template <typename TreeType>
void test_tree_logic(std::string name) {
    std::cout << "Testowanie: " << name << "... ";
    TreeType tree;

    // 1. Test wstawiania i wyszukiwania
    std::vector<int> values = {50, 30, 70, 20, 40, 60, 80};
    for (int v : values) {
        tree.insert(v);
    }

    for (int v : values) {
        assert(tree.find(v) == true);
    }
    assert(tree.find(100) == false);
    assert(tree.find(0) == false);

    // 2. Test usuwania liścia
    tree.remove(20);
    assert(tree.find(20) == false);
    assert(tree.find(50) == true); // reszta musi zostać

    // 3. Test usuwania węzła z jednym dzieckiem
    tree.remove(30);
    assert(tree.find(30) == false);
    assert(tree.find(40) == true);

    // 4. Test usuwania węzła z dwójką dzieci (korzeń lub środek)
    tree.remove(50);
    assert(tree.find(50) == false);
    assert(tree.find(60) == true);
    assert(tree.find(70) == true);

    // 5. Test dużej ilości danych (sprawdzenie stabilności)
    for (int i = 1000; i < 2000; ++i)
        tree.insert(i);
    for (int i = 1000; i < 2000; ++i)
        assert(tree.find(i) == true);
    for (int i = 1000; i < 2000; ++i)
        tree.remove(i);
    for (int i = 1000; i < 2000; ++i)
        assert(tree.find(i) == false);

    std::cout << "PASSED" << std::endl;
}

void test_splay_specific() {
    std::cout << "Testowanie specyfiki Splay Tree... ";
    SplayTree<int> tree;

    // Splay powinien przenosić ostatnio wyszukiwany element do korzenia
    // (Można to sprawdzić debugerem, tutaj sprawdzamy tylko poprawność logiczną)
    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    assert(tree.find(10) == true);
    tree.remove(10);
    assert(tree.find(10) == false);

    std::cout << "PASSED" << std::endl;
}

int main() {
    const int N = 1'000'000;
    std::vector<int> data(N);
    std::iota(data.begin(), data.end(), 1);

    // Losujemy kolejność danych
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(data.begin(), data.end(), g);

    // Przygotowujemy dane do szukania
    std::vector<int> search_data = data;
    std::shuffle(search_data.begin(), search_data.end(), g);

    std::cout << "Benchmark dla N = " << N << " (dane losowe)\n";
    std::cout
        << "-------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(15) << "Struktura" << std::setw(18) << "Insert"
              << std::setw(18) << "Find" << std::setw(18) << "Remove" << std::endl;
    std::cout
        << "-------------------------------------------------------------------------------\n";

    run_benchmark<BST<int>>("BST", data, search_data);
    run_benchmark<SplayTree<int>>("Splay", data, search_data);
    run_benchmark<AVL<int>>("AVL", data, search_data);
    run_benchmark<RedBlackTree<int>>("Red-Black", data, search_data);

    return 0;
}
