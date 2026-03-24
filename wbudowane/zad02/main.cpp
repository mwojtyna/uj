#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using num_t = std::int32_t;

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
num_t random_range(num_t range_from, num_t range_to) {
    std::uniform_int_distribution<num_t> dist(range_from, range_to);
    return dist(generator);
}

using Edge = std::pair<num_t, num_t>; // (node_idx, weight)

enum ProcessorType { HC, PP };
struct Processor {
    num_t cost;
    ProcessorType type;
};

struct Bus {
    std::string name;
    num_t cost; // koszt podpięcia dowolnego procesora do kanału
    num_t bandwidth;
    std::vector<bool> connected_to_processor; // czy obecna szyna jest podpięta do i-tego procesora
};

struct Input {
    std::unordered_map<num_t, std::unordered_map<num_t, Edge>>
        adj_list; // lista sąsiedztwa i-tego wierzchołka
    std::vector<Processor> processors;
    std::vector<std::vector<num_t>>
        task_processor_time; // czas wykonania i-tego zadania na j-tym procesorze
    std::vector<std::vector<num_t>>
        task_processor_cost; // koszt wykonania i-tego zadania na j-tym procesorze
    std::vector<Bus> buses;
};

struct Task {
    num_t idx;
    num_t task_begin_time;
};

struct Output {
    std::map<num_t, std::map<num_t, Task>>
        processor_tasks; // nazwa PE -> lista zadań (nazwa, czas rozpoczęcia)
    std::map<std::string, std::vector<num_t>>
        bus_processors; // nazwa szyny -> lista indeksów procesorów połączonych z szyną
    num_t total_cost;
};

num_t calculateCost(const Input& in, const std::map<num_t, num_t>& task_proc,
                    const std::map<num_t, std::string>& proc_bus) {
    num_t total_cost = 0;

    for (const auto& [taskIdx, procIdx] : task_proc) {
        total_cost += in.task_processor_cost[taskIdx][procIdx] + in.processors[procIdx].cost;
    }

    for (const auto& [_, busName] : proc_bus) {
        // TODO: hashmap
        for (const auto& bus : in.buses) {
            if (bus.name == busName) {
                total_cost += bus.cost;
                break;
            }
        }
    }

    return total_cost;
}

Output process(Input& in) {
    Output out;
    const num_t task_count = in.task_processor_time.size();

    std::map<num_t, num_t> task_proc;      // taskIdx -> procIdx
    std::map<num_t, std::string> proc_bus; // procIdx -> busIdx

    // Znajdź najszybszy procesor HC dla każdego zadania
    for (num_t taskIdx = 0; taskIdx < task_count; taskIdx++) {
        num_t minTimeProcIdx = 0;
        num_t minTime = in.task_processor_time[taskIdx][minTimeProcIdx];
        for (num_t procIdx = 0; procIdx < in.task_processor_time[taskIdx].size(); procIdx++) {
            auto curTime = in.task_processor_time[taskIdx][procIdx];
            auto curCost = in.task_processor_cost[taskIdx][procIdx];

            if (curTime < minTime ||
                (curTime == minTime && curCost < in.task_processor_cost[taskIdx][minTimeProcIdx])) {
                minTime = curTime;
                minTimeProcIdx = procIdx;
            }
        }

        task_proc[taskIdx] = minTimeProcIdx;
    }

    // Wpisz do Output
    for (const auto& [taskIdx, procIdx] : task_proc) {
        out.processor_tasks[procIdx][taskIdx] = Task{.idx = taskIdx, .task_begin_time = -1};
    }

    // Znajdź najtańszą szynę dla każdego procesora
    for (num_t procIdx = 0; procIdx < in.processors.size(); procIdx++) {
        if (out.processor_tasks[procIdx].empty()) {
            continue;
        }

        // Znajdź szyny do których można dołączyć procesor
        std::vector<num_t> validBusIdxs;
        validBusIdxs.reserve(in.buses.size());
        for (num_t busIdx = 0; busIdx < in.buses.size(); busIdx++) {
            if (in.buses[busIdx].connected_to_processor[procIdx]) {
                validBusIdxs.push_back(busIdx);
            }
        }

        if (validBusIdxs.empty()) {
            continue;
        }

        num_t busChoiceIdx = random_range(0, validBusIdxs.size() - 1);
        num_t busIdx = validBusIdxs[busChoiceIdx];
        proc_bus[procIdx] = in.buses[busIdx].name;
    }

    // Wpisz do Output
    for (const auto& [procIdx, busIdx] : proc_bus) {
        out.bus_processors[busIdx].push_back(procIdx);
    }

    // Topo sort
    std::vector<num_t> indeg(task_count, 0);
    for (num_t from = 0; from < task_count; from++) {
        for (const auto& [to, _] : in.adj_list[from]) {
            indeg[to] += 1;
        }
    }

    std::vector<num_t> task_start_time(task_count, 0);

    std::queue<num_t> q;
    for (num_t taskIdx = 0; taskIdx < task_count; taskIdx++) {
        if (indeg[taskIdx] == 0) {
            q.push(taskIdx);
        }
    }

    while (!q.empty()) {
        num_t taskIdx = q.front();
        q.pop();

        for (const auto& [nbIdx, _] : in.adj_list[taskIdx]) {
            task_start_time[nbIdx] +=
                task_start_time[taskIdx] + in.task_processor_time[taskIdx][task_proc[taskIdx]];

            indeg[nbIdx]--;
            if (indeg[nbIdx] == 0) {
                q.push(nbIdx);
            }
        }
    }

    for (const auto& [taskIdx, procIdx] : task_proc) {
        out.processor_tasks[procIdx][taskIdx].task_begin_time = task_start_time[taskIdx];
    }

    out.total_cost = calculateCost(in, task_proc, proc_bus);

    return out;
}

