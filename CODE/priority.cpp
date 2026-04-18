#include "priority.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <climits>
#include <algorithm>

// ---- helper: trim khoảng trắng ----
static inline std::string trim(const std::string& s) {
    size_t l = s.find_first_not_of(" \t\r\n");
    if (l == std::string::npos) return "";
    size_t r = s.find_last_not_of(" \t\r\n");
    return s.substr(l, r - l + 1);
}

// ---- đọc CSV: id,arrival,burst,priority ----
std::vector<ProcessPrio> readProcessesFromCSV(const std::string& filename) {
    std::vector<ProcessPrio> processes;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Cannot open file: " << filename << "\n";
        return processes;
    }

    std::string line;
    // có thể có header -> đọc bỏ 1 dòng
    if (std::getline(file, line)) {
        // nếu dòng đầu không phải header (vd bắt đầu bằng 'P'), ta xử lý luôn
        if (!line.empty() && (line[0] == 'P' || line[0] == 'p')) {
            // xử lý như dữ liệu
            std::stringstream ss(line);
            std::string id, at, bt, pr;
            std::getline(ss, id, ',');
            std::getline(ss, at, ',');
            std::getline(ss, bt, ',');
            std::getline(ss, pr, ',');

            try {
                ProcessPrio p;
                p.id = trim(id);
                p.arrivalTime = std::stoi(trim(at));
                p.burstTime   = std::stoi(trim(bt));
                p.priority    = std::stoi(trim(pr));
                processes.push_back(p);
            } catch (...) {
                // bỏ dòng lỗi
            }
        }
    }

    // đọc các dòng còn lại
    while (std::getline(file, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, at, bt, pr;

        std::getline(ss, id, ',');
        std::getline(ss, at, ',');
        std::getline(ss, bt, ',');
        std::getline(ss, pr, ',');

        try {
            ProcessPrio p;
            p.id = trim(id);
            p.arrivalTime = std::stoi(trim(at));
            p.burstTime   = std::stoi(trim(bt));
            p.priority    = std::stoi(trim(pr));
            processes.push_back(p);
        } catch (...) {
            // bỏ dòng lỗi
            continue;
        }
    }

    return processes;
}

// ---- Priority Non-Preemptive ----
// Quy ước: priority nhỏ hơn => ưu tiên cao hơn
void priorityScheduling(std::vector<ProcessPrio>& processes) {
    int n = (int)processes.size();
    if (n == 0) return;

    // reset trạng thái
    for (auto &p : processes) {
        p.completed = false;
        p.startTime = p.completionTime = p.waitingTime = p.turnaroundTime = 0;
    }

    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int selected = -1;

        // chọn process:
        // priority ↑ (nhỏ hơn), rồi arrivalTime ↑, rồi id ↑
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (selected == -1 ||
                    processes[i].priority < processes[selected].priority ||
                    (processes[i].priority == processes[selected].priority &&
                     processes[i].arrivalTime < processes[selected].arrivalTime) ||
                    (processes[i].priority == processes[selected].priority &&
                     processes[i].arrivalTime == processes[selected].arrivalTime &&
                     processes[i].id < processes[selected].id)) {
                    selected = i;
                }
            }
        }

        // CPU idle -> nhảy tới arrival gần nhất
        if (selected == -1) {
            int nextArrival = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (!processes[i].completed) {
                    nextArrival = std::min(nextArrival, processes[i].arrivalTime);
                }
            }
            currentTime = nextArrival;
            continue;
        }

        // thực thi
        processes[selected].startTime = currentTime;
        processes[selected].completionTime =
            processes[selected].startTime + processes[selected].burstTime;

        processes[selected].turnaroundTime =
            processes[selected].completionTime - processes[selected].arrivalTime;

        processes[selected].waitingTime =
            processes[selected].turnaroundTime - processes[selected].burstTime;

        currentTime = processes[selected].completionTime;
        processes[selected].completed = true;
        completedCount++;
    }
}

// ---- in kết quả ----
void printPriorityResults(const std::vector<ProcessPrio>& processes) {
    int n = (int)processes.size();
    if (n == 0) {
        std::cout << "No processes.\n";
        return;
    }

    double totalWT = 0.0, totalTAT = 0.0;

    std::cout << "\n===== Priority Scheduling (Non-Preemptive) =====\n";
    std::cout << std::left << std::setw(10) << "Process"
              << std::setw(12) << "Arrival"
              << std::setw(10) << "Burst"
              << std::setw(10) << "Prio"
              << std::setw(10) << "Start"
              << std::setw(12) << "Finish"
              << std::setw(12) << "Waiting"
              << std::setw(15) << "Turnaround" << "\n";

    for (const auto& p : processes) {
        std::cout << std::left << std::setw(10) << p.id
                  << std::setw(12) << p.arrivalTime
                  << std::setw(10) << p.burstTime
                  << std::setw(10) << p.priority
                  << std::setw(10) << p.startTime
                  << std::setw(12) << p.completionTime
                  << std::setw(12) << p.waitingTime
                  << std::setw(15) << p.turnaroundTime << "\n";

        totalWT  += p.waitingTime;
        totalTAT += p.turnaroundTime;
    }

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nAverage Waiting Time: " << (totalWT / n) << "\n";
    std::cout << "Average Turnaround Time: " << (totalTAT / n) << "\n";
}

void printGanttPriority(const std::vector<ProcessPrio>& processes) {
    int n = (int)processes.size();
    if (n == 0) {
        std::cout << "No processes.\n";
        return;
    }

    // sắp xếp theo startTime để in Gantt
    std::vector<ProcessPrio> sorted = processes;
    std::sort(sorted.begin(), sorted.end(),
              [](const ProcessPrio& a, const ProcessPrio& b) {
                  if (a.startTime != b.startTime)
                      return a.startTime < b.startTime;
                  return a.id < b.id; // tie-breaker
              });

    std::cout << "\nGantt Chart:\n|";
    for (const auto& p : sorted) {
        std::cout << " " << p.id << " |";
    }
    std::cout << "\n0";
    for (const auto& p : sorted) {
        std::cout << std::setw(4) << p.completionTime;
    }
    std::cout << "\n";
}
