#include <cerrno>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using num_t = std::int32_t;

constexpr num_t PROC_PP_PRICE_LO = 100;
constexpr num_t PROC_PP_PRICE_HI = 300;
constexpr num_t PROC_HC_PRICE_LO = 300;
constexpr num_t PROC_HC_PRICE_HI = 1000;

constexpr num_t TASK_TIME_HC_LO = 1;
constexpr num_t TASK_TIME_HC_HI = 200;
constexpr num_t TASK_TIME_PP_LO = 201;
constexpr num_t TASK_TIME_PP_HI = 500;
constexpr num_t TASK_UNAVILABLE_CHANCE_PERCENT = 1;

constexpr num_t BUS_CONN_COST_LO = 1;
constexpr num_t BUS_CONN_COST_HI = 50;
constexpr num_t BUS_BANDWIDTH_LO = 1;
constexpr num_t BUS_BANDWIDTH_HI = 10;

constexpr num_t WEIGHT_LO = 1;
constexpr num_t WEIGHT_HI = 50;

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
num_t random_range(num_t range_from, num_t range_to) {
    std::uniform_int_distribution<num_t> dist(range_from, range_to);
    return dist(generator);
}

struct Input {
    num_t tasks_n, hcs_n, pps_n, buses_n;
    bool unweighted_edges;
    std::string outfile;
};

using Edge = std::pair<num_t, num_t>; // (node_idx, weight)

enum ProcessorType { HC, PP };
struct Processor {
    num_t cost;
    ProcessorType type;
};

struct Bus {
    num_t cost; // koszt podpięcia dowolnego procesora do kanału
    num_t bandwidth;
    std::vector<bool> connected_to_processor; // czy obecna szyna jest podpięta do i-tego procesora
};

struct Output {
    Output(const Input& in)
        : adj_list(in.tasks_n), task_processor_time(in.tasks_n), task_processor_cost(in.tasks_n),
          buses(in.buses_n) {

        num_t proc_n = in.hcs_n + in.pps_n;
        processors.reserve(proc_n);

        for (int i = 0; i < task_processor_time.size(); i++) {
            task_processor_time[i] = std::vector<num_t>(proc_n);
        }
        for (int i = 0; i < task_processor_cost.size(); i++) {
            task_processor_cost[i] = std::vector<num_t>(proc_n);
        }
    }

    std::vector<std::unordered_map<num_t, Edge>> adj_list; // lista sąsiedztwa i-tego wierzchołka
    std::vector<Processor> processors;
    std::vector<std::vector<num_t>>
        task_processor_time; // czas wykonania i-tego zadania na j-tym procesorze
    std::vector<std::vector<num_t>>
        task_processor_cost; // koszt wykonania i-tego zadania na j-tym procesorze
    std::vector<Bus> buses;
};

