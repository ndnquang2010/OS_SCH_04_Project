#ifndef SJF_H
#define SJF_H

#include <vector>
#include <string>

struct Process {
    std::string id;
    int arrivalTime;
    int burstTime;

    int startTime = 0;
    int finishTime = 0;
    int waitingTime = 0;
    int turnaroundTime = 0;

    bool completed = false;
};

void sjfScheduling(std::vector<Process>& processes);
void printSJFResults(const std::vector<Process>& processes);
void printGanttSJF(std::vector<Process> p);

#endif
