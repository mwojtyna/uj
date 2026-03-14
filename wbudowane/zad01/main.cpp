#include <cstdint>
#include <iostream>
#include <random>
#include <string>
#include <vector>

using edge_t = std::pair<std::uint32_t, std::uint32_t>; // (node, weight)

std::random_device rand_dev;
std::mt19937 generator(rand_dev());

uint32_t random(uint32_t range_from, uint32_t range_to) {
    std::uniform_int_distribution<uint32_t> dist(range_from, range_to);
    return dist(generator);
}

std::vector<std::vector<std::uint32_t>> generateDag(std::uint32_t nodesCount) {
    //
}

int main(int argc, char* argv[]) {
    if (argc > 5) {
        std::cout << "Za mało argumentów! Poprawne argumenty:\n";
        std::cout
            << "liczba_zadań liczba_procesorów_hc liczba_procesorów_pp liczba_szyn plik_wyjściowy";
    }

    std::uint32_t tasks, hcs, pps, buses;
    std::string outfile;

    tasks = std::stoi(argv[1]);
    pps = std::stoi(argv[2]);
    pps = std::stoi(argv[3]);
    pps = std::stoi(argv[4]);
    outfile = argv[5];

    return 0;
}
