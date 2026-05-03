#include <algorithm>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <limits>
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
    num_t hookup_cost;
    num_t bandwidth;
    std::vector<bool> connected_processors;
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

struct RefinementResult {
    std::vector<num_t> task_processor;
    num_t total_time = 0;
    num_t total_cost = 0;
    num_t iterations = 0;
    std::string stop_reason;
};

num_t parseTaskId(const std::string& token) {
    if (token.empty()) {
        throw std::runtime_error("Pusty identyfikator zadania");
    }

    if (token[0] == 'T' || token[0] == 't') {
        return static_cast<num_t>(std::stoi(token.substr(1)));
    }

    return static_cast<num_t>(std::stoi(token));
}

std::vector<num_t> readProcessorVector(const std::string& line, num_t proc_n,
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

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;

                    const std::size_t open_pos = edge_token.find('(');
                    const std::size_t close_pos = edge_token.find(')');
                    const num_t node =
                        static_cast<num_t>(std::stoi(edge_token.substr(0, open_pos)));
                    const num_t weight = static_cast<num_t>(
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

    return input;
}

num_t calculateTime(const Input& in, const std::vector<num_t>& assignment) {
    const num_t task_count = in.taskCount();
    std::vector<num_t> indeg(task_count, 0);

    for (num_t task = 0; task < task_count; task++) {
        for (const Dependency& dependency : in.tasks[task].dependencies) {
            indeg[dependency.to] += 1;
        }
    }

    // toposort
    std::queue<num_t> q;
    std::vector<num_t> start_time(task_count, 0);
    for (num_t task = 0; task < task_count; task++) {
        if (indeg[task] == 0) {
            q.push(task);
        }
    }

    num_t max_time = 0;
    while (!q.empty()) {
        const num_t task = q.front();
        q.pop();

        const num_t proc = assignment[task];
        const num_t finish = start_time[task] + in.tasks[task].time_by_proc[proc];
        max_time = std::max(max_time, finish);

        for (const Dependency& dependency : in.tasks[task].dependencies) {
            start_time[dependency.to] = std::max(start_time[dependency.to], finish);
            indeg[dependency.to] -= 1;
            if (indeg[dependency.to] == 0) {
                q.push(dependency.to);
            }
        }
    }

    return max_time;
}

num_t calculateCost(const Input& in, const std::vector<num_t>& assignment) {
    num_t cost = 0;
    for (num_t task = 0; task < in.taskCount(); task++) {
        cost += in.tasks[task].cost_by_proc[assignment[task]];
    }
    return cost;
}

num_t fastestProcessorForTask(const TaskProfile& task) {
    num_t best = -1;
    for (num_t proc = 0; proc < static_cast<num_t>(task.time_by_proc.size()); proc++) {
        if (task.time_by_proc[proc] == -1) {
            continue;
        }

        if (best == -1 || task.time_by_proc[proc] < task.time_by_proc[best] ||
            (task.time_by_proc[proc] == task.time_by_proc[best] &&
             task.cost_by_proc[proc] < task.cost_by_proc[best])) {

            best = proc;
        }
    }

    if (best == -1) {
        throw std::runtime_error("Zadanie nie ma żadnej dostępnej implementacji");
    }
    return best;
}

num_t nextSlowerProcessorForTask(const TaskProfile& task, num_t current_proc) {
    const num_t current_time = task.time_by_proc[current_proc];
    num_t best = -1;

    for (num_t proc = 0; proc < static_cast<num_t>(task.time_by_proc.size()); proc++) {
        const num_t candidate_time = task.time_by_proc[proc];
        if (candidate_time < 0 || candidate_time <= current_time) {
            continue;
        }

        // Szukamy najbliższej wolniejszej implementacji, czyli najszybszej z wolniejszych.
        if (best == -1 || candidate_time < task.time_by_proc[best] ||
            (candidate_time == task.time_by_proc[best] &&
             task.cost_by_proc[proc] < task.cost_by_proc[best])) {

            best = proc;
        }
    }

    return best;
}

RefinementResult refine(const Input& in, num_t time_limit) {
    RefinementResult result;
    result.task_processor.assign(in.taskCount(), 0);

    // Startujemy od najszybszego wariantu dla każdego zadania.
    for (num_t task = 0; task < in.taskCount(); task++) {
        result.task_processor[task] = fastestProcessorForTask(in.tasks[task]);
    }

    result.total_time = calculateTime(in, result.task_processor);
    result.total_cost = calculateCost(in, result.task_processor);
    if (result.total_time > time_limit) {
        result.stop_reason = "Najszybszy przydział przekracza ograniczenie czasowe";
        return result;
    }

    while (true) {
        num_t chosen_task = -1;
        num_t chosen_next_proc = -1;
        num_t max_current_cost = std::numeric_limits<num_t>::min();

        // Wybieramy najdroższy aktualny wariant, ale tylko taki, który ma wolniejszą alternatywę.
        for (num_t task = 0; task < in.taskCount(); task++) {
            const num_t current_proc = result.task_processor[task];
            const num_t next_proc = nextSlowerProcessorForTask(in.tasks[task], current_proc);
            if (next_proc == -1) {
                continue;
            }

            const num_t current_cost = in.tasks[task].cost_by_proc[current_proc];
            if (chosen_task == -1 || current_cost > max_current_cost ||
                (current_cost == max_current_cost &&
                 in.tasks[task].time_by_proc[next_proc] <
                     in.tasks[chosen_task].time_by_proc[chosen_next_proc])) {

                chosen_task = task;
                chosen_next_proc = next_proc;
                max_current_cost = current_cost;
            }
        }

        if (chosen_task == -1) {
            result.stop_reason = "Dla żadnego zadania nie ma wolniejszej implementacji";
            break;
        }

        std::vector<num_t> candidate_assignment = result.task_processor;
        candidate_assignment[chosen_task] = chosen_next_proc;
        const num_t candidate_time = calculateTime(in, candidate_assignment);

        if (candidate_time > time_limit) {
            result.stop_reason = "Następna decyzja przekroczyłaby ograniczenie czasowe";
            break;
        }

        result.task_processor = candidate_assignment;
        result.total_time = candidate_time;
        result.total_cost = calculateCost(in, result.task_processor);
        result.iterations += 1;
    }

    return result;
}

void printResult(const Input& in, const RefinementResult& result) {
    std::cout << "Całkowity czas: " << result.total_time << "\n";
    std::cout << "Całkowity koszt: " << result.total_cost << "\n";
    std::cout << "Liczba iteracji: " << result.iterations << "\n";
    std::cout << "Powód zatrzymania: " << result.stop_reason << "\n";

    std::cout << "Przydział zadań:\n";
    for (num_t task = 0; task < in.taskCount(); task++) {
        const num_t proc = result.task_processor[task];
        std::cout << "T" << task << " -> P" << proc << " (czas "
                  << in.tasks[task].time_by_proc[proc] << ", koszt "
                  << in.tasks[task].cost_by_proc[proc] << ")\n";
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Złe argumenty! Poprawne argumenty:\n";
        std::cout << "plik_wejściowy ograniczenie_czasowe\n";
        return 1;
    }

    try {
        const std::string infile = argv[1];
        const num_t time_limit = static_cast<num_t>(std::stoi(argv[2]));

        const Input input = readInput(infile);
        const RefinementResult result = refine(input, time_limit);
        printResult(input, result);
        return 0;
    } catch (const std::exception& e) {
        std::cout << "Błąd: " << e.what() << "\n";
        return 1;
    }
}
