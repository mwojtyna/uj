#include <algorithm>
#include <chrono>
#include <iomanip>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <vector>

enum State { EMPTY, OCCUPIED, DELETED };

struct HashNode {
    int key;
    int value;
    State state;

    HashNode() : key(-1), value(-1), state(EMPTY) {}
};

class OpenAddressingHashTable {
public:
    OpenAddressingHashTable(int cap) : capacity(cap), size(0) {
        table.resize(capacity);
    }

    bool insert(int key, int value) {
        if (size >= capacity) {
            std::cout << "Tablica pełna!" << std::endl;
            return false;
        }

        int index = hashFunction(key);
        int startIndex = index;

        // Szukamy wolnego miejsca lub miejsca po usuniętym elemencie
        // Pętla zatrzymuje się, gdy znajdziemy miejsce lub gdy wrócimy do punktu wyjścia
        while (table[index].state == OCCUPIED) {
            // Aktualizacja istniejącego klucza, jeśli używamy insert() do aktualizacji
            if (table[index].key == key) {
                table[index].value = value;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) {
                return false; // Tablica pełna
            }
        }

        // Wstawiamy nowy element
        table[index].key = key;
        table[index].value = value;
        table[index].state = OCCUPIED;
        size++;
        return true;
    }

    int search(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index].state != EMPTY) {
            // Jeśli komórka jest zajęta i klucz pasuje
            if (table[index].state == OCCUPIED && table[index].key == key) {
                return table[index].value;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) {
                break;
            }
        }
        return -1;
    }

    bool remove(int key) {
        int index = hashFunction(key);
        int startIndex = index;

        while (table[index].state != EMPTY) {
            if (table[index].state == OCCUPIED && table[index].key == key) {
                table[index].state = DELETED;
                size--;
                return true;
            }
            index = (index + 1) % capacity;
            if (index == startIndex) {
                break;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            if (table[i].state == OCCUPIED) {
                std::cout << "[" << i << "]: " << table[i].key << "(" << table[i].value << ") ";
            } else if (table[i].state == DELETED) {
                std::cout << "[" << i << "]: DELETED ";
            } else {
                std::cout << "[" << i << "]: NULL ";
            }
        }
        std::cout << std::endl;
    }

private:
    std::vector<HashNode> table;
    int capacity;
    int size;

    int hashFunction(int key) {
        return key % capacity;
    }
};

class ChainingHashTable {
public:
    ChainingHashTable(int cap) : capacity(cap) {
        table.resize(capacity);
    }

    void insert(int key, int value) {
        int index = hashFunction(key);

        // Sprawdzamy, czy klucz już istnieje jeśli tak, aktualizujemy
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value;
                return;
            }
        }

        table[index].push_back({key, value});
    }

    int search(int key) {
        int index = hashFunction(key);

        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }
        return -1;
    }

    bool remove(int key) {
        int index = hashFunction(key);

        // Używamy iteratora żeby bezpiecznie usunąć element z listy
        auto& cellList = table[index];
        for (auto it = cellList.begin(); it != cellList.end(); ++it) {
            if (it->first == key) {
                cellList.erase(it);
                return true;
            }
        }
        return false;
    }

    void display() {
        for (int i = 0; i < capacity; i++) {
            std::cout << "[" << i << "]: ";
            for (const auto& pair : table[i]) {
                std::cout << "{" << pair.first << "," << pair.second << "} -> ";
            }
            std::cout << "NULL" << std::endl;
        }
    }

private:
    int capacity;
    // Wektor list wiązanych par o strukturze (klucz, wartość)
    std::vector<std::list<std::pair<int, int>>> table;

    int hashFunction(int key) {
        return key % capacity;
    }
};

template <typename HashTable>
void run_benchmark(std::string name, const std::vector<int>& data,
                   const std::vector<int>& search_data) {
    HashTable hashTable(data.size());

    std::cout << std::left << std::setw(20) << name;

    // 1. INSERT
    auto start = std::chrono::high_resolution_clock::now();
    for (int x : data) {
        hashTable.insert(x, x);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s | ";

    // 2. SEARCH
    start = std::chrono::high_resolution_clock::now();
    for (int x : search_data) {
        hashTable.search(x);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s | ";

    // 3. REMOVE
    start = std::chrono::high_resolution_clock::now();
    for (int x : search_data) {
        hashTable.remove(x);
    }
    end = std::chrono::high_resolution_clock::now();
    std::cout << std::setw(15) << std::chrono::duration<double>(end - start).count() << "s"
              << std::endl;
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

    run_benchmark<ChainingHashTable>("Łańcuchowanie", data, search_data);
    run_benchmark<OpenAddressingHashTable>("Adresowanie otwarte", data, search_data);

    return 0;
}