Output generate_dag(const Input& in) {
    Output out(in);
    int proc_n = in.hcs_n + in.pps_n;

    for (int i = 0; i < in.hcs_n; i++) {
        out.processors.push_back(Processor{.cost = random_range(PROC_HC_PRICE_LO, PROC_HC_PRICE_HI),
                                           .type = ProcessorType::HC});
    }
    for (int i = 0; i < in.pps_n; i++) {
        out.processors.push_back(Processor{.cost = random_range(PROC_PP_PRICE_LO, PROC_PP_PRICE_HI),
                                           .type = ProcessorType::PP});
    }

    for (int i = 0; i < in.tasks_n; i++) {
        for (int j = 0; j < proc_n; j++) {
            if (out.processors[j].type == ProcessorType::PP) {
                out.task_processor_time[i][j] = random_range(TASK_TIME_PP_LO, TASK_TIME_PP_HI);
            } else if (out.processors[j].type == ProcessorType::HC) {
                out.task_processor_time[i][j] = random_range(TASK_TIME_HC_LO, TASK_TIME_HC_HI);
            }

            if (random_range(1, 100) <= TASK_UNAVILABLE_CHANCE_PERCENT) {
                out.task_processor_time[i][j] = -1;
            }
        }
    }
    for (int i = 0; i < in.tasks_n; i++) {
        for (int j = 0; j < proc_n; j++) {
            if (out.processors[j].type == ProcessorType::PP) {
                out.task_processor_cost[i][j] = random_range(PROC_PP_PRICE_LO, PROC_PP_PRICE_HI);
            } else if (out.processors[j].type == ProcessorType::HC) {
                out.task_processor_cost[i][j] = random_range(PROC_HC_PRICE_LO, PROC_HC_PRICE_HI);
            }
        }
    }

    for (int i = 0; i < in.buses_n; i++) {
        out.buses[i].cost = random_range(BUS_CONN_COST_LO, BUS_CONN_COST_HI);
        out.buses[i].bandwidth = random_range(BUS_BANDWIDTH_LO, BUS_BANDWIDTH_HI);

        out.buses[i].connected_to_processor = std::vector<bool>(proc_n);
        // Zawsze połącz do przynajmniej jednego
        out.buses[i].connected_to_processor[random_range(0, proc_n - 1)] = true;
        for (int j = 0; j < proc_n; j++) {
            out.buses[i].connected_to_processor[j] = (random_range(1, in.buses_n) == 1);
        }
    }

    // Always rooted at 0
    for (int cur = 1; cur < in.tasks_n; cur++) {
        num_t trials = random_range(1, 3);
        for (int i = 0; i < trials; i++) {
            num_t parent = random_range(0, cur - 1);
            num_t weight = in.unweighted_edges ? 0 : random_range(WEIGHT_LO, WEIGHT_HI);
            out.adj_list[parent][cur] = std::make_pair(cur, weight);
        }
    }

    return out;
}

void write_file(std::string filename, Output& out) {
    std::ofstream file;
    file.exceptions(std::ios::badbit | std::ios::failbit);
    file.open(filename);

    file << "@tasks " << out.adj_list.size() << '\n';
    for (auto i = 0; i < out.adj_list.size(); i++) {
        file << i << ' ' << out.adj_list[i].size();

        for (auto& [_, edge] : out.adj_list[i]) {
            auto& [node, weight] = edge;
            file << ' ' << node << '(' << weight << ')';
        }
        file << '\n';
    }
    file << '\n';

    file << "@proc " << out.processors.size() << '\n';
    for (const Processor& proc : out.processors) {
        num_t type = proc.type == ProcessorType::HC ? 0 : 1;
        file << proc.cost << ' ' << 0 << ' ' << type << '\n';
    }
    file << '\n';

    file << "@times\n";
    for (auto i = 0; i < out.adj_list.size(); i++) {
        for (auto j = 0; j < out.processors.size(); j++) {
            file << out.task_processor_time[i][j] << ' ';
        }
        file << '\n';
    }
    file << '\n';

    file << "@cost\n";
    for (auto i = 0; i < out.adj_list.size(); i++) {
        for (auto j = 0; j < out.processors.size(); j++) {
            file << out.task_processor_cost[i][j] << ' ';
        }
        file << '\n';
    }
    file << '\n';

    file << "@comm\n";
    for (auto i = 0; i < out.buses.size(); i++) {
        const Bus& bus = out.buses[i];
        file << "chan" << i << ' ' << bus.cost << ' ' << bus.bandwidth;

        for (bool connected : bus.connected_to_processor) {
            file << ' ' << (int)connected;
        }

        file << '\n';
    }
    file << '\n';

    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 7) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "liczba_zadań liczba_procesorów_hc liczba_procesorów_pp liczba_szyn "
                     "etykiety_0 plik_wyjściowy";
        return 1;
    }

    Input input;
    input.tasks_n = std::stoi(argv[1]);
    input.hcs_n = std::stoi(argv[2]);
    input.pps_n = std::stoi(argv[3]);
    input.buses_n = std::stoi(argv[4]);
    input.unweighted_edges = static_cast<bool>(std::stoi(argv[5]));
    input.outfile = argv[6];

    Output output = generate_dag(input);
    try {
        write_file(input.outfile, output);
        std::cout << "Pomyślnie zapisano dane do pliku\n";
        return 0;
    } catch (std::ios_base::failure e) {
        std::cout << "Błąd zapisywania do pliku:\n\t" << std::strerror(errno) << '\n';
        return 1;
    }
}
