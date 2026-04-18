#include <iostream>
#include <vector>
#include "SJF.h"
#include "priority.h"

using namespace std;

// ---- chuyển ProcessPrio -> Process (cho SJF dùng chung input) ----
vector<Process> convertToSJF(const vector<ProcessPrio>& prioList) {
    vector<Process> sjfList;

    for (const auto& p : prioList) {
        Process temp;
        temp.id = p.id;
        temp.arrivalTime = p.arrivalTime;
        temp.burstTime = p.burstTime;
        sjfList.push_back(temp);
    }

    return sjfList;
}

int main() {
    string filename = "input.csv";

    // đọc dữ liệu 1 lần
    vector<ProcessPrio> processesPrio = readProcessesFromCSV(filename);

    if (processesPrio.empty()) {
        cout << "No data found or cannot read file.\n";
        return 0;
    }

    int choice;

    cout << "===== CPU Scheduling Simulator =====\n";
    cout << "1. Shortest Job First (SJF)\n";
    cout << "2. Priority Scheduling\n";
    cout << "Choose algorithm: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            vector<Process> processesSJF = convertToSJF(processesPrio);

            sjfScheduling(processesSJF);
            printSJFResults(processesSJF);

            break;
        }

        case 2: {
            priorityScheduling(processesPrio);
            printPriorityResults(processesPrio);

            break;
        }

        default:
            cout << "Invalid choice.\n";
    }

    return 0;
}
