#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using num_t = std::int32_t;

std::random_device rand_dev;
std::mt19937 generator(rand_dev());
num_t random_range(num_t range_from, num_t range_to) {
    std::uniform_int_distribution<num_t> dist(range_from, range_to);
    return dist(generator);
}

struct Dependency {
    num_t to;
    num_t communication_cost;
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

struct Input {
    std::vector<TaskProfile> tasks;
    std::vector<Processor> processors;
    std::vector<Bus> buses;

    num_t taskCount() const {
        return static_cast<num_t>(tasks.size());
    }
    num_t processorCount() const {
        return static_cast<num_t>(processors.size());
    }
};

struct TaskResult {
    num_t idx;
    num_t task_begin_time;
    TaskResult(num_t idx, num_t task_begin_time) : idx(idx), task_begin_time(task_begin_time) {}
};

struct Output {
    num_t total_time;
    num_t total_cost;
    std::vector<TaskResult> task_results; // PE -> lista zadań (idx, czas rozpoczęcia)
};

num_t timeToLeaf(num_t taskIdx, num_t procIdx, const Input& in, std::vector<num_t>& memo) {
    if (memo[taskIdx] != -1) {
        return memo[taskIdx];
    }

    num_t time = in.tasks[taskIdx].time_by_proc[procIdx];

    num_t maxChildTime = 0;
    for (const Dependency& dependency : in.tasks[taskIdx].dependencies) {
        const num_t nbIdx = dependency.to;
        maxChildTime = std::max(maxChildTime, timeToLeaf(nbIdx, procIdx, in, memo));
    }

    memo[taskIdx] = time + maxChildTime;
    return memo[taskIdx];
}

Output process(const Input& in) {
    const num_t task_count = in.taskCount();
    Output out{};

    // Find first PP processor
    num_t firstPPIdx = 0;
    for (num_t i = 0; i < in.processorCount(); i++) {
        if (in.processors[i].type == ProcessorType::PP) {
            firstPPIdx = i;
            break;
        }
    }

    // Compute total time and cost
    out.total_cost += in.processors[firstPPIdx].cost;
    for (int i = 0; i < task_count; i++) {
        out.total_time += in.tasks[i].time_by_proc[firstPPIdx];
        out.total_cost += in.tasks[i].cost_by_proc[firstPPIdx];
    }

    std::vector<num_t> memo(in.taskCount(), -1);
    timeToLeaf(0, firstPPIdx, in, memo);

    std::vector<num_t> indeg(task_count, 0);
    for (num_t from = 0; from < task_count; from++) {
        for (const Dependency& dependency : in.tasks[from].dependencies) {
            indeg[dependency.to] += 1;
        }
    }

    // Toposort + choose biggest time to leaf
    struct TaskPQ {
        num_t taskIdx;
        num_t timeToLeaf;
        TaskPQ(num_t taskIdx, num_t timeToLeaf) : taskIdx(taskIdx), timeToLeaf(timeToLeaf) {}
    };
    auto comp = [](const TaskPQ& a, const TaskPQ& b) -> bool {
        return a.timeToLeaf <= b.timeToLeaf;
    };
    std::priority_queue<TaskPQ, std::vector<TaskPQ>, decltype(comp)> maxHeap;

    for (num_t i = 0; i < task_count; i++) {
        if (indeg[i] == 0) {
            maxHeap.push(TaskPQ(i, memo[i]));
        }
    }

    num_t curTime = 0;
    while (!maxHeap.empty()) {
        const auto [taskIdx, timeToLeaf] = maxHeap.top();
        maxHeap.pop();
        out.task_results.emplace_back(taskIdx, curTime);

        for (const Dependency& dependency : in.tasks[taskIdx].dependencies) {
            const num_t nbIdx = dependency.to;
            indeg[nbIdx] -= 1;
            if (indeg[nbIdx] == 0) {
                maxHeap.push(TaskPQ(nbIdx, memo[nbIdx]));
            }
        }

        curTime += in.tasks[taskIdx].time_by_proc[firstPPIdx];
    }

    return out;
}

Input readInput(const std::string& filename) {
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
            input.tasks.assign(tasks_n, TaskProfile{});

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

                    input.tasks[task_id].dependencies.push_back(
                        Dependency{.to = node, .communication_cost = weight});
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
                    .cost = cost, .type = (type == 0) ? ProcessorType::HC : ProcessorType::PP});
            }
        } else if (section == "@times") {
            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);
                input.tasks[i].time_by_proc.assign(proc_n, 0);
                for (num_t j = 0; j < proc_n; j++) {
                    row >> input.tasks[i].time_by_proc[j];
                }
            }
        } else if (section == "@cost") {
            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);
                input.tasks[i].cost_by_proc.assign(proc_n, 0);
                for (num_t j = 0; j < proc_n; j++) {
                    row >> input.tasks[i].cost_by_proc[j];
                }
            }
        } else if (section == "@comm") {
            input.buses.clear();

            while (std::getline(file, line) && !line.empty()) {
                std::istringstream row(line);
                Bus bus;

                row >> bus.name >> bus.hookup_cost >> bus.bandwidth;
                bus.connected_processors.assign(proc_n, false);

                for (num_t i = 0; i < proc_n; i++) {
                    int connected = 0;
                    row >> connected;
                    bus.connected_processors[i] = static_cast<bool>(connected);
                }

                input.buses.push_back(bus);
            }
            break;
        }
    }

    file.close();
    return input;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejsciowy\n";
        return 1;
    }

    std::string infile = argv[1];

    Input in = readInput(infile);
    if (in.buses.size() != 1) {
        std::cout << "Obsługiwany jest jednie przypadek gdy liczba szyn == 1";
        return 1;
    }

    Output out = process(in);
    std::cout << "Całkowity czas: " << out.total_time << "\n";
    std::cout << "Całkowity koszt: " << out.total_cost << "\n";

    for (const TaskResult& task : out.task_results) {
        std::cout << "T" << task.idx << "(" << task.task_begin_time << "), ";
    }
    std::cout << "\n";

    return 0;
}
