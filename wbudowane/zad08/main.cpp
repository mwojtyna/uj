#include <cerrno>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iostream>
#include <random>
#include <string>
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
constexpr num_t DEPENDENCY_CONDITION_CHANCE_PERCENT = 10;

// clang-format off
const std::vector<std::string> CONDITIONS = {
    "temperatura < 100",
    "napiecie >= 12",
    "obciazenie < 80",
    "czas_pracy <= 500",
    "pamiec > 256",
    "predkosc >= 50",
    "cisnienie < 30",
    "energia <= 1000",
    "sygnal == aktywny",
    "tryb != serwis",
};

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
num_t random_range(num_t range_from, num_t range_to) {
    std::uniform_int_distribution<num_t> dist(range_from, range_to);
    return dist(generator);
}

const std::string& random_condition() {
    return CONDITIONS[random_range(0, static_cast<num_t>(CONDITIONS.size() - 1))];
}

std::string maybe_random_condition() {
    if (random_range(1, 100) > DEPENDENCY_CONDITION_CHANCE_PERCENT) {
        return "";
    }

    return random_condition();
}

struct Input {
    num_t tasks_n, hcs_n, pps_n, buses_n;
    bool unweighted_edges;
    std::string outfile;
};

struct Dependency {
    num_t to;
    num_t communication_cost;
    std::string condition;
};

enum class ProcessorType { HC, PP };
struct Processor {
    num_t cost;
    ProcessorType type;
};

struct TaskProfile {
    std::vector<Dependency> dependencies;
    std::vector<num_t> time_by_proc;
    std::vector<num_t> cost_by_proc;
};

struct Bus {
    std::string name;
    num_t hookup_cost; // koszt podpięcia dowolnego procesora do kanału
    num_t bandwidth;
    std::vector<bool> connected_processors; // czy obecna szyna jest podpięta do i-tego procesora
};

struct Output {
    Output(const Input& in) : tasks(in.tasks_n), buses(in.buses_n) {
        const num_t proc_n = in.hcs_n + in.pps_n;
        processors.reserve(proc_n);

        for (TaskProfile& task : tasks) {
            task.time_by_proc.assign(proc_n, 0);
            task.cost_by_proc.assign(proc_n, 0);
        }
    }

    std::vector<TaskProfile> tasks;
    std::vector<Processor> processors;
    std::vector<Bus> buses;
};

Output generate_dag(const Input& in) {
    Output out(in);
    const int proc_n = in.hcs_n + in.pps_n;

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
                out.tasks[i].time_by_proc[j] = random_range(TASK_TIME_PP_LO, TASK_TIME_PP_HI);
            } else if (out.processors[j].type == ProcessorType::HC) {
                out.tasks[i].time_by_proc[j] = random_range(TASK_TIME_HC_LO, TASK_TIME_HC_HI);
            }

            if (random_range(1, 100) <= TASK_UNAVILABLE_CHANCE_PERCENT) {
                out.tasks[i].time_by_proc[j] = -1;
            }
        }
    }
    for (int i = 0; i < in.tasks_n; i++) {
        for (int j = 0; j < proc_n; j++) {
            if (out.processors[j].type == ProcessorType::PP) {
                out.tasks[i].cost_by_proc[j] = random_range(PROC_PP_PRICE_LO, PROC_PP_PRICE_HI);
            } else if (out.processors[j].type == ProcessorType::HC) {
                out.tasks[i].cost_by_proc[j] = random_range(PROC_HC_PRICE_LO, PROC_HC_PRICE_HI);
            }
        }

    }

    for (int i = 0; i < in.buses_n; i++) {
        out.buses[i].name = "chan" + std::to_string(i);
        out.buses[i].hookup_cost = random_range(BUS_CONN_COST_LO, BUS_CONN_COST_HI);
        out.buses[i].bandwidth = random_range(BUS_BANDWIDTH_LO, BUS_BANDWIDTH_HI);

        out.buses[i].connected_processors = std::vector<bool>(proc_n);
        // Zawsze połącz do przynajmniej jednego
        out.buses[i].connected_processors[random_range(0, proc_n - 1)] = true;
        for (int j = 0; j < proc_n; j++) {
            out.buses[i].connected_processors[j] =
                out.buses[i].connected_processors[j] || (random_range(1, in.buses_n) == 1);
        }
    }

    // Always rooted at 0
    for (int cur = 1; cur < in.tasks_n; cur++) {
        num_t trials = random_range(1, 3);
        for (int i = 0; i < trials; i++) {
            num_t parent = random_range(0, cur - 1);
            num_t weight = in.unweighted_edges ? 0 : random_range(WEIGHT_LO, WEIGHT_HI);
            bool dependency_exists = false;
            for (const Dependency& dependency : out.tasks[parent].dependencies) {
                if (dependency.to == cur) {
                    dependency_exists = true;
                    break;
                }
            }

            if (!dependency_exists) {
                out.tasks[parent].dependencies.push_back(
                    Dependency{
                        .to = cur,
                        .communication_cost = weight,
                        .condition = maybe_random_condition(),
                    });
            }
        }
    }

    return out;
}

void write_file(std::string filename, Output& out) {
    std::ofstream file;
    file.exceptions(std::ios::badbit | std::ios::failbit);
    file.open(filename);

    file << "@tasks " << out.tasks.size() << '\n';
    for (std::size_t i = 0; i < out.tasks.size(); i++) {
        file << i << ' ' << out.tasks[i].dependencies.size();

        for (const Dependency& dependency : out.tasks[i].dependencies) {
            file << ' ' << dependency.to << '(' << dependency.communication_cost << ')';
            if (!dependency.condition.empty()) {
                file << '[' << dependency.condition << ']';
            }
        }
        file << '\n';
    }
    file << '\n';

    file << "@proc " << out.processors.size() << '\n';
    for (const Processor& proc : out.processors) {
        const num_t type = proc.type == ProcessorType::HC ? 0 : 1;
        file << proc.cost << ' ' << 0 << ' ' << type << '\n';
    }
    file << '\n';

    file << "@times\n";
    for (std::size_t i = 0; i < out.tasks.size(); i++) {
        for (std::size_t j = 0; j < out.processors.size(); j++) {
            file << out.tasks[i].time_by_proc[j] << ' ';
        }
        file << '\n';
    }
    file << '\n';

    file << "@cost\n";
    for (std::size_t i = 0; i < out.tasks.size(); i++) {
        for (std::size_t j = 0; j < out.processors.size(); j++) {
            file << out.tasks[i].cost_by_proc[j] << ' ';
        }
        file << '\n';
    }
    file << '\n';

    file << "@comm\n";
    for (std::size_t i = 0; i < out.buses.size(); i++) {
        const Bus& bus = out.buses[i];
        file << bus.name << ' ' << bus.hookup_cost << ' ' << bus.bandwidth;

        for (bool connected : bus.connected_processors) {
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
