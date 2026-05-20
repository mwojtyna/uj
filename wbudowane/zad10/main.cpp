#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using num_t = std::int32_t;

struct Dependency {
    num_t to;
    num_t data_size;
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

struct Candidate {
    num_t proc = -1;
    num_t time = 0;
    num_t cost = 0;
    num_t load = 0;
};

struct ConstructionResult {
    std::vector<num_t> task_processor;
    std::vector<num_t> task_start_time;
    num_t total_time = 0;
    num_t total_cost = 0;
};

struct RawDependency {
    num_t from;
    std::string to_token;
    num_t data_size;
};

bool startsWith(const std::string& text, const std::string& prefix) {
    return text.rfind(prefix, 0) == 0;
}

bool isBlank(const std::string& text) {
    return std::all_of(text.begin(), text.end(),
                       [](const char c) { return std::isspace(static_cast<unsigned char>(c)); });
}

std::string normalizeTaskToken(std::string token) {
    for (char& c : token) {
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
    }
    return token;
}

bool isUnexpectedTask(const std::string& name) {
    return startsWith(normalizeTaskToken(name), "UT");
}

bool isNumber(const std::string& token) {
    return !token.empty() && std::all_of(token.begin(), token.end(), [](const char c) {
        return std::isdigit(static_cast<unsigned char>(c));
    });
}

num_t parseRegularTaskNumber(const std::string& token) {
    const std::string normalized = normalizeTaskToken(token);
    if (isNumber(normalized)) {
        return std::stoi(normalized);
    }
    if (startsWith(normalized, "T") && normalized.size() > 1 && isNumber(normalized.substr(1))) {
        return std::stoi(normalized.substr(1));
    }

    return -1;
}

num_t resolveTaskToken(const std::unordered_map<std::string, num_t>& task_id_by_name,
                       const std::string& token, const num_t tasks_n) {
    const std::string normalized = normalizeTaskToken(token);
    const auto it = task_id_by_name.find(normalized);
    if (it != task_id_by_name.end()) {
        return it->second;
    }

    const num_t regular_id = parseRegularTaskNumber(normalized);
    if (regular_id >= 0 && regular_id < tasks_n) {
        return regular_id;
    }

    throw std::runtime_error("Nieznany identyfikator zadania: " + token);
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

            for (num_t row_idx = 0; row_idx < tasks_n; row_idx++) {
                std::getline(file, line);
                std::istringstream row(line);

                std::string task_token;
                num_t edge_count = 0;
                row >> task_token >> edge_count;

                const num_t task_id = row_idx;
                input.tasks[task_id].name = task_token;
                task_id_by_name[normalizeTaskToken(task_token)] = task_id;
                task_id_by_name[std::to_string(task_id)] = task_id;

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;

                    const std::size_t open_pos = edge_token.find('(');
                    const std::size_t close_pos = edge_token.find(')');

                    raw_dependencies.push_back(RawDependency{
                        .from = task_id,
                        .to_token = edge_token.substr(0, open_pos),
                        .data_size =
                            std::stoi(edge_token.substr(open_pos + 1, close_pos - open_pos - 1)),
                    });
                }
            }

