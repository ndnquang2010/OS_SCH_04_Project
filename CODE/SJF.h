#ifndef SJF_H
#define SJF_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct ProcessSJF {
    string name;
    int arrivalTimeSjf;
    int burstTimeSjf;

    int startTimeSjf;
    int finishTimeSjf;
    int waitingTimeSjf;
    int turnaroundTimeSjf;

    bool completed = false;
};

// Đọc file CSV
vector<ProcessSJF> readProcessesFromCSV_SJF(const string& filename);

// SJF Non-Preemptive
void sjfScheduling(vector<ProcessSJF>& processes);

// In kết quả
void printResults_SJF(const vector<ProcessSJF>& processes);

#endif