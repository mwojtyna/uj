#include <cstdint>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

using num_t = int32_t;
using Node = std::string;
using Graph = std::unordered_map<Node, std::vector<Node>>;

// Kroki
const Node step1 = "nagrzać patelnię";
const Node step2 = "zmieszać jajko, olej, mleko i proszek do naleśników";
const Node step3 = "wylać część ciasta naleśnikowego na gorącą patelnię";
const Node step4 = "gdy naleśnik jest rumiany od spodu, przewrócić i podpiec z drugiej strony";
const Node step5 = "podgrzać syrop klonowy";
const Node step6 = "zjeść naleśnik polany ciepłym syropem klonowym";

std::vector<Node> topoSort(const Graph& graph) {
    std::unordered_map<Node, num_t> indegree;

    // init indegree
    for (const auto& [u, adj] : graph) {
        if (!indegree.contains(u)) {
            indegree[u] = 0;
        }
        for (const Node& v : adj) {
            indegree[v]++;
        }
    }

    std::queue<Node> q;

    for (const auto& [node, deg] : indegree) {
        if (deg == 0) {
            q.push(node);
        }
    }

    std::vector<Node> order;

    while (!q.empty()) {
        Node u = q.front();
        q.pop();
        order.push_back(u);

        for (const Node& v : graph.at(u)) {
            indegree[v]--;
            if (indegree[v] == 0) {
                q.push(v);
            }
        }
    }

    return order;
}

int main() {
    Graph graph;

    graph[step1] = {step3};
    graph[step2] = {step3};
    graph[step3] = {step4};
    graph[step4] = {step6};
    graph[step5] = {step6};
    graph[step6] = {};

    std::vector<Node> order = topoSort(graph);

    std::cout << "Kolejność:\n";
    for (const auto& step : order) {
        std::cout << step << "\n";
    }

    return 0;
}