            for (const RawDependency& dependency : raw_dependencies) {
                const num_t to = resolveTaskToken(task_id_by_name, dependency.to_token, tasks_n);
                input.tasks[dependency.from].dependencies.push_back(
                    Dependency{.to = to, .data_size = dependency.data_size});
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

    if (static_cast<num_t>(order.size()) != in.taskCount()) {
        throw std::runtime_error("Graf posiada cykl");
    }

    return order;
}

bool hcAvailableForTask(const Input& in, const std::vector<num_t>& assignment, const num_t task,
                        const num_t proc) {
    if (in.processors[proc].type == ProcessorType::PP) {
        return true;
    }

    for (num_t other_task = 0; other_task < static_cast<num_t>(assignment.size()); other_task++) {
        if (other_task != task && assignment[other_task] == proc) {
            return false;
        }
    }

    return true;
}

num_t communicationDelay(const Input& in, const num_t from_proc, const num_t to_proc,
                         const num_t data_size) {
    if (from_proc == to_proc || data_size == 0) {
        return 0;
    }

    num_t best = std::numeric_limits<num_t>::max();
    for (const Bus& bus : in.buses) {
        if (bus.bandwidth <= 0) {
            continue;
        }
        if (from_proc < static_cast<num_t>(bus.connected_processors.size()) &&
            to_proc < static_cast<num_t>(bus.connected_processors.size()) &&
            bus.connected_processors[from_proc] && bus.connected_processors[to_proc]) {
            const num_t delay = (data_size + bus.bandwidth - 1) / bus.bandwidth;
            best = std::min(best, delay);
        }
    }

    if (best == std::numeric_limits<num_t>::max()) {
        throw std::runtime_error("Brak wspólnej szyny komunikacyjnej dla procesorów P" +
                                 std::to_string(from_proc) + " i P" + std::to_string(to_proc));
    }

    return best;
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
            const num_t child_proc = assignment[dependency.to];
            const num_t communication_time =
                communicationDelay(in, proc, child_proc, dependency.data_size);
            ready_times[dependency.to] =
                std::max(ready_times[dependency.to], finish + communication_time);
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

num_t assignedTaskCount(const std::vector<num_t>& assignment, const num_t proc) {
    return static_cast<num_t>(std::count(assignment.begin(), assignment.end(), proc));
}

ConstructionResult constructSystem(const Input& in) {
    ConstructionResult result;
    result.task_processor.assign(in.taskCount(), -1);
    result.task_start_time.assign(in.taskCount(), -1);

    const std::vector<num_t> order = topologicalOrder(in);
    for (const num_t task : order) {
        Candidate best;
        bool found = false;
        const bool unexpected = isUnexpectedTask(in.tasks[task].name);

        for (num_t proc = 0; proc < in.processorCount(); proc++) {
            if (in.tasks[task].time_by_proc[proc] < 0 ||
                !hcAvailableForTask(in, result.task_processor, task, proc)) {
                continue;
            }
            if (unexpected && in.processors[proc].type != ProcessorType::PP) {
                continue;
            }

            std::vector<num_t> candidate_assignment = result.task_processor;
            candidate_assignment[task] = proc;

            const Schedule schedule = calculateSchedule(in, candidate_assignment);
            const num_t cost = calculateCost(in, candidate_assignment);
            const num_t load = assignedTaskCount(result.task_processor, proc);

            const bool better_regular =
                !unexpected &&
                (!found || cost < best.cost ||
                 (cost == best.cost && schedule.total_time < best.time) ||
                 (cost == best.cost && schedule.total_time == best.time && proc < best.proc));

            const bool better_unexpected =
                unexpected &&
                (!found || load < best.load || (load == best.load && cost < best.cost) ||
                 (load == best.load && cost == best.cost && schedule.total_time < best.time) ||
                 (load == best.load && cost == best.cost && schedule.total_time == best.time &&
                  proc < best.proc));

            if (better_regular || better_unexpected) {
                best = Candidate{
                    .proc = proc, .time = schedule.total_time, .cost = cost, .load = load};
                found = true;
            }
        }

        if (!found) {
            throw std::runtime_error("Nie istnieje lokalnie dopuszczalny zasób dla zadania " +
                                     in.tasks[task].name);
        }

        result.task_processor[task] = best.proc;
        const Schedule schedule = calculateSchedule(in, result.task_processor);
        result.task_start_time = schedule.task_start_time;
        result.total_time = schedule.total_time;
        result.total_cost = calculateCost(in, result.task_processor);
    }

    return result;
}

std::string processorTypeName(const ProcessorType type) {
    return type == ProcessorType::HC ? "HC" : "PP";
}

void printResult(const Input& in, const ConstructionResult& result) {
    std::cout << "Całkowity koszt: " << result.total_cost << "\n";
    std::cout << "Całkowity czas: " << result.total_time << "\n";

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
    if (argc != 2) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejściowy\n";
        return 1;
    }

    try {
        const std::string infile = argv[1];
        const Input input = readInput(infile);
        const ConstructionResult result = constructSystem(input);
        printResult(input, result);
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Błąd: " << e.what() << "\n";
        return 1;
    }
}
