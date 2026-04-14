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
        p.arrivalTimeSjf = stoi(arrivalStr);
        p.burstTimeSjf = stoi(burstStr);

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
            if (!processes[i].completed && processes[i].arrivalTimeSjf <= currentTime) {
                if (selected == -1 ||
                    processes[i].burstTimeSjf < processes[selected].burstTimeSjf ||
                    (processes[i].burstTimeSjf == processes[selected].burstTimeSjf &&
                     processes[i].arrivalTimeSjf < processes[selected].arrivalTimeSjf)) {
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
        processes[selected].startTimeSjf = currentTime;
        processes[selected].finishTimeSjf = processes[selected].startTimeSjf + processes[selected].burstTimeSjf;

        processes[selected].turnaroundTimeSjf =
            processes[selected].finishTimeSjf - processes[selected].arrivalTimeSjf;

        processes[selected].waitingTimeSjf =
            processes[selected].turnaroundTimeSjf - processes[selected].burstTimeSjf;

        currentTime = processes[selected].finishTimeSjf;
        processes[selected].completed = true;
        completedCount++;
    }
}

// In kết quả
void printResults_SJF(const vector<ProcessSJF>& processes) {
    float totalWaitingSjf = 0, totalTurnaroundSjf = 0;
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
             << setw(12) << p.arrivalTimeSjf
             << setw(10) << p.burstTimeSjf
             << setw(10) << p.startTimeSjf
             << setw(10) << p.finishTimeSjf
             << setw(12) << p.waitingTimeSjf
             << setw(15) << p.turnaroundTimeSjf << endl;

        totalWaitingSjf += p.waitingTimeSjf;
        totalTurnaroundSjf += p.turnaroundTimeSjf;
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage Waiting Time: " << totalWaitingSjf / n << endl;
    cout << "Average Turnaround Time: " << totalTurnaroundSjf / n << endl;
}