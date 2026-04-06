#ifndef PRIORITY_H
#define PRIORITY_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Process {
    string name;
    int arrivalTime;
    int burstTime;
    int priority;
    int startTime;
    int finishTime;
    int waitingTime;
    int turnaroundTime;
    bool completed = false;
};

// Đọc dữ liệu từ file CSV
vector<Process> readProcessesFromCSV(const string& filename);

// Priority Non-Preemptive
void priorityScheduling(vector<Process>& processes);

// In kết quả ra màn hình
void printResults(const vector<Process>& processes);

#endif