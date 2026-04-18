#ifndef PRIORITY_H
#define PRIORITY_H

#include <vector>
#include <string>

struct ProcessPrio {
    std::string id;

    int arrivalTime;
    int burstTime;
    int priority; // smaller value = higher priority

    int startTime = 0;
    int completionTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;

    bool completed = false;
};

// Đọc file CSV
std::vector<ProcessPrio> readProcessesFromCSV(const std::string& filename);

// Priority Non-Preemptive
void priorityScheduling(std::vector<ProcessPrio>& processes);

// In kết quả
void printPriorityResults(const std::vector<ProcessPrio>& processes);

void printGanttPriority(const std::vector<ProcessPrio>& processes);
#endif
