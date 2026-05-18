#include <algorithm>
#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// https://www.geeksforgeeks.org/cpp/how-to-create-an-unordered_map-of-pairs-in-c/
struct hash_node {
    template <class T1, class T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        // Hash the first element
        size_t hash1 = std::hash<T1>()(p.first);
        // Hash the second element
        size_t hash2 = std::hash<T2>()(p.second);
        // Combine the two hash values
        return hash1 ^ (hash2 + 0x9e3779b9 + (hash1 << 6) + (hash1 >> 2));
    }
};

using num_t = int32_t;
using Node = std::pair<num_t, num_t>;
using Graph = std::unordered_map<Node, std::vector<Node>, hash_node>;

std::vector<Node> directions = {{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
                                {1, -2},  {1, 2},  {2, -1},  {2, 1}};

Graph generateGraph(num_t boardSize) {
    Graph graph;

    for (num_t r = 0; r < boardSize; r++) {
        for (num_t c = 0; c < boardSize; c++) {
            const Node curNode = std::make_pair(r, c);

            for (const auto& [dr, dc] : directions) {
                const num_t nr = r + dr;
                const num_t nc = c + dc;

                if (nr >= 0 && nr < boardSize && nc >= 0 && nc < boardSize) {
                    graph[curNode].emplace_back(nr, nc);
                }
            }
        }
    }

    for (auto& [node, nbs] : graph) {
        std::ranges::sort(nbs,
                          [&graph](Node a, Node b) { return graph[a].size() < graph[b].size(); });
    }

    return graph;
}

bool backtrack(num_t r, num_t c, num_t boardSize, std::unordered_set<Node, hash_node>& visited,
               std::vector<Node>& cur, std::vector<Node>& res, Graph& graph) {
    if (visited.size() == boardSize * boardSize) {
        res = std::vector<Node>(cur);
        return true;
    }

    const Node curNode = std::make_pair(r, c);

    for (const Node& nb : graph[curNode]) {
        if (visited.contains(nb)) {
            continue;
        }

        visited.insert(nb);
        cur.push_back(nb);

        if (backtrack(nb.first, nb.second, boardSize, visited, cur, res, graph)) {
            return true;
        }

        cur.pop_back();
        visited.erase(nb);
    }

    return false;
}

std::vector<Node> knightTour(num_t startRow, num_t startCol, num_t boardSize) {
    Graph graph = generateGraph(boardSize);
    Node startNode = std::make_pair(startRow, startCol);

    std::unordered_set<Node, hash_node> visited;
    visited.insert(startNode);

    std::vector<Node> cur;
    cur.push_back(startNode);

    std::vector<Node> tour;

    backtrack(startRow, startCol, boardSize, visited, cur, tour, graph);

    return tour;
}

void printTour(const std::vector<Node>& tour) {
    std::cout << "[";
    for (size_t i = 0; i < tour.size(); i++) {
        auto [r, c] = tour[i];
        std::cout << "(" << r << ", " << c << ")";
        if (i + 1 != tour.size()) {
            std::cout << ", ";
        }
    }
    std::cout << "]\n";
}

int main() {
    std::vector<Node> tour = knightTour(0, 0, 8);
    if (tour.empty()) {
        std::cout << "Nie znaleziono trasy skoczka\n";
        return 1;
    }

    std::cout << "Znaleziono trasę skoczka o długości " << tour.size() << ":\n";
    printTour(tour);

    return 0;
}
