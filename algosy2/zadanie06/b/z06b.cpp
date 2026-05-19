#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using Node = std::string;
using Graph = std::unordered_map<Node, std::vector<Node>>;

std::vector<std::string> readWords(const std::string& filename) {
    std::ifstream file(filename);

    std::vector<std::string> words;

    std::string line;
    while (std::getline(file, line)) {
        words.push_back(std::move(line));
    }

    return words;
}

std::vector<std::string> shortestPath(const std::string& startWord, const std::string& endWord,
                                      const std::vector<std::string>& words) {
    // word with wildcard -> normal word
    Graph graph;
    std::unordered_map<Node, Node> prev;

    for (const std::string& word : words) {
        for (size_t i = 0; i < word.size(); i++) {
            std::string left = word.substr(0, i);
            std::string right = word.substr(i + 1);
            graph[left + '*' + right].push_back(word);
        }
    }

    std::unordered_set<Node> visited;
    visited.insert(startWord);

    std::queue<Node> q;
    q.push(startWord);

    while (!q.empty()) {
        const Node word = q.front();
        q.pop();

        if (word == endWord) {
            break;
        }

        for (size_t i = 0; i < word.size(); i++) {
            std::string left = word.substr(0, i);
            std::string right = word.substr(i + 1);

            for (const Node& nb : graph[left + '*' + right]) {
                if (visited.contains(nb)) {
                    continue;
                }

                visited.insert(nb);
                prev[nb] = word;
                q.push(nb);
            }
        }
    }

    std::vector<std::string> path;

    std::string cur = endWord;
    while (true) {
        path.push_back(cur);
        if (!prev.contains(cur)) {
            break;
        }
        cur = prev[cur];
    }

    std::ranges::reverse(path);

    return path;
}

void printPath(const std::vector<std::string>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        std::cout << path[i];
        if (i != path.size() - 1) {
            std::cout << " -> ";
        }
    }
    std::cout << "\n";
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Niepoprawne argumenty!\n";
        return 1;
    }

    std::string startWord = argv[1];
    std::string endWord = argv[2];

    std::vector<std::string> words = readWords("./slowa4.txt");
    std::vector<std::string> path = shortestPath(startWord, endWord, words);

    printPath(path);

    return 0;
}
