#include "SJF.h"
#include "priority.h"

using namespace std;

int main() {
    string filename = "input.csv";

    vector<ProcessPrio> processes = readProcessesFromCSV(filename);

    if (processes.empty()) {
        cout << "No process data found!" << endl;
        return 1;
    }

    priorityScheduling(processes);
    printResults(processes);

    //B1: Đọc file CSV
    vector<ProcessSJF> p = readProcessesFromCSV_SJF("input.csv");

    //kiểm tra đọc có thành công không
    if (p.empty()) {
        cout << "Khong doc duoc file CSV!\n";
        return 1;
    }

    //B2: Chạy thuật toán SJF
    sjfScheduling(p);

    cout << "Result:\n";
    for (auto &x : p) {
        cout << x.name << "\t"
             << "Arrival=" << x.arrivalTimeSjf << "\t"
             << "Burst=" << x.burstTimeSjf << "\t"
             << "Start=" << x.startTimeSjf << "\t"
             << "Finish=" << x.finishTimeSjf << "\t"
             << "Waiting=" << x.waitingTimeSjf << "\t"
             << "Turnaround=" << x.turnaroundTimeSjf << endl;
    }

    return 0;
}