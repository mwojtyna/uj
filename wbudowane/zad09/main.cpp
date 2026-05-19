#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <queue>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using num_t = std::int32_t;

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

struct Params {
    double k1 = 0.0;
    double k2 = 0.0;
    double k3 = 0.0;
    num_t tmax = 0;
    double fmax = 0.0;
};

struct Schedule {
    std::vector<num_t> task_start_time;
    num_t total_time = 0;
};

struct Candidate {
    num_t proc = -1;
    num_t time = 0;
    num_t cost = 0;
    double f = 0.0;
};

struct ConstructionResult {
    std::vector<num_t> task_processor;
    std::vector<num_t> task_start_time;
    num_t total_time = 0;
    num_t total_cost = 0;
    double f = 0.0;
};

num_t parseTaskId(const std::string& token) {
    if (token.empty()) {
        throw std::runtime_error("Pusty identyfikator zadania");
    }

    if (token[0] == 'T' || token[0] == 't') {
        return std::stoi(token.substr(1));
    }

    return std::stoi(token);
}

std::vector<num_t> readProcessorVector(const std::string& line, const num_t proc_n,
                                       const std::string& section) {
    std::istringstream row(line);
    std::vector<num_t> values(proc_n, 0);
    for (num_t i = 0; i < proc_n; i++) {
        if (!(row >> values[i])) {
            throw std::runtime_error("Za mało wartości w sekcji " + section);
        }
    }

    return values;
}

Input readInput(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku wejściowego: " + filename);
    }

    Input input;
    std::string line;
    num_t tasks_n = 0;
    num_t proc_n = 0;

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
                const num_t task_id = parseTaskId(task_token);
                if (task_id < 0 || task_id >= tasks_n) {
                    throw std::runtime_error("Identyfikator zadania poza zakresem");
                }

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;

                    const std::size_t open_pos = edge_token.find('(');
                    const std::size_t close_pos = edge_token.find(')');
                    if (open_pos == std::string::npos || close_pos == std::string::npos ||
                        close_pos <= open_pos) {
                        throw std::runtime_error("Niepoprawny opis krawędzi: " + edge_token);
                    }

                    const num_t node =
                        static_cast<num_t>(std::stoi(edge_token.substr(0, open_pos)));
                    const num_t weight = static_cast<num_t>(
                        std::stoi(edge_token.substr(open_pos + 1, close_pos - open_pos - 1)));

                    if (node < 0 || node >= tasks_n) {
                        throw std::runtime_error("Krawędź prowadzi do zadania poza zakresem");
                    }
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
                input.tasks[i].time_by_proc = readProcessorVector(line, proc_n, "@times");
            }
        } else if (section == "@cost") {
            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                input.tasks[i].cost_by_proc = readProcessorVector(line, proc_n, "@cost");
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

    if (input.tasks.empty()) {
        throw std::runtime_error("Brak sekcji @tasks");
    }
    if (input.processors.empty()) {
        throw std::runtime_error("Brak sekcji @proc albo brak procesorów");
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
        if (proc < 0 || proc >= in.processorCount() || in.tasks[task].time_by_proc[proc] < 0) {
            throw std::runtime_error("Niepoprawny przydział procesora do zadania");
        }
        if (!hcAvailableForTask(in, assignment, task, proc)) {
            throw std::runtime_error("Ten sam procesor HC został przypisany do kilku zadań");
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

double calculateF(const Params& params, const num_t cost, const num_t time) {
    const num_t penalty = std::max<num_t>(0, time - params.tmax);
    return params.k1 * cost + params.k2 * time + params.k3 * penalty;
}

ConstructionResult constructSystem(const Input& in, const Params& params) {
    ConstructionResult result;
    result.task_processor.assign(in.taskCount(), -1);
    result.task_start_time.assign(in.taskCount(), -1);

    for (const std::vector<num_t> order = topologicalOrder(in); const num_t task : order) {
        Candidate best;
        bool found = false;

        for (num_t proc = 0; proc < in.processorCount(); proc++) {
            if (in.tasks[task].time_by_proc[proc] < 0 ||
                !hcAvailableForTask(in, result.task_processor, task, proc)) {
                continue;
            }

            std::vector<num_t> candidate_assignment = result.task_processor;
            candidate_assignment[task] = proc;
            const Schedule schedule = calculateSchedule(in, candidate_assignment);
            const num_t cost = calculateCost(in, candidate_assignment);
            const double f = calculateF(params, cost, schedule.total_time);

            if (f > params.fmax) {
                continue;
            }

            if (!found || cost < best.cost ||
                (cost == best.cost && schedule.total_time < best.time) ||
                (cost == best.cost && schedule.total_time == best.time && proc < best.proc)) {

                best = Candidate{.proc = proc, .time = schedule.total_time, .cost = cost, .f = f};
                found = true;
            }
        }

        if (!found) {
            throw std::runtime_error("Nie istnieje lokalnie dopuszczalny zasób dla zadania T" +
                                     std::to_string(task));
        }

        result.task_processor[task] = best.proc;
        const Schedule schedule = calculateSchedule(in, result.task_processor);
        result.task_start_time = schedule.task_start_time;
        result.total_time = schedule.total_time;
        result.total_cost = calculateCost(in, result.task_processor);
        result.f = calculateF(params, result.total_cost, result.total_time);
    }

    return result;
}

std::string processorTypeName(const ProcessorType type) {
    return type == ProcessorType::HC ? "HC" : "PP";
}

void printResult(const Input& in, const Params& params, const ConstructionResult& result) {
    const num_t penalty = std::max<num_t>(0, result.total_time - params.tmax);

    std::cout << "Całkowity koszt: " << result.total_cost << "\n";
    std::cout << "Całkowity czas: " << result.total_time << "\n";
    std::cout << "Kara: " << penalty << "\n";
    std::cout << std::fixed << std::setprecision(4);
    std::cout << "F: " << result.f << "\n";

    std::cout << "Przydział zadań:\n";
    for (num_t task = 0; task < in.taskCount(); task++) {
        const num_t proc = result.task_processor[task];
        const num_t start = result.task_start_time[task];
        const num_t finish = start + in.tasks[task].time_by_proc[proc];
        std::cout << "T" << task << " -> P" << proc << " ("
                  << processorTypeName(in.processors[proc].type) << ", start " << start
                  << ", koniec " << finish << ", czas " << in.tasks[task].time_by_proc[proc]
                  << ", koszt wykonania " << in.tasks[task].cost_by_proc[proc] << ")\n";
    }
}

int main(const int argc, char* argv[]) {
    if (argc != 7) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejściowy k1 k2 k3 tmax fmax\n";
        return 1;
    }

    try {
        const std::string infile = argv[1];
        const Params params = {
            .k1 = std::stod(argv[2]),
            .k2 = std::stod(argv[3]),
            .k3 = std::stod(argv[4]),
            .tmax = std::stoi(argv[5]),
            .fmax = std::stod(argv[6]),
        };

        const Input input = readInput(infile);
        const ConstructionResult result = constructSystem(input, params);
        printResult(input, params, result);
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Błąd: " << e.what() << "\n";
        return 1;
    }
}
