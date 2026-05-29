#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <queue>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using num_t = std::int32_t;

struct Dependency {
    num_t to;
};

enum class ProcessorType { HC, PP };

struct Processor {
    num_t cost;
    ProcessorType type;
};

struct TaskProfile {
    std::string name;
    std::vector<Dependency> dependencies;
    std::vector<num_t> time_by_proc;
    std::vector<num_t> cost_by_proc;
};

struct Bus {
    std::string name;
    num_t hookup_cost = 0;
    num_t bandwidth = 0;
    std::vector<bool> connected_processors;
};

struct Input {
    std::vector<TaskProfile> tasks;
    std::vector<Processor> processors;
    std::vector<Bus> buses;

    [[nodiscard]] num_t taskCount() const {
        return static_cast<num_t>(tasks.size());
    }

    [[nodiscard]] num_t processorCount() const {
        return static_cast<num_t>(processors.size());
    }
};

struct Schedule {
    std::vector<num_t> task_start_time;
    num_t total_time = 0;
};

struct ConstructionResult {
    std::vector<num_t> task_processor;
    std::vector<num_t> task_start_time;
    num_t total_time = 0;
    num_t total_cost = 0;
    num_t attempts = 0;
};

struct RawDependency {
    num_t from;
    std::string to_token;
};

bool isBlank(const std::string& text) {
    return std::ranges::all_of(
        text, [](const char c) { return std::isspace(static_cast<unsigned char>(c)); });
}

std::string edgeTargetToken(const std::string& edge_token) {
    const std::size_t open_pos = edge_token.find('(');
    if (open_pos != std::string::npos) {
        return edge_token.substr(0, open_pos);
    }

    const std::size_t condition_pos = edge_token.find('[');
    const std::size_t split_pos =
        condition_pos == std::string::npos ? edge_token.size() : condition_pos;
    return edge_token.substr(0, split_pos);
}

std::vector<num_t> readProcessorVector(const std::string& line, const num_t proc_n) {
    std::istringstream row(line);
    std::vector<num_t> values(proc_n, 0);
    for (num_t i = 0; i < proc_n; i++) {
        row >> values[i];
    }

    return values;
}

