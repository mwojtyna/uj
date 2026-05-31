#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <print>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using num_t = int32_t;
using Node = std::string;

struct Edge {
    size_t fromIdx;
    size_t toIdx;
    num_t weight;
};

struct Graph {
    std::vector<Node> nodes;
    std::vector<Edge> edges;
};

struct Position {
    double latitude;
    double longitude;
};

struct FloydWarshallResult {
    std::vector<std::vector<num_t>> distances;
    std::vector<std::vector<int>> next;
};

constexpr num_t INF = std::numeric_limits<num_t>::max() / 4;

size_t getOrCreateNode(std::vector<Node>& nodes, const Node& node) {
    auto it = std::ranges::find(nodes, node);
    if (it != nodes.end()) {
        return static_cast<size_t>(std::distance(nodes.begin(), it));
    }

    nodes.push_back(node);
    return nodes.size() - 1;
}

Graph readGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Nie można otworzyć pliku: " + filename);
    }

    std::vector<Node> nodes;
    std::vector<Edge> edges;

    Node from;
    Node to;
    num_t weight;
    while (file >> from >> to >> weight) {
        size_t fromIdx = getOrCreateNode(nodes, from);
        size_t toIdx = getOrCreateNode(nodes, to);
        edges.emplace_back(fromIdx, toIdx, weight);
    }

    return Graph{.nodes = std::move(nodes), .edges = std::move(edges)};
}

std::vector<Position> readPositions(const std::string& filename, const std::vector<Node>& nodes) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Nie można otworzyć pliku: " + filename);
    }

    std::map<Node, Position> positionsByName;
    Node city;
    double latitude;
    double longitude;
    while (file >> city >> latitude >> longitude) {
        positionsByName[city] = Position{.latitude = latitude, .longitude = longitude};
    }

    std::vector<Position> positions;
    positions.reserve(nodes.size());
    for (const Node& node : nodes) {
        auto it = positionsByName.find(node);
        if (it == positionsByName.end()) {
            throw std::runtime_error("Brak współrzędnych miasta: " + node);
        }
        positions.push_back(it->second);
    }

    return positions;
}

FloydWarshallResult floydWarshall(const Graph& graph) {
    const size_t n = graph.nodes.size();
    std::vector<std::vector<num_t>> distances(n, std::vector<num_t>(n, INF));
    std::vector<std::vector<int>> next(n, std::vector<int>(n, -1));

    for (size_t i = 0; i < n; ++i) {
        distances[i][i] = 0;
        next[i][i] = static_cast<int>(i);
    }

    for (const Edge& edge : graph.edges) {
        if (edge.weight < distances[edge.fromIdx][edge.toIdx]) {
            distances[edge.fromIdx][edge.toIdx] = edge.weight;
            distances[edge.toIdx][edge.fromIdx] = edge.weight;
            next[edge.fromIdx][edge.toIdx] = static_cast<int>(edge.toIdx);
            next[edge.toIdx][edge.fromIdx] = static_cast<int>(edge.fromIdx);
        }
    }

    for (size_t k = 0; k < n; ++k) {
        for (size_t i = 0; i < n; ++i) {
            if (distances[i][k] == INF) {
                continue;
            }

            for (size_t j = 0; j < n; ++j) {
                if (distances[k][j] == INF) {
                    continue;
                }

                num_t transitiveDist = distances[i][k] + distances[k][j];
                if (transitiveDist < distances[i][j]) {
                    distances[i][j] = transitiveDist;
                    next[i][j] = next[i][k];
                }
            }
        }
    }

    return FloydWarshallResult{.distances = std::move(distances), .next = std::move(next)};
}

std::vector<size_t> reconstructPath(size_t from, size_t to,
                                    const std::vector<std::vector<int>>& next) {
    if (next[from][to] == -1) {
        return {};
    }

    std::vector<size_t> path{from};
    while (from != to) {
        from = static_cast<size_t>(next[from][to]);
        path.push_back(from);
    }

    return path;
}

std::pair<size_t, size_t> edgeKey(size_t a, size_t b) {
    return std::minmax(a, b);
}

std::string quoted(const std::string& value) {
    std::string result = "\"";
    for (char ch : value) {
        if (ch == '"' || ch == '\\') {
            result.push_back('\\');
        }
        result.push_back(ch);
    }
    result.push_back('"');
    return result;
}

std::string pairFilename(size_t from, size_t to, const std::string& extension) {
    std::ostringstream name;
    name
        << "route_"
        << std::setw(2)
        << std::setfill('0')
        << from
        << "_"
        << std::setw(2)
        << std::setfill('0')
        << to
        << extension;
    return name.str();
}