Input readInput(std::string& filename) {
    std::ifstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku wejściowego: " + filename);
    }

    Input input;
    std::string line;
    num_t tasks_n = 0;
    num_t proc_n = 0;
    auto parseTaskId = [](const std::string& token) -> num_t {
        if (token.empty()) {
            throw std::runtime_error("Pusty identyfikator zadania");
        }

        if (token[0] == 'T' || token[0] == 't') {
            return static_cast<num_t>(std::stoi(token.substr(1)));
        }

        return static_cast<num_t>(std::stoi(token));
    };

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream header(line);
        std::string section;
        header >> section;

        if (section == "@tasks") {
            header >> tasks_n;
            input.adj_list.clear();
            for (num_t i = 0; i < tasks_n; i++) {
                input.adj_list[i] = {};
            }

            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);

                std::string task_token;
                num_t edge_count = 0;
                row >> task_token >> edge_count;
                num_t task_id = parseTaskId(task_token);

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;

                    std::size_t open_pos = edge_token.find('(');
                    std::size_t close_pos = edge_token.find(')');
                    num_t node = static_cast<num_t>(std::stoi(edge_token.substr(0, open_pos)));
                    num_t weight = static_cast<num_t>(
                        std::stoi(edge_token.substr(open_pos + 1, close_pos - open_pos - 1)));

                    input.adj_list[task_id][node] = std::make_pair(node, weight);
                }
            }
        } else if (section == "@proc") {
            header >> proc_n;
            input.processors.clear();
            input.processors.reserve(proc_n);

            for (num_t i = 0; i < proc_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);

                num_t cost = 0;
                num_t ignored = 0;
                num_t type = 0;
                row >> cost >> ignored >> type;

                input.processors.push_back(Processor{
                    .cost = cost, .type = type == 0 ? ProcessorType::HC : ProcessorType::PP});
            }
        } else if (section == "@times") {
            input.task_processor_time.assign(tasks_n, std::vector<num_t>(proc_n));

            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);
                for (num_t j = 0; j < proc_n; j++) {
                    row >> input.task_processor_time[i][j];
                }
            }
        } else if (section == "@cost") {
            input.task_processor_cost.assign(tasks_n, std::vector<num_t>(proc_n));

            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);
                for (num_t j = 0; j < proc_n; j++) {
                    row >> input.task_processor_cost[i][j];
                }
            }
        } else if (section == "@comm") {
            input.buses.clear();

            while (std::getline(file, line) && !line.empty()) {
                std::istringstream row(line);
                Bus bus;

                row >> bus.name >> bus.cost >> bus.bandwidth;
                bus.connected_to_processor.assign(proc_n, false);

                for (num_t i = 0; i < proc_n; i++) {
                    int connected = 0;
                    row >> connected;
                    bus.connected_to_processor[i] = static_cast<bool>(connected);
                }

                input.buses.push_back(bus);
            }
            break;
        }
    }

    file.close();
    return input;
}

void writeOutput(Output& out, std::string& filename) {
    std::ofstream file;
    file.open(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można stworzyć pliku wyjściowego: " + filename);
    }

    for (const auto& [procIdx, tasks] : out.processor_tasks) {
        if (tasks.empty()) {
            continue;
        }

        file << "P" << procIdx << ":";
        for (const auto& [_, task] : tasks) {
            file << " T" << task.idx << "(" << task.task_begin_time << ")";
        }
        file << "\n";
    }

    for (const auto& [bus_name, procs] : out.bus_processors) {
        if (procs.empty()) {
            continue;
        }

        file << bus_name << ":";
        for (int proc_id : procs) {
            file << " P" << proc_id;
        }
        file << "\n";
    }

    file.close();
    std::cout << "Napisano do pliku " << filename << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejsciowy plik_wyjsciowy\n";
        return 1;
    }

    std::string infile = argv[1];
    std::string outfile = argv[2];

    Input input = readInput(infile);
    Output output = process(input);
    writeOutput(output, outfile);

    std::cout << "Koszt: " << output.total_cost << "\n";

    return 0;
}
