#include "sjf.h"
#include <fstream>
#include <sstream>
#include <iomanip>

// Đọc file CSV
vector<ProcessSJF> readProcessesFromCSV_SJF(const string& filename) {
    vector<ProcessSJF> processes;
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Cannot open file: " << filename << endl;
        return processes;
    }

    string line;
    getline(file, line); // bỏ header

    while (getline(file, line)) {
        stringstream ss(line);
        string name, arrivalStr, burstStr;

        getline(ss, name, ',');
        getline(ss, arrivalStr, ',');
        getline(ss, burstStr, ',');

        ProcessSJF p;
        p.name = name;
        p.arrivalTime = stoi(arrivalStr);
        p.burstTime = stoi(burstStr);

        processes.push_back(p);
    }

    file.close();
    return processes;
}

// SJF
void sjfScheduling(vector<ProcessSJF>& processes) {
    int n = processes.size();
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int selected = -1;

        // Tìm process có burst nhỏ nhất trong ready queue
        for (int i = 0; i < n; i++) {
            if (!processes[i].completed && processes[i].arrivalTime <= currentTime) {
                if (selected == -1 ||
                    processes[i].burstTime < processes[selected].burstTime ||
                    (processes[i].burstTime == processes[selected].burstTime &&
                     processes[i].arrivalTime < processes[selected].arrivalTime)) {
                    selected = i;
                }
            }
        }

        // Nếu chưa có process nào đến → CPU idle
        if (selected == -1) {
            currentTime++;
            continue;
        }

        // Thực thi process
        processes[selected].startTime = currentTime;
        processes[selected].finishTime = processes[selected].startTime + processes[selected].burstTime;

        processes[selected].turnaroundTime =
            processes[selected].finishTime - processes[selected].arrivalTime;

        processes[selected].waitingTime =
            processes[selected].turnaroundTime - processes[selected].burstTime;

        currentTime = processes[selected].finishTime;
        processes[selected].completed = true;
        completedCount++;
    }
}

// In kết quả
void printResults_SJF(const vector<ProcessSJF>& processes) {
    float totalWaiting = 0, totalTurnaround = 0;
    int n = processes.size();

    cout << "\n===== SJF Scheduling =====\n";
    cout << left << setw(10) << "Process"
         << setw(12) << "Arrival"
         << setw(10) << "Burst"
         << setw(10) << "Start"
         << setw(10) << "Finish"
         << setw(12) << "Waiting"
         << setw(15) << "Turnaround" << endl;

    for (const auto& p : processes) {
        cout << left << setw(10) << p.name
             << setw(12) << p.arrivalTime
             << setw(10) << p.burstTime
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