Input readInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku wejściowego: " + filename);
    }

    Input input;
    std::vector<RawDependency> raw_dependencies;
    std::unordered_map<std::string, num_t> task_id_by_name;
    std::string line;
    num_t tasks_n = 0;
    num_t proc_n = 0;

    while (std::getline(file, line)) {
        if (isBlank(line)) {
            continue;
        }

        std::istringstream header(line);
        std::string section;
        header >> section;

        if (section == "@tasks") {
            header >> tasks_n;
            input.tasks.assign(tasks_n, TaskProfile{});
            raw_dependencies.clear();

            for (num_t row_idx = 0; row_idx < tasks_n; row_idx++) {
                std::getline(file, line);
                std::istringstream row(line);

                std::string task_token;
                num_t edge_count = 0;
                row >> task_token >> edge_count;

                const num_t task_id = row_idx;
                input.tasks[task_id].name = task_token;
                task_id_by_name[task_token] = task_id;

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;
                    raw_dependencies.push_back(
                        RawDependency{.from = task_id, .to_token = edgeTargetToken(edge_token)});
                }
            }

            for (const RawDependency& dependency : raw_dependencies) {
                const num_t to = task_id_by_name[dependency.to_token];
                input.tasks[dependency.from].dependencies.push_back(Dependency{.to = to});
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
                input.tasks[i].time_by_proc = readProcessorVector(line, proc_n);
            }
        } else if (section == "@cost") {
            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                input.tasks[i].cost_by_proc = readProcessorVector(line, proc_n);
            }
        } else if (section == "@comm") {
            input.buses.clear();

            while (std::getline(file, line) && !isBlank(line)) {
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

    return input;
}

std::vector<num_t> topologicalOrder(const Input& in) {
    std::vector<num_t> indeg(in.taskCount(), 0);
    for (num_t task = 0; task < in.taskCount(); task++) {
        for (const Dependency& dependency : in.tasks[task].dependencies) {
            indeg[dependency.to] += 1;
        }
    }

    std::queue<num_t> q;
    for (num_t task = 0; task < in.taskCount(); task++) {
        if (indeg[task] == 0) {
            q.push(task);
        }
    }

    std::vector<num_t> order;
    order.reserve(in.taskCount());
    while (!q.empty()) {
        const num_t task = q.front();
        q.pop();
        order.push_back(task);

        for (const Dependency& dependency : in.tasks[task].dependencies) {
            indeg[dependency.to] -= 1;
            if (indeg[dependency.to] == 0) {
                q.push(dependency.to);
            }
        }
    }

    return order;
}

bool processorUsed(const std::vector<num_t>& assignment, const num_t proc) {
    return std::ranges::find(assignment, proc) != assignment.end();
}

bool resourceSelectableForTask(const Input& in, const std::vector<num_t>& assignment,
                               const num_t task, const num_t proc) {
    if (in.tasks[task].time_by_proc[proc] < 0) {
        return false;
    }

    const bool used = processorUsed(assignment, proc);
    if (!used) {
        return true;
    }

    return in.processors[proc].type == ProcessorType::PP;
}

Schedule calculateSchedule(const Input& in, const std::vector<num_t>& assignment) {
    std::vector<num_t> ready_times(in.taskCount(), 0);
    std::vector<num_t> start_times(in.taskCount(), -1);
    std::vector<num_t> processor_available_times(in.processorCount(), 0);
    const std::vector<num_t> order = topologicalOrder(in);

    num_t max_time = 0;
    for (const num_t task : order) {
        const num_t proc = assignment[task];
        if (proc == -1) {
            continue;
        }

        if (in.processors[proc].type == ProcessorType::PP) {
            start_times[task] = std::max(ready_times[task], processor_available_times[proc]);
            processor_available_times[proc] = start_times[task] + in.tasks[task].time_by_proc[proc];
        } else {
            start_times[task] = ready_times[task];
        }

        const num_t finish = start_times[task] + in.tasks[task].time_by_proc[proc];
        max_time = std::max(max_time, finish);

        for (const Dependency& dependency : in.tasks[task].dependencies) {
            if (assignment[dependency.to] == -1) {
                continue;
            }
            ready_times[dependency.to] = std::max(ready_times[dependency.to], finish);
        }
    }

    return Schedule{.task_start_time = start_times, .total_time = max_time};
}

num_t calculateCost(const Input& in, const std::vector<num_t>& assignment) {
    num_t cost = 0;
    std::vector<bool> processor_used(in.processorCount(), false);

    for (num_t task = 0; task < in.taskCount(); task++) {
        const num_t proc = assignment[task];
        if (proc == -1) {
            continue;
        }

        cost += in.tasks[task].cost_by_proc[proc];
        processor_used[proc] = true;
    }

    for (num_t proc = 0; proc < in.processorCount(); proc++) {
        if (!processor_used[proc]) {
            continue;
        }

        cost += in.processors[proc].cost;
        for (const Bus& bus : in.buses) {
            if (proc < static_cast<num_t>(bus.connected_processors.size()) &&
                bus.connected_processors[proc]) {
                cost += bus.hookup_cost;
            }
        }
    }

    return cost;
}

bool tryConstructSystem(const Input& in, const num_t time_limit, std::mt19937& rng,
                        ConstructionResult& result) {
    result.task_processor.assign(in.taskCount(), -1);
    result.task_start_time.assign(in.taskCount(), -1);

    const std::vector<num_t> order = topologicalOrder(in);
    for (const num_t task : order) {
        std::vector<num_t> feasible_processors;

        for (num_t proc = 0; proc < in.processorCount(); proc++) {
            if (!resourceSelectableForTask(in, result.task_processor, task, proc)) {
                continue;
            }

            std::vector<num_t> candidate_assignment = result.task_processor;
            candidate_assignment[task] = proc;
            const Schedule schedule = calculateSchedule(in, candidate_assignment);
            if (schedule.total_time <= time_limit) {
                feasible_processors.push_back(proc);
            }
        }

        if (feasible_processors.empty()) {
            return false;
        }

        std::uniform_int_distribution<std::size_t> dist(0, feasible_processors.size() - 1);
        result.task_processor[task] = feasible_processors[dist(rng)];
    }

    const Schedule schedule = calculateSchedule(in, result.task_processor);
    result.task_start_time = schedule.task_start_time;
    result.total_time = schedule.total_time;
    result.total_cost = calculateCost(in, result.task_processor);

    return result.total_time <= time_limit;
}

ConstructionResult constructSystem(const Input& in, const num_t time_limit, const num_t seed,
                                   const num_t max_attempts) {
    std::mt19937 rng(seed);
    ConstructionResult result;

    for (num_t attempt = 1; attempt <= max_attempts; attempt++) {
        result.attempts = attempt;
        if (tryConstructSystem(in, time_limit, rng, result)) {
            return result;
        }
    }

    throw std::runtime_error("Nie znaleziono rozwiązania po " + std::to_string(max_attempts) +
                             " próbach");
}

std::string processorTypeName(const ProcessorType type) {
    return type == ProcessorType::HC ? "HC" : "PP";
}

void printResult(const Input& in, const num_t time_limit, const ConstructionResult& result) {
    std::cout << "Całkowity koszt: " << result.total_cost << "\n";
    std::cout << "Całkowity czas: " << result.total_time << "\n";
    std::cout << "Ograniczenie czasu: " << time_limit << "\n";
    std::cout << "Liczba prób konstrukcji: " << result.attempts << "\n";

    std::cout << "Przydział zadań:\n";
    for (num_t task = 0; task < in.taskCount(); task++) {
        const num_t proc = result.task_processor[task];
        const num_t start = result.task_start_time[task];
        const num_t finish = start + in.tasks[task].time_by_proc[proc];
        std::cout << in.tasks[task].name << " -> P" << proc << " ("
                  << processorTypeName(in.processors[proc].type) << ", start " << start
                  << ", koniec " << finish << ", czas " << in.tasks[task].time_by_proc[proc]
                  << ", koszt wykonania " << in.tasks[task].cost_by_proc[proc] << ")\n";
    }
}

int main(const int argc, char* argv[]) {
    if (argc != 3 && argc != 4 && argc != 5) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejściowy ograniczenie_czasowe [seed] [max_liczba_prób]\n";
        return 1;
    }

    try {
        const std::string infile = argv[1];
        const num_t time_limit = std::stoi(argv[2]);
        if (time_limit < 0) {
            throw std::runtime_error("Ograniczenie czasowe nie może być ujemne");
        }

        num_t seed = 67;
        if (argc == 4) {
            seed = std::stoi(argv[3]);
        }

        num_t max_attempts = 10000;
        if (argc == 5) {
            max_attempts = std::stoi(argv[4]);
        }

        const Input input = readInput(infile);
        const ConstructionResult result = constructSystem(input, time_limit, seed, max_attempts);
        printResult(input, time_limit, result);
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Błąd: " << e.what() << "\n";
        return 1;
    }
}
