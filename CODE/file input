#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Process {
    string name;
    int arrival, burst, priority;
    int waiting, turnaround, completion;
};

// ================= READ CSV =================
vector<Process> readCSV(string filename) {
    vector<Process> processes;
    ifstream file(filename);
    string line;

    getline(file, line); // bỏ header

    while (getline(file, line)) {
        stringstream ss(line);
        string temp;
        Process p;

        getline(ss, p.name, ',');

        getline(ss, temp, ',');
        p.arrival = stoi(temp);

        getline(ss, temp, ',');
        p.burst = stoi(temp);

        getline(ss, temp, ',');
        p.priority = stoi(temp);

        p.waiting = p.turnaround = p.completion = 0;

        processes.push_back(p);
    }
    return processes;
}

// ================= PRINT TABLE =================
void printTable(vector<Process> p) {
    cout << "\nProcess\tArr\tBurst\tPri\tWait\tTurn\n";
    for (auto x : p) {
        cout << x.name << "\t"
             << x.arrival << "\t"
             << x.burst << "\t"
             << x.priority << "\t"
             << x.waiting << "\t"
             << x.turnaround << endl;
    }
}

// ================= GANTT =================
void printGantt(vector<Process> p) {
    cout << "\nGantt Chart:\n| ";
    for (auto x : p) {
        cout << x.name << " | ";
    }

    cout << "\n0 ";
    for (auto x : p) {
        cout << "   " << x.completion;
    }
    cout << endl;
}

// ================= SJF =================
void SJF(vector<Process> p) {
    int time = 0, completed = 0, n = p.size();
    vector<bool> done(n, false);
    vector<Process> result;

    while (completed < n) {
        int idx = -1;
        int minBurst = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (p[i].burst < minBurst) {
                    minBurst = p[i].burst;
                    idx = i;
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        done[idx] = true;
        result.push_back(p[idx]);
        completed++;
    }

    cout << "\n===== SJF =====";
    printTable(result);
    printGantt(result);
}

// ================= PRIORITY =================
void Priority(vector<Process> p) {
    int time = 0, completed = 0, n = p.size();
    vector<bool> done(n, false);
    vector<Process> result;

    while (completed < n) {
        int idx = -1;
        int bestPri = 1e9;

        for (int i = 0; i < n; i++) {
            if (!done[i] && p[i].arrival <= time) {
                if (p[i].priority < bestPri) {
                    bestPri = p[i].priority;
                    idx = i;
                }
                else if (p[i].priority == bestPri) {
                    if (p[i].arrival < p[idx].arrival) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            time++;
            continue;
        }

        time += p[idx].burst;
        p[idx].completion = time;
        p[idx].turnaround = time - p[idx].arrival;
        p[idx].waiting = p[idx].turnaround - p[idx].burst;

        done[idx] = true;
        result.push_back(p[idx]);
        completed++;
    }

    cout << "\n===== PRIORITY =====";
    printTable(result);
    printGantt(result);
}

// ================= MAIN =================
int main() {
    vector<Process> processes = readCSV("input.csv");

    int choice;
    cout << "1. SJF\n2. Priority\n3. Both\nChoose: ";
    cin >> choice;

    if (choice == 1) SJF(processes);
    else if (choice == 2) Priority(processes);
    else {
        SJF(processes);
        Priority(processes);
    }

    return 0;
}