void writeRouteDot(const std::filesystem::path& filename, const Graph& graph,
                   const std::vector<Position>& positions, const std::vector<size_t>& path,
                   num_t distance) {
    std::ofstream out(filename);
    if (!out) {
        throw std::runtime_error("Nie można zapisać pliku: " + filename.string());
    }

    std::set<std::pair<size_t, size_t>> pathEdges;
    for (size_t i = 1; i < path.size(); ++i) {
        pathEdges.insert(edgeKey(path[i - 1], path[i]));
    }

    const auto minLatIt
        = std::ranges::min_element(positions, {}, [](const Position& pos) { return pos.latitude; });
    const auto minLonIt = std::ranges::min_element(
        positions, {}, [](const Position& pos) { return pos.longitude; });

    const double scale = 120.0;
    const double minLat = minLatIt->latitude;
    const double minLon = minLonIt->longitude;

    out << "graph G {\n";
    out << "  layout=fdp;\n";
    out << "  overlap=false;\n";
    out << "  splines=true;\n";
    out
        << "  label="
        << quoted(graph.nodes[path.front()]
                  + " -> "
                  + graph.nodes[path.back()]
                  + ", czas: "
                  + std::to_string(distance))
        << ";\n";
    out << "  labelloc=t;\n";
    out << "  node [shape=ellipse, style=filled, fillcolor=white, color=black, "
           "fontname=\"DejaVu Sans\", fontsize=9, margin=0.04];\n";
    out << "  edge [color=gray70, penwidth=1.2, fontname=\"DejaVu Sans\"];\n";

    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        double x = (positions[i].longitude - minLon) * scale;
        double y = (positions[i].latitude - minLat) * scale;
        bool isRouteNode = std::ranges::find(path, i) != path.end();

        out << "  " << quoted(graph.nodes[i]) << " [pos=\"" << x << "," << y << "!\"";
        if (isRouteNode) {
            out << ", fillcolor=\"#ffe08a\", color=\"#cc5500\", penwidth=2";
        }
        out << "];\n";
    }

    for (const Edge& edge : graph.edges) {
        bool isRouteEdge = pathEdges.contains(edgeKey(edge.fromIdx, edge.toIdx));
        out
            << "  "
            << quoted(graph.nodes[edge.fromIdx])
            << " -- "
            << quoted(graph.nodes[edge.toIdx])
            << " [label="
            << quoted(std::to_string(edge.weight));
        if (isRouteEdge) {
            out << ", color=\"#d62728\", penwidth=4";
        }
        out << "];\n";
    }

    out << "}\n";
}

void generatePng(const std::filesystem::path& dotFile, const std::filesystem::path& pngFile) {
    std::ostringstream command;
    command
        << "dot -Kfdp -n -Tpng "
        << quoted(dotFile.string())
        << " -o "
        << quoted(pngFile.string())
        << " 2> /dev/null";

    int exitCode = std::system(command.str().c_str());
    if (exitCode != 0) {
        std::println(std::cerr, "Nie udało się wygenerować PNG dla pliku: {}", dotFile.string());
    }
}

int main() {
    try {
        Graph graph = readGraph("./czasy");
        std::vector<Position> positions = readPositions("./positions", graph.nodes);
        FloydWarshallResult result = floydWarshall(graph);

        const std::filesystem::path outputDir = "routes";
        std::filesystem::create_directories(outputDir);

        std::println("Najkrótsze czasy przejazdu:");
        for (size_t i = 0; i < graph.nodes.size(); ++i) {
            for (size_t j = i + 1; j < graph.nodes.size(); ++j) {
                if (result.distances[i][j] == INF) {
                    continue;
                }

                std::vector<size_t> path = reconstructPath(i, j, result.next);
                std::filesystem::path dotFile = outputDir / pairFilename(i, j, ".dot");
                std::filesystem::path pngFile = outputDir / pairFilename(i, j, ".png");

                writeRouteDot(dotFile, graph, positions, path, result.distances[i][j]);
                generatePng(dotFile, pngFile);

                std::print("{} -> {}: {} (", graph.nodes[i], graph.nodes[j],
                           result.distances[i][j]);
                for (size_t pathIdx = 0; pathIdx < path.size(); ++pathIdx) {
                    if (pathIdx != 0) {
                        std::print(" -> ");
                    }
                    std::print("{}", graph.nodes[path[pathIdx]]);
                }
                std::println(")");
            }
        }
    } catch (const std::exception& ex) {
        std::println(std::cerr, "Błąd: {}", ex.what());
        return 1;
    }

    return 0;
}
