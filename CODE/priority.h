#ifndef PRIORITY_H
#define PRIORITY_H

#include <vector>
#include <string>
using namespace std;

struct ProcessPrio {
    string name;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
    int originalIndex;

    bool completed = false;
};

// Đọc file CSV
vector<ProcessPrio> readProcessesFromCSV(const string& filename);

// Priority Non-Preemptive
void priorityScheduling(vector<ProcessPrio>& processes);

// In kết quả
void printResults(const vector<ProcessPrio>& processes);

#endif