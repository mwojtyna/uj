#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using num_t = std::int32_t;
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

struct Input {
    std::vector<std::unordered_map<num_t, Edge>> adj_list; // lista sąsiedztwa i-tego wierzchołka
    std::vector<Processor> processors;
    std::vector<std::vector<num_t>>
        task_processor_time; // czas wykonania i-tego zadania na j-tym procesorze
    std::vector<std::vector<num_t>>
        task_processor_cost; // koszt wykonania i-tego zadania na j-tym procesorze
    std::vector<Bus> buses;
};

using Task = std::pair<std::string, num_t>;
struct Output {
    std::map<std::string, std::vector<Task>>
        processor_tasks; // nazwa PE -> lista zadań (nazwa, czas rozpoczęcia)
    std::map<std::string, std::vector<std::string>>
        bus_processors; // nazwa szyny -> lista nazw PE połączonych z szyną
};

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

    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        std::istringstream header(line);
        std::string section;
        header >> section;

        if (section == "@tasks") {
            header >> tasks_n;
            input.adj_list.assign(tasks_n, {});

            for (num_t i = 0; i < tasks_n; i++) {
                std::getline(file, line);
                std::istringstream row(line);

                num_t task_id = 0;
                num_t edge_count = 0;
                row >> task_id >> edge_count;

                for (num_t j = 0; j < edge_count; j++) {
                    std::string edge_token;
                    row >> edge_token;

                    std::size_t open_pos = edge_token.find('(');
                    std::size_t close_pos = edge_token.find(')');
                    num_t node = std::stoi(edge_token.substr(0, open_pos));
                    num_t weight =
                        std::stoi(edge_token.substr(open_pos + 1, close_pos - open_pos - 1));

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
                std::string bus_name;
                Bus bus;

                row >> bus_name >> bus.cost >> bus.bandwidth;
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

void writeOutput(Output& output, std::string& outfile) {
    //
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

    return 0;
}
