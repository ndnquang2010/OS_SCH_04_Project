#include "Priority.h"
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

// Hàm đọc dữ liệu từ file CSV
vector<ProcessPrio> readProcessesFromCSV(const string& filename) {
    vector<ProcessPrio> processes;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return processes;
    }

    string line;
    getline(file, line); // Bỏ qua dòng tiêu đề

    while (getline(file, line)) {
        stringstream ss(line);
        string name, arrivalStr, burstStr, priorityStr;

        getline(ss, name, ',');
        getline(ss, arrivalStr, ',');
        getline(ss, burstStr, ',');
        getline(ss, priorityStr, ',');

        ProcessPrio p;
        p.name = name;
        p.arrivalTime = stoi(arrivalStr);
        p.burstTime = stoi(burstStr);
        p.priority = stoi(priorityStr);

        processes.push_back(p);
    }

    file.close();
    return processes;
}

// Priority Non-Preemptive
void priorityScheduling(vector<ProcessPrio>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int selected = -1;

        // Tìm process phù hợp tại thời điểm hiện tại
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (selected == -1 ||
                    processes[i].priority < processes[selected].priority ||
                    (processes[i].priority == processes[selected].priority &&
                     processes[i].arrivalTime < processes[selected].arrivalTime)) {
                    selected = i;
                }
            }
        }

        // Nếu chưa có process nào đến thì CPU chờ
        if (selected == -1) {
            currentTime++;
            continue;
        }

        // Chạy process được chọn
        processes[selected].startTime = currentTime;
        processes[selected].finishTime = processes[selected].startTime + processes[selected].burstTime;
        processes[selected].waitingTime = processes[selected].startTime - processes[selected].arrivalTime;
        processes[selected].turnaroundTime = processes[selected].finishTime - processes[selected].arrivalTime;

        currentTime = processes[selected].finishTime;
        processes[selected].completed = true;
        completedCount++;
    }
}

// In kết quả ra màn hình
void printResults(const vector<ProcessPrio>& processes) {
    float totalWaiting = 0, totalTurnaround = 0;
    int n = processes.size();

    cout << "\n===== Priority Scheduling (Non-Preemptive) =====\n";
    cout << left << setw(10) << "Process"
         << setw(12) << "Arrival"
         << setw(10) << "Burst"
         << setw(10) << "Priority"
         << setw(10) << "Start"
         << setw(10) << "Finish"
         << setw(12) << "Waiting"
         << setw(15) << "Turnaround" << endl;

    for (const auto& p : processes) {
        cout << left << setw(10) << p.name
             << setw(12) << p.arrivalTime
             << setw(10) << p.burstTime
             << setw(10) << p.priority
             << setw(10) << p.startTime
             << setw(10) << p.finishTime
             << setw(12) << p.waitingTime
             << setw(15) << p.turnaroundTime << endl;

        totalWaiting += p.waitingTime;
        totalTurnaround += p.turnaroundTime;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaiting / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaround / n << endl;
